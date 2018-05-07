/*  rgu_board.c
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

#include "rgu/rgu_board.h"
#include "rgu/rgu_piece.h"
#include "rgu/rgu_tile.h"



rgu_board* rgu_board_new()
{
    rgu_board *self = (rgu_board*) malloc(sizeof(rgu_board));

    /* Link to section of video with animations of the pieces moving around
     *   the board: <https://youtu.be/WZskjLq040I?t=3m49s>. */

    /* Tail-end tiles */
    rgu_tile *tailA = rgu_tile_new(0, 0, TAIL);
    rgu_tile *lastA = rgu_tile_new(tailA, 0, DOUBLE);
    rgu_tile *botmA = rgu_tile_new(lastA, 0, NORMAL);

    rgu_tile *tailB = rgu_tile_new(0, 0, TAIL);
    rgu_tile *lastB = rgu_tile_new(0, tailB, DOUBLE);
    rgu_tile *botmB = rgu_tile_new(0, lastB, NORMAL);
    
    /* Center tiles */
    rgu_tile *cent0 = rgu_tile_new(botmA, botmB, NORMAL);
    rgu_tile *cent1 = rgu_tile_new(cent0, cent0, NORMAL);
    rgu_tile *cent2 = rgu_tile_new(cent1, cent1, NORMAL);
    rgu_tile *cent3 = rgu_tile_new(cent2, cent2, NORMAL);
    rgu_tile *cent4 = rgu_tile_new(cent3, cent3, DOUBLE);
    rgu_tile *cent5 = rgu_tile_new(cent4, cent4, NORMAL);
    rgu_tile *cent6 = rgu_tile_new(cent5, cent5, NORMAL);
    rgu_tile *cent7 = rgu_tile_new(cent6, cent6, NORMAL);

    /* Head-end tiles */
    rgu_tile *topA = rgu_tile_new(cent7, 0, DOUBLE);
    rgu_tile *thrA = rgu_tile_new(topA, 0, NORMAL);
    rgu_tile *secA = rgu_tile_new(thrA, 0, NORMAL);
    rgu_tile *firA = rgu_tile_new(secA, 0, NORMAL);
    rgu_tile *headA = rgu_tile_new(firA, 0, HEAD);

    rgu_tile *topB = rgu_tile_new(0, cent7, DOUBLE);
    rgu_tile *thrB = rgu_tile_new(0, topB, NORMAL);
    rgu_tile *secB = rgu_tile_new(0, thrB, NORMAL);
    rgu_tile *firB = rgu_tile_new(0, secB, NORMAL);
    rgu_tile *headB = rgu_tile_new(0, firB, HEAD);

    /* Create the pieces */
    uint8_t i;
    for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
    {
        headA->piece[i] = rgu_piece_new(ALPHA, (char) ('a'+i));
        headB->piece[i] = rgu_piece_new(BRAVO, (char)
                                        (('z'-RGU_PIECES_PER_PLAYER+1)+i));
    }
    
    /* Set self's heads, then return */
    self->headA = headA;
    self->headB = headB;

    return self;
}



uint8_t rgu_board_del(rgu_board *self)
{
    if (self)
    {
        /* Free the pieces */
        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            rgu_piece_del(self->headA->piece[i]);
            rgu_piece_del(self->headB->piece[i]);
        }

        /* Free the tiles */
        rgu_tile *iterA = self->headA,
                 *iterB = self->headB,
                 *nextA = 0,
                 *nextB = 0;
        
        do
        {
            nextA = iterA->nextA;
            nextB = iterB->nextB;

            rgu_tile_del(iterA);
            /* No need to free the center tiles twice. */
            if (iterA != iterB) rgu_tile_del(iterB);

            iterA = nextA;
            iterB = nextB;
        }
        while(iterA && iterB);

        free(self);
    }
    else
    {
        /* Cannot free null pointer. */
        return 0;
    }
}



uint8_t rgu_board_movePiece(rgu_board *self, char keyPress, uint8_t moves)
{
}
