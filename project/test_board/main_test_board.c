/** @file       main_test_board.c
 *  @brief      Royal Game of Ur board initialization test.
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

#include <stdint.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
    printf("RGU Board Test\n");
    
    rgu_board *board = rgu_board_new();

    printf("Board Linked List Map\n");
    printf("  (See if you can spot the center tiles of matching addresses.)\n");
    rgu_tile *iter;
    printf("  Path A: ");
    for (iter=board->headA; iter; iter=iter->nextA)
        printf("0x%x ", iter);
    printf("\n  Path B: ");
    for (iter=board->headB; iter; iter=iter->nextB)
        printf("0x%x ", iter);
    printf("\n");

    printf("Staging Tile Pieces Count\n");
    printf("  Player A: %u\n", rgu_tile_countPieces(board->headA));
    printf("  Player B: %u\n", rgu_tile_countPieces(board->headB));
   
    printf("Game Piece Key Assignments\n");
    uint8_t i;
    printf("  Player A: ");
    for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        printf("%c ", board->headA->piece[i]->key);
    printf("\n  Player B: ");
    for (i=0; i<RGU_PIECES_PER_PLAYER; i++)
        printf("%c ", board->headB->piece[i]->key);
    printf("\n");

    rgu_board_print(board);
    
    /*
    char key;
    uint8_t moves, succA, succB;
    while (1)
    {
        printf("Select a piece to move ('Q' to quit): ");
        scanf("%c", &key);
        if (key == 'Q') break;
        printf("Amount of tiles to move forward: ");
        scanf("%u", &moves);

        succA = rgu_board_movePiece(board, ALPHA, key, moves);
        if (!succA) succB = rgu_board_movePiece(board, BRAVO, key, moves);

        if (succA || succB)
            printf("Successfully moved %c.\n", key);
        else
            printf("FAILED to move %c.\n", key);

        scanf("%c", &key);
        rgu_board_print(board);
    }
    */

    rgu_board_del(board);

    return 0;
}
