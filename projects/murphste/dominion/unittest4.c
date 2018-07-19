// Testing isGameOver()

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>

int fail = 0;

// Own assert true function to provide more information than standard C assert
void assertTrue(int a, int b) {
    if (a == b) {
        printf("TEST: PASSED\n\n");
    } else {
        printf("TEST: FAILED\n\n");
        fail++;
    }
}

int main() {
    
    int k[10] = { adventurer, council_room, feast, gardens, mine,
        remodel, smithy, village, baron, great_hall };
    
    int seed = 1000;
    int numPlayer = 2;
    
    struct gameState state;
    
    printf("Testing: isGameOver()\n\n");
    
    // Clear the game state
    memset(&state, 23, sizeof(struct gameState));
    
    // Initalize Game: 2 players, seed of 1000
    initializeGame(numPlayer, k, seed, &state);
    
    // Set number of province cards in stack to 0
    printf("Province = 0\n");
    printf("Game should end since stack is empty\n");
    state.supplyCount[province] = 0;
    assertTrue(isGameOver(&state), 1);
    
    // Set number of province cards in stack to 1
    // and add a supply card for one pile
    printf("Province = 1\n");
    printf("Game should NOT end since stack is NOT empty\n");
    state.supplyCount[province] = 1;
    state.supplyCount[2] = 1;
    assertTrue(isGameOver(&state), 0);
    
    // Set number of supply count to 0 for 3 piles
    printf("Supply Count = 0 for 3 piles\n");
    printf("Game should end\n");
    state.supplyCount[2] = 0;
    state.supplyCount[6] = 0;
    state.supplyCount[20] = 0;
    assertTrue(isGameOver(&state), 1);
    
    // Set number of supply count for 3 piles
    printf("Supply Count = 1 for 3 piles\n");
    printf("Game should NOT end since supply piles are NOT empty\n");
    state.supplyCount[2] = 1;
    state.supplyCount[6] = 1;
    state.supplyCount[20] = 1;
    assertTrue(isGameOver(&state), 0);
    
    if (fail == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
    }
    
    return 0;
}
