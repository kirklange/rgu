/*  rgu_piece.c
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

#include "rgu/rgu_piece.h"



rgu_piece* rgu_piece_new(rgu_piece_t owner, char key)
{
    rgu_piece *self = (rgu_piece*) malloc(sizeof(rgu_piece));
    self->owner = owner;
    self->key = key;
    return self;
}



rgu_piece* rgu_piece_cpy(rgu_piece *orig)
{
    if (orig)
    {
        rgu_piece *copy = (rgu_piece*) malloc(sizeof(rgu_piece));
        copy->owner = orig->owner;
        copy->key = orig->key;
        return copy;
    }
    else
    {
        /* Cannot free null pointer. */
        return 0;
    }
}



uint8_t rgu_piece_del(rgu_piece *self)
{
    if (self)
    {
        free(self);
    }
    else
    {
        /* Cannot free null pointer. */
        return 0;
    }
}
