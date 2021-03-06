/** @file       rgu_dice.h
 *  @brief      Dice functions.
 *  
 *  <!-------------------------------------------------------------------------
 *  Copyright (c) 2018 Kirk Lange <github.com/kirklange>
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

#ifndef RGU_DICE_H
#define RGU_DICE_H

#ifdef __cplusplus
extern "C"
{
#endif



#include <stdint.h>



/**
 *  @brief      Seed the pseudo-random number generator.
 *  @details    Only needs to be called once in the program. Its effect
 *              is global.
 */
void rgu_dice_seed();

/**
 *  @brief      Roll the four tetrahedral dice and return the sum.
 *  @return     The sum of the four dice. Range: [0,4]
 *  @details    Due to the nature of multi-dice rolls, the distribution of
 *              this function's output is non-uniform.
 */
uint8_t rgu_dice_roll();



#ifdef __cplusplus
}
#endif

#endif /* RGU_DICE_H */
