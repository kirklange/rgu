/*  rgu_ai.c
 *
 *  <!-------------------------------------------------------------------------
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
 *  -------------------------------------------------------------------------->
 */

#include "rgu/rgu_ai.h"
#include "rgu/rgu_board.h"
#include "rgu/rgu_game.h"
#include "rgu/rgu_piece.h"
#include "rgu/rgu_tile.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>



uint8_t rgu_ai_mmab(rgu_game *game, uint8_t moves, uint8_t lookAhead,
                 int16_t alpha, int16_t bravo, int16_t *rValue, uint8_t first);



char rgu_ai(rgu_game *game, uint8_t moves, uint8_t lookAhead)
{
    if (game && moves > 0)
    {
        int16_t rValue;
        if (rgu_ai_mmab(game, moves, lookAhead, INT_MIN, INT_MAX, &rValue, 1))
        {
            return (char) rValue;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        /* Nonsense inputs */
        return 0;
    }
}



/* Minimax with Alpha-"Bravo" Pruning */
uint8_t rgu_ai_mmab(rgu_game *game, uint8_t moves, uint8_t lookAhead,
                 int16_t alpha, int16_t bravo, int16_t *rValue, uint8_t first)
{
    uint8_t success;

    if (game && moves > 0)
    {
        /* The return value `rValue` lives two lives.
         * It either stores the `char` of the move that should be taken,
         *   or it stores the utility value of the current ply.
         * Thank goodness `char` is just a subset of `int`! */

        /* Get all possible actions and their utility value */
        uint8_t i, actions = 0;
        char actionArray[RGU_MAX_ACTIONS];
        int16_t utilityArray[RGU_MAX_ACTIONS];
        for (i=0; i<RGU_MAX_ACTIONS; i++)
            actionArray[i] = utilityArray[i] = 0;

        rgu_board_getActions(game->board, game->turn,
                moves, actionArray, utilityArray);
        
        /* We could have up to `RGU_MAX_ACTIONS`, but figure out how many
         *   actual options we have. Store this in `actions` */
        for (i=0; i<RGU_MAX_ACTIONS && actionArray[i]!=0; i++, actions++);

        /* If `0`, be a random agent */
        if (lookAhead == 0)
        {
            *rValue = actionArray[ rand()%actions ];
            success = 1;
        }
        /* If lookAhead > 0, don't be random */
        else
        {
            /* Test out each action on a copy of the game */
            for (i=0; i<actions; i++)
            {
                rgu_game *gameCopy = rgu_game_cpy(game);
                
                if (gameCopy)
                {
                    rgu_tile_t dest;

                    /* Move it! */
                    if (actionArray[i] == '+')
                        dest = rgu_board_enterPiece(gameCopy->board,
                                gameCopy->turn, moves);
                    else
                        dest = rgu_board_movePiece(gameCopy->board,
                                gameCopy->turn, actionArray[i], moves);
                    
                    /* If mock action was successful */
                    if (dest != FAIL)
                    {
                        if (dest != DOUBLE) rgu_game_flipTurn(gameCopy);

                        /* At plies (`lookAhead`) bottom; simply use
                         *   utility value of this board state */
                        if (lookAhead == 1)
                        {
                            utilityArray[i] =
                                rgu_board_getUtility(gameCopy->board);
                        }
                        else
                        {
                            /* Do recursive call */
                            int16_t temp;
                            if (rgu_ai_mmab(gameCopy, moves, lookAhead-1,
                                            alpha, bravo, &temp, 0))
                            {
                                utilityArray[i] = temp;
                            }
                            else
                            {
                                /* If recursion failed, i.e. if there are no
                                 *   moves that can be taken, then get the
                                 *   utility of the current board state */
                                utilityArray[i] =
                                    rgu_board_getUtility(gameCopy->board);
                            }
                        }
                        
                        /* Unflip turn for following minimax and pruning */
                        if (dest != DOUBLE) rgu_game_flipTurn(gameCopy);

                        /* Pruning logic */
                        if (gameCopy->turn == ALPHA)
                        {
                            if (utilityArray[i] > alpha)
                                alpha = utilityArray[i];
                        }
                        else if (gameCopy->turn == BRAVO)
                        {
                            if (utilityArray[i] < bravo)
                                bravo = utilityArray[i];
                        }
                        
                        rgu_game_del(gameCopy);

                        if (bravo <= alpha) break;
                    }
                }
                else
                {
                    /* Print error message about failed to create game copy */
                }
            } /* End for each action loop */
            
            uint8_t actionIndex = 0;
            /* Find min/max value */
            for (i=0; i<actions; i++)
            {
                if (  (game->turn == ALPHA &&
                         utilityArray[i] > utilityArray[actionIndex]) ||
                      (game->turn == BRAVO &&
                         utilityArray[i] < utilityArray[actionIndex])  )
                {
                    actionIndex = i;
                }
            }
            
            /* If this is the first call, set `rValue` to be the action key */
            if (first)
            {
                *rValue = actionArray[actionIndex];
            }
            else
            {
                *rValue = utilityArray[actionIndex];
            }
            
            success = 1;
        } /* End else lookahead > 0*/
    }
    else
    {
        /* Nonsense inputs */
        success = 0;
    }

    return success;
}
