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

#include <stdio.h>





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
    
    /* Set self's heads */
    self->headA = headA;
    self->headB = headB;

    return self;
}



rgu_board* rgu_board_cpy(rgu_board *orig)
{
    if (orig)
    {
        rgu_board *copy = (rgu_board*) malloc(sizeof(rgu_board));

        copy->headA = rgu_tile_cpy(orig->headA);
        copy->headB = rgu_tile_cpy(orig->headB);

        /* Copy the tiles (deep copy) */
        rgu_tile *origIterA = orig->headA,
                 *origIterB = orig->headB,
                 *copyIterA = copy->headA,
                 *copyIterB = copy->headB;
        
        while ((origIterA = origIterA->nextA) &&
               (origIterB = origIterB->nextB))
        {
            copyIterA->nextA = rgu_tile_cpy(origIterA);
            /* Don't copy center row twice */
            if (origIterA != origIterB)
                copyIterB->nextB = rgu_tile_cpy(origIterB);
            else
                copyIterB->nextB = copyIterA->nextA;

            copyIterA = copyIterA->nextA;
            copyIterB = copyIterB->nextB;
        }

        return copy;
    }
    else
    {
        return 0;
    }
}



uint8_t rgu_board_del(rgu_board *self)
{
    if (self)
    {
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



rgu_tile_t rgu_board_movePiece(rgu_board *self,
        rgu_piece_t player, char key, uint8_t moves)
{
    uint8_t success;
    rgu_tile_t tile_type;

    if (self && moves>=0 && key>=0)
    {
        rgu_tile *tile_orig = player==ALPHA ? self->headA : self->headB;
        rgu_piece *piece = 0;
        uint8_t i;
        
        /* Try looking for the game piece with this key input */
        do
        {
            /* No point in trying to move a piece that passed the finish */
            if (tile_orig->type == TAIL) break;
            
            /* Break if piece!=0 (i.e. we found it) */
            if (piece = rgu_tile_getPieceKey(tile_orig, key))
            {
                rgu_tile_removePiece(tile_orig, piece);
                break;
            }

            tile_orig = player==ALPHA ? tile_orig->nextA : tile_orig->nextB;
        }
        while (tile_orig && !piece);

        /* If found piece, now actually move it */
        if (piece)
        {
            rgu_tile *tile_attempt = tile_orig;

            /* Get the destination tile.
             * Abandon loop if we're starting to move off the board. */
            for (; moves>0 && tile_attempt; moves--)
            {
                tile_attempt = player==ALPHA ?
                    tile_attempt->nextA : tile_attempt->nextB;
            }
            
            /* If we got a valid destination tile */
            if (moves == 0 && tile_attempt)
            {
                /* Check if there is already an occupying piece */
                rgu_piece *occupant = rgu_tile_getPieceAny(tile_attempt);
                if (occupant)
                {
                    /* Kick off if it's of the enemy and not on safe tile */
                    if (occupant->owner != piece->owner &&
                            tile_attempt->type != DOUBLE)
                    {
                        /* Send occupant back to its own head tile */
                        rgu_tile_removePiece(tile_attempt, occupant);
                        rgu_tile_addPiece(
                                occupant->owner == ALPHA ?
                                    self->headA : self->headB,
                                occupant);
                    }
                }
                
                /* `success` could be set to zero here if stuff goes wrong */
                success = rgu_tile_addPiece(tile_attempt, piece);
            }
            else
            {
                success = 0;
            }
            
            /* All successful scenarios go through here */
            if (success)
            {
                /* SUCCESS! Set `tile_type` */
                tile_type = tile_attempt->type;
            }
            else
            {
                /* Cannot move off the board or on top of other piece.
                 * Replace tile back to its original spot. */
                rgu_tile_addPiece(tile_orig, piece);
                tile_type = FAIL;
            }
        }
        else
        {
            /* Could not find piece with key input `key` */
            tile_type = FAIL;
        }
    }
    else
    {
        /* Nonsensical parameters (such as null pointer) */
        tile_type = FAIL;
    }

    return tile_type;
}



rgu_tile_t rgu_board_enterPiece(rgu_board *self,
        rgu_piece_t player, uint8_t moves)
{
    rgu_tile_t tile_type;

    if (self && moves>=0)
    {
        rgu_tile *tile = player==ALPHA ? self->headA : self->headB;
        tile_type = FAIL;

        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (tile->piece[i])
            {
                tile_type = rgu_board_movePiece(self, player,
                        tile->piece[i]->key, moves);
                break;
            }
        }
    }
    else
    {
        /* Null pointer or rolled a zero */
        tile_type = FAIL;
    }

    return tile_type;
}



uint8_t rgu_board_getPossible(rgu_board *self, char *inputs)
{
    uint8_t success;

    if (self && inputs)
    {
        
    }
    else
    {
        /* Null pointer inputs */
        success = 0;
    }

    return success;
}



rgu_tile_t rgu_board_getWinner(rgu_board *self)
{
    rgu_tile_t winner;

    if (self)
    {
        rgu_tile *iterA = self->headA,
                 *iterB = self->headB;

        /* Iterate to the tail tiles */
        while (iterA->type != TAIL) iterA = iterA->nextA;
        while (iterB->type != TAIL) iterB = iterB->nextB;

        if (rgu_tile_countPieces(iterA) == RGU_PIECES_PER_PLAYER)
            winner = ALPHA;
        else if (rgu_tile_countPieces(iterB) == RGU_PIECES_PER_PLAYER)
            winner = BRAVO;
        else
            winner = NONE;
    }
    else
    {
        /* Nonsensical parameters (such as null pointer) */
        winner = NONE;
    }

    return winner;
}



void rgu_board_print(rgu_board *self)
{
    rgu_tile *iterA = self->headA,
             *iterB = self->headB;

    /*               0    5  8  11 14 17 20 23 26
     *               v    v  v  v  v  v  v  v  v   */
    char row0[30] = "    { }[ ][ ][ ]<#--#<{ }[ ]\n",
         row1[30] = "    [ ][ ][ ]{ }[ ][ ][ ][ ]\n",
         row2[30] = "    { }[ ][ ][ ]<#--#<{ }[ ]\n";
    /*                   head-end        tail-end  */
    
    /* Player A starts and ends on the bottom (row 2).
     * Conversely, player B starts and ends on the top (row 0). */

    /* Draw head tile piece counts */
    const uint8_t N;
    char buffer[4];
    sprintf(buffer, "%u", rgu_tile_countPieces(iterA));
    row2[17] = buffer[0];
    sprintf(buffer, "%u", rgu_tile_countPieces(iterB));
    row0[17] = buffer[0];

    iterA = iterA->nextA;
    iterB = iterB->nextB;
    
    /* Draw head-end */
    uint8_t i;
    for (i=0; i<4; i++)
    {
        row2[14 - (i*3)] = iterA->piece[0] ? iterA->piece[0]->key : ' ';
        row0[14 - (i*3)] = iterB->piece[0] ? iterB->piece[0]->key : ' ';

        iterA = iterA->nextA;
        iterB = iterB->nextB;
    }
    
    /* Draw center (all of row 1) */
    for (i=0; i<8; i++)
    {
        row1[5 + (i*3)] = iterA->piece[0] ? iterA->piece[0]->key : ' ';
        
        iterA = iterA->nextA;
        iterB = iterB->nextB;
    }

    /* Draw tail-end */
    for (i=0; i<2; i++)
    {
        row2[26 - (i*3)] = iterA->piece[0] ? iterA->piece[0]->key : ' ';
        row0[26 - (i*3)] = iterB->piece[0] ? iterB->piece[0]->key : ' ';

        iterA = iterA->nextA;
        iterB = iterB->nextB;
    }

    /* Draw tail tile piece counts */
    sprintf(buffer, "%u", rgu_tile_countPieces(iterA));
    row2[20] = buffer[0];
    sprintf(buffer, "%u", rgu_tile_countPieces(iterB));
    row0[20] = buffer[0];

    printf("\n%s%s%s\n", row0, row1, row2);
}
