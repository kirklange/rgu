/*  rgu_game.c
 *
 *  <!---------
 *  Copyright (c) 2018 Kirk Lange
 *  
 *  This software is provided 'as-is', without any express or implied
 *  warranty.  In no event will the authors be held liable for any damages
 *  arising from the use of this software.
 *
 *  Permission is granted to anyone to use this software for any purpose,
 *  including commercial applications, and to alter it and redistribute it
 *  freely, subject to the following restrictions:
 *
 *  1. The origin of this software must not be misrepresented; you must not
 *     claim that you wrote the original software. If you use this software
 *     in a product, an acknowledgment in the product documentation would be
 *     appreciated but is not required.
 *  2. Altered source versions must be plainly marked as such, and must not be
 *     misrepresented as being the original software.
 *  3. This notice may not be removed or altered from any source distribution.
 *  ---------->
 */

#include "rgu/rgu_game.h"

#include "rgu/rgu_board.h"
#include "rgu/rgu_dice.h"
#include "rgu/rgu_piece.h"
#include "rgu/rgu_tile.h"

#include <stdio.h>
#include <stdlib.h>



#define STRLEN 64
#define STRFMT " %63s"

static uint8_t seeded = 0;



rgu_game* rgu_game_new()
{
    rgu_game *self = (rgu_game*) malloc(sizeof(rgu_game));

    self->board = rgu_board_new();
    self->turn = rand()%2 == 0 ? ALPHA : BRAVO;

    if (!seeded)
    {
        rgu_dice_seed();
        seeded = 1;
    }

    return self;
}



rgu_game* rgu_game_cpy(rgu_game *orig)
{
    rgu_game *copy = (rgu_game*) malloc(sizeof(rgu_game));

    copy->board = rgu_board_cpy(orig->board);
    copy->turn = orig->turn;

    return copy;
}



uint8_t rgu_game_del(rgu_game *self)
{
    if (self)
    {
        rgu_board_del(self->board);
        free(self);
    }
    else
    {
        /* Cannot free null pointer. */
        return 0;
    }
}



uint8_t rgu_game_flipTurn(rgu_game *self)
{
    if (self)
    {
        self->turn = (self->turn == ALPHA ? BRAVO : ALPHA);
    }
    else
    {
        /* Null pointer input */
        return 0;
    }
}



uint8_t rgu_game_run(rgu_game *self, char *name[2],
                     uint8_t lookAhead[2], int16_t *score)
{
    if (self)
    {
        rgu_tile_t winner = NONE;
        char action = 0;
        uint8_t moves = 0, quit = 0;
        uint8_t isAI[2], benchmarking = 0;
        
        /* AI benchmarking mode.
         * `benchmarking = 1` suppresses most print messages. */
        if (name && lookAhead && score)
            isAI[0] = isAI[1] = benchmarking = 1;

        if (!benchmarking)
        {
            printf(">>> Welcome to the Royal Game of Ur <<<\n\n");

            uint8_t i;
            for (i=0; i<2; i++)
            {
                printf("What is your name, player %s? >",
                        (i == 0 ? "one" : "two"));
                scanf(STRFMT, name[i]);
                
                action = 0;
                while (!(action == 'y' || action == 'n'))
                {
                    printf("Is %s an AI? (y/n) >", name[i]);
                    scanf(" %c", &action);

                    if (action == 'y')
                    {
                        printf("What should the look-ahead of %s be? >", name[i]);
                        scanf("%i", &lookAhead[i]);
                        isAI[i] = 1;
                    }
                    else
                    {
                        isAI[i] = 0;
                        lookAhead[i] = 0;
                    }
                }
            }
        }
        
        /* Display who owns what pieces */
        if (!benchmarking)
        {
            uint8_t i;
            printf("\n%s's Pieces: ", name[0]);
            for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
                printf("%c ", self->board->headA->piece[i]->key);
            printf("\n%s Pieces: ", name[1]);
            for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
                printf("%c ", self->board->headB->piece[i]->key);
            printf("\n");

            printf("\nOn each turn when you're prompted to choose an action, "
                    "input the char of one of your piece's chars on the "
                    "screen, or input \'+\' to add your next piece onto the "
                    "board.\nTo quit early, input capital \'Q\'.\n");
        }

        while (winner == NONE && !quit)
        {
            /* Deep copy torture test
            rgu_board *temp = rgu_board_cpy(self->board);
            rgu_board_del(self->board);
            self->board = temp;
            */
            
            uint8_t playerIndex = (self->turn == ALPHA ? 0 : 1);
            moves = rgu_dice_roll();
            
            if (!benchmarking)
            {
                rgu_board_print(self->board);
                printf("    Utility: %i\n\n",
                        rgu_board_getUtility(self->board));
                printf("=== %s ===\n", name[playerIndex]);
                printf("Dice Roll: %i\n", moves);
            }


            /* Figure out possible actions and their utility value */
            char actionArray[RGU_MAX_ACTIONS];
            int16_t utilityArray[RGU_MAX_ACTIONS];

            uint8_t i;
            for (i=0; i<RGU_MAX_ACTIONS; i++)
            {
                actionArray[i] = 0;
                utilityArray[i] = 0;
            }

            rgu_board_getActions(self->board, self->turn,
                    moves, actionArray, utilityArray);

            if (!benchmarking)
            {
                printf("Possible Actions:  %s\n", actionArray);
                printf("Possible Utility:  ");
                for (i=0; i<RGU_MAX_ACTIONS && actionArray[i]!=0; i++)
                    printf("%i ", utilityArray[i]);
                printf("\n");
            }
            
            rgu_tile_t dest = FAIL;
            /* Only ask to choose action if there is at least one action */
            if (moves > 0 && actionArray[0] != 0)
            {
                while (dest == FAIL && !quit)
                {
                    if (!benchmarking) printf("Choose an action. >");

                    /* If human, do a scanf */
                    if (!isAI[playerIndex])
                    {
                        scanf(" %c", &action);
                    }
                    else
                    {
                        action = rgu_ai(self, moves, lookAhead[playerIndex]);
                        if (!benchmarking) printf("%c\n", action);
                    }
                    
                    switch (action)
                    {
                        case 'Q':
                            quit=1;
                            break;
                        case '+':
                            dest = rgu_board_enterPiece(self->board,
                                    self->turn, moves);
                            break;
                        default:
                            dest = rgu_board_movePiece(self->board,
                                    self->turn, action, moves);
                            break;
                    }
                }
            }
            else
            {
                /* Threw a zero or cannot move any pieces */
                if (!benchmarking) printf("Cannot make any moves!\n");
                
                /* Only pause for 1 second if there's at least one human */
                if (!isAI[0] || !isAI[1]) sleep(1);
            }
            
            if (dest != DOUBLE)
                rgu_game_flipTurn(self);
            else if (!benchmarking)
                printf("Landed on a flower tile. Recieving an extra turn!\n");
            
            if (!benchmarking) printf("\n");
            winner = rgu_board_getWinner(self->board);
        }
        
        if (winner != NONE)
        {
            *score = rgu_board_getUtility(self->board);

            if (!benchmarking)
            {
                rgu_board_print(self->board);
                printf("    Utility: %i\n\n", *score);
                printf(">>> %s wins! <<<\n",
                        (winner == ALPHA ? name[0] : name[1]));
            }
        }
        else if (quit)
        {
            printf("Sorry to see you leave early...\n");
        }
    }
    else
    {
        /* Null pointer input */
        return 0;
    }
}
