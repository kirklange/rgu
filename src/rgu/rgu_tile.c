/*  rgu_tile.c
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

#include "rgu/rgu_tile.h"



rgu_tile* rgu_tile_new(rgu_tile *nextA, rgu_tile *nextB, rgu_tile_t type)
{
    rgu_tile *self = (rgu_tile*) malloc(sizeof(rgu_tile));
    self->nextA = nextA;
    self->nextB = nextB;
    self->type = type;
    return self;
}



uint8_t rgu_tile_del(rgu_tile *self)
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
