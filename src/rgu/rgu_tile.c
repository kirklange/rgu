/*  rgu_tile.c
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

#include "rgu/rgu_tile.h"

#include <stdint.h>



rgu_tile* rgu_tile_new(rgu_tile *nextA, rgu_tile *nextB, rgu_tile_t type)
{
    rgu_tile *self = (rgu_tile*) malloc(sizeof(rgu_tile));
    self->nextA = nextA;
    self->nextB = nextB;
    self->type = type;
    self->piece = calloc(RGU_PIECES_PER_PLAYER, sizeof(rgu_piece*));
    return self;
}



rgu_tile* rgu_tile_cpy(rgu_tile *orig)
{
    if (orig)
    {
        rgu_tile *copy = (rgu_tile*) malloc(sizeof(rgu_tile));
        copy->nextA = orig->nextA;
        copy->nextB = orig->nextB;
        copy->type = orig->type;
        copy->piece = calloc(RGU_PIECES_PER_PLAYER, sizeof(rgu_piece*));

        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (orig->piece[i]) copy->piece[i] = rgu_piece_cpy(orig->piece[i]);
        }

        return copy;
    }
    else
    {
        /* Null pointer non-sense */
        return 0;
    }
}



uint8_t rgu_tile_del(rgu_tile *self)
{
    if (self)
    {
        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (self->piece[i]) rgu_piece_del(self->piece[i]);
        }

        free(self->piece);
        free(self);
    }
    else
    {
        /* Cannot free null pointer. */
        return 0;
    }
}



uint8_t rgu_tile_getPieceCount(rgu_tile *self)
{
    if (self)
    {
        uint8_t i, count;
        for (i=0, count=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (self->piece[i]) count++;
        }
        return count;
    }
    else
    {
        /* Nonsensical parameters */
        return 0;
    }
}



rgu_piece* rgu_tile_getPieceAny(rgu_tile *self)
{
    if (self)
    {
        rgu_piece *voila = 0;
        
        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (self->piece[i])
            {
                voila = self->piece[i];
                break;
            }
        }

        /* If never found this will return 0 */
        return voila;
    }
    else
    {
        /* Nonsensical parameter */
        return 0;
    }
}



rgu_piece* rgu_tile_getPieceKey(rgu_tile *self, char key)
{
    if (self && key)
    {
        rgu_piece *voila = 0;
        
        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (self->piece[i])
            {
                if (self->piece[i]->key == key)
                {
                    voila = self->piece[i];
                    break;
                }
            }
        }

        /* If never found this will return 0 */
        return voila;
    }
    else
    {
        /* Nonsensical parameters */
        return 0;
    }
}




uint8_t rgu_tile_addPiece(rgu_tile *self, rgu_piece *piece)
{
    uint8_t success;

    if (self && piece)
    {
        uint8_t i;
        success = 0;

        switch (self->type)
        {
            /* Can have multiple piece on the head or tail */
            case HEAD:
            case TAIL:
                for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
                {
                    if (self->piece[i] == 0)
                    {
                        self->piece[i] = piece;
                        success = 1;
                        break;
                    }
                }
                break;
            /* Can only have one piece on non-head and non-tail tiles */
            case NORMAL:
            case DOUBLE:
                if (self->piece[0] == 0)
                {
                    self->piece[0] = piece;
                    success = 1;
                }
                break;
        }
    }
    else
    {
        /* Nonsensical parameters */
        success = 0;
    }
    
    return success;
}



uint8_t rgu_tile_removePiece(rgu_tile *self, rgu_piece *piece)
{
    uint8_t success;

    if (self && piece)
    {
        success = 0;

        uint8_t i;
        for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        {
            if (self->piece[i] == piece)
            {
                self->piece[i] = 0;
                success = 1;
                break;
            }
        }
    }
    else
    {
        /* Nonsensical parameters */
        success = 0;
    }

    return success;
}
