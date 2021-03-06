/*  rgu_dice.c
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

#include "rgu/rgu_dice.h"

#include <stdint.h>
#include <stdlib.h>
#include <time.h>



void rgu_dice_seed()
{
    time_t t;
    srand((unsigned) time(&t));
}



uint8_t rgu_dice_roll()
{
    uint8_t sum = 0, dice = 4;

    for (; dice > 0; dice--)
    {
        sum += rand()%2;
    }

    return sum;
}
