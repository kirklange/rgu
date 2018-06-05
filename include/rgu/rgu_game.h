/** @file       rgu_game.h
 *  @brief      Board structure and functions.
 *  
 *  <!-------------------------------------------------------------------------
 *  Copyright (c) 2018 Kirk Lange <gitlab.com/kirklange>
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

#ifndef RGU_GAME_H
#define RGU_GAME_H

#ifdef __cplusplus
extern "C"
{
#endif



#include "rgu/rgu_board.h"
#include "rgu/rgu_piece.h"

#include <stdint.h>



/**
 *  @brief      The game!
 *  @details    GAME DESCRIPTION.
 */
typedef struct rgu_game
{
    rgu_board      *board;
    rgu_piece_t     turn;
}
rgu_game;



rgu_game*   rgu_game_new();
rgu_game*   rgu_game_cpy(rgu_game *orig);
uint8_t     rgu_game_del(rgu_game *self);

uint8_t     rgu_game_flipTurn(rgu_game *self);
uint8_t     rgu_game_run(rgu_game *self, char *name[2],
                         uint8_t lookAhead[2], int16_t *score);



#ifdef __cplusplus
}
#endif

#endif /* RGU_GAME_H */
