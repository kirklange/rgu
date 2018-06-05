/** @file       test_ai.c
 *  @brief      Royal Game of Ur AI benchmarking.
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

#include "rgu/rgu_game.h"

#include <stdint.h>
#include <stdio.h>
#include <math.h>



int main(int argc, char *argv[])
{
    printf("RGU AI Benchmark\n\n");

    const uint8_t GAMES = 20;
    const char *NAME[2] = {"Galileo", "Simplicio"};

    uint8_t i, j, k;
    for (i=0; i<4; i++)
    {
        for (j=0; j<=i; j++)
        {
            printf("== %s: %i -- %s: %i ==\n", NAME[0], i, NAME[1], j);
            uint8_t lookAhead[2] = {i, j};
            int16_t score[GAMES];
            float average = 0, stddev = 0;
            
            printf("Outcomes:");
            for (k=0; k<GAMES; k++)
            {
                rgu_game *game = rgu_game_new();
                rgu_game_run(game, NAME, lookAhead, &score[k]);
                rgu_game_del(game);

                average += score[k];
                printf(" %i", score[k]);
            }

            /* Calculate average and standard deviation */
            average /= (float) GAMES;
            for (k=0; k<GAMES; k++)
                stddev += abs(score[k] - (int16_t) average);
            stddev /= (float) GAMES;
            
            printf("\nAverage: %.1f\n", average);
            printf("Std Dev: %.1f\n\n", stddev);
        }
    }

    return 0;
}
