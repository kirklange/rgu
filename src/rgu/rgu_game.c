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



rgu_game* rgu_game_new()
{
    rgu_game *self = (rgu_game*) malloc(sizeof(rgu_game));

    self->board = rgu_board_new();
    self->turn = rand()%2 == 0 ? ALPHA : BRAVO;

    rgu_dice_seed();

    return self;
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



uint8_t rgu_game_run(rgu_game *self)
{
    if (self)
    {
        rgu_tile_t winner = NONE;
        char nameAlpha[STRLEN], nameBravo[STRLEN], action;
        uint8_t moves = 0, quit = 0;

        printf(">>> Welcome to the Royal Game of Ur <<<\n\n");

        printf("What is your name, player one? >");
        scanf(STRFMT, nameAlpha);
        printf("And what about you, player two? >");
        scanf(STRFMT, nameBravo);
        
        /* Display who owns what pieces */
        {
            uint8_t i;
            printf("\n%s's Pieces: ", nameAlpha);
            for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
                printf("%c ", self->board->headA->piece[i]->key);
            printf("\n%s Pieces: ", nameBravo);
            for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
                printf("%c ", self->board->headB->piece[i]->key);
            printf("\n");
        }

        printf("\nOn each turn when you're prompted to choose an action, "
                "input the char of one of your piece's chars on the screen, "
                "or input \'+\' to add your next piece onto the board.\n"
                "To quit early, input capital \'Q\'.\n");

        while (winner == NONE && !quit)
        {
            rgu_board_print(self->board);
            moves = rgu_dice_roll();

            printf("=== %s ===\n", (self->turn == ALPHA ?
                        nameAlpha : nameBravo));
            printf("Dice Roll: %i\n", moves);

            rgu_tile_t dest = FAIL;
            if (moves > 0)
            {
                while (dest == FAIL && !quit)
                {
                    printf("Choose an action. >");
                    scanf(" %c", &action);
                    
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
                /* Threw a zero */
                printf("Unlucky throw!\n");
            }
            
            if (dest != DOUBLE)
            {
                self->turn = (self->turn == ALPHA ? BRAVO : ALPHA);
            }
            else
            {
                printf("Landed on a flower tile. Recieving an extra turn!\n");
            }
            
            printf("\n");
            winner = rgu_board_getWinner(self->board);
        }
        
        if (winner != NONE)
        {
            printf(">>> %s wins! <<<\n",
                    (winner == ALPHA ? nameAlpha : nameBravo));
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
