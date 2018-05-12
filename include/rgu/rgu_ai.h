/** @file       rgu_ai.h
 *  @brief      The AI function.
 *  
 *  <!-------------------------------------------------------------------------
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
 *  -------------------------------------------------------------------------->
 */

#ifndef RGU_AI_H
#define RGU_AI_H

#ifdef __cplusplus
extern "C"
{
#endif



#include "rgu/rgu_game.h"

#include <stdint.h>



/**
 *  @brief      Get the best move for this turn.
 *  @return     `char` representation of the AI's chosen move.
 *  @details    DETAIL DESCRIPTION... There are annonymous functions being
 *              called behind the scenes. See `rgu_ai.c` for more.
 */
char    rgu_ai(rgu_game *game, uint8_t moves, uint8_t lookAhead);



#ifdef __cplusplus
}
#endif

#endif /* RGU_AI_H */
