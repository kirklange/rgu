/** @file       rgu_tile.h
 *  @brief      Board tile enum and struct.
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

#ifndef RGU_TILE_H
#define RGU_TILE_H

#ifdef __cplusplus
extern "C"
{
#endif



#include "rgu/rgu_piece.h"

#include <stdint.h>



/**
 *  @brief      The four (technically two) types of tiles on an RGU board.
 *  @details    The starting and ending tiles are where the pieces reside when
 *              they aren't being rendered off the board. For our convenience,
 *              we will treat them like as if they are still on tiles, albeit
 *              very special tiles.
 */
typedef enum rgu_tile_t
{
    /** Where pieces are staged before getting placed on the board.
     *  When a piece gets kicked off the board, it's reset to here. */
    HEAD,

    /** Boring regular old tile. */
    NORMAL,

    /** Landing on this tile grants an extra turn. */
    DOUBLE,

    /** After a piece has completed its tour of the board, it lives here. */
    TAIL
}
rgu_tile_t;



/**
 *  @brief      Struct for describing the tiles on the game board.
 *  @details    This is sort of like a singly linked list, but because each
 *              player takes a slightly different path along the board, there
 *              are two `next` pointers, one for each player.
 *
 *              If this tile is of type `HEAD` or `TAIL`, up to seven pieces
 */
typedef struct rgu_tile
{
    /** Next tile for player one. */
    struct rgu_tile     *nextA;

    /** Next tile for player two. */
    struct rgu_tile     *nextB;

    /** This tile's type. */
    rgu_tile_t           type;
    
    /** Array of pointers to the game pieces that are on this tile. If no
     *    piece is on this tile, `piece` will point to `0`. */
    rgu_piece          **piece;
}
rgu_tile;



rgu_tile*   rgu_tile_new(rgu_tile *nextA, rgu_tile *nextB, rgu_tile_t type);
uint8_t     rgu_tile_del(rgu_tile *self);

rgu_tile*   rgu_tile_getPiece(rgu_tile *self, char key);
uint8_t     rgu_tile_addPiece(rgu_tile *self, rgu_piece *piece);
uint8_t     rgu_tile_removePiece(rgu_tile *self, rgu_piece *piece);



#ifdef __cplusplus
}
#endif

#endif /* RGU_TILE_H */
