/*  rgu_ai.c
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

#include "rgu/rgu_ai.h"
#include "rgu/rgu_board.h"
#include "rgu/rgu_game.h"
#include "rgu/rgu_piece.h"
#include "rgu/rgu_tile.h"

#include <stdio.h>
#include <stdlib.h>



char rgu_ai(rgu_game *game, uint8_t moves, uint8_t lookAhead)
{
    if (game && moves > 0)
    {
        /* Get all possible actions and their utility value */
        char actionChoice = 0;
        uint8_t i, actions = 0;
        char actionArray[RGU_MAX_ACTIONS];
        int16_t utilityArray[RGU_MAX_ACTIONS];
        for (i=0; i<RGU_MAX_ACTIONS; i++)
            actionArray[i] = utilityArray[i] = 0;

        rgu_board_getActions(game->board, game->turn,
                moves, actionArray, utilityArray);
        
        /* We could have up to `RGU_MAX_ACTIONS`, but figure out how many
         *   actual options we have. Store this in `actions` */
        for (i=0; i<RGU_MAX_ACTIONS && actionArray[i]!=0; i++, actions++);

        /* If `0`, be a random agent */
        if (lookAhead == 0)
        {
            actionChoice = actionArray[ rand()%actions ];
        }
        /* If lookAhead > 0, don't be random */
        else
        {
        }

        return actionChoice;
    }
    else
    {
        /* Nonsense inputs */
        return 0;
    }
}
