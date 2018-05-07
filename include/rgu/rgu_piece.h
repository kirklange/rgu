/** @file       rgu_piece.h
 *  @brief      Game piece enum and struct.
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

#ifndef RGU_PIECE_H
#define RGU_PIECE_H

#ifdef __cplusplus
extern "C"
{
#endif



/** 
 *  @brief      The number of pieces each player has.
 */
#define RGU_PIECES_PER_PLAYER 7



/**
 *  @brief      Game piece enum describing who owns the piece.
 */
typedef enum rgu_piece_t
{
    ALPHA,  /** Owned by player one. */
    BRAVO   /** Owned by player two. */
}
rgu_piece_t;



/**
 *  @brief      Struct for describing the tiles on the game board.
 *  @details    This is sort of like a singly linked list, but because each
 *              player takes a slightly different path along the board, there
 *              are two `next` pointers, one for each player.
 */
typedef struct rgu_piece
{
    rgu_piece_t     owner;  /** This tile's type. */
    char            key;    /** Keyboard input for moving the piece. */
}
rgu_piece;



#ifdef __cplusplus
}
#endif

#endif /* RGU_PIECE_H */