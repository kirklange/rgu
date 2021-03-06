/** @file       rgu_board.h
 *  @brief      Board structure and functions.
 *  
 *  <!-------------------------------------------------------------------------
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
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

#ifndef RGU_BOARD_H
#define RGU_BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif



#include "rgu/rgu_piece.h"
#include "rgu/rgu_tile.h"

#include <stdint.h>

#define RGU_MAX_ACTIONS RGU_PIECES_PER_PLAYER+1



/**
 *  @brief      The board!
 *  @details    Description of the board.
 */
typedef struct rgu_board
{
    rgu_tile       *headA;
    rgu_tile       *headB;
}
rgu_board;



rgu_board*  rgu_board_new();
rgu_board*  rgu_board_cpy(rgu_board *orig);
uint8_t     rgu_board_del(rgu_board *self);

/**
 *  @brief      Attempt to move a piece a certain amount of moves.
 *  @param      self        Pointer to the board's self.
 *  @param      keyPress    `char` correlating to the piece's `key` struct
 *                            member that you want to move.
 *  @param      moves       The amount of movements you want to try to move.
 *  @return     `0` if cannot move. `1` if successfully moved.
 */
rgu_tile_t  rgu_board_movePiece(rgu_board *self, rgu_piece_t player,
                                char key, uint8_t moves);

/* Attempt to move some piece from head tile onto board. */
rgu_tile_t  rgu_board_enterPiece(rgu_board *self, rgu_piece_t player,
                                 uint8_t moves);

/* Set `actions` to be list of chars of possible moves.
 * We also assume that the max possible amount of actions is equal to the
 *   player's number of tiles plus the '+' action. */
uint8_t     rgu_board_getActions(rgu_board *self, rgu_piece_t player,
                    uint8_t moves, char action[RGU_MAX_ACTIONS],
                    int16_t utility[RGU_MAX_ACTIONS]);
rgu_tile_t  rgu_board_getWinner(rgu_board *self);
int16_t     rgu_board_getUtility(rgu_board *self);

void        rgu_board_print(rgu_board *self);



#ifdef __cplusplus
}
#endif

#endif /* RGU_BOARD_H */
