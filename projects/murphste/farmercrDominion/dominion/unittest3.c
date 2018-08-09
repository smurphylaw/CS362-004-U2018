// Testing buyCard()

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
    
    printf("Testing: buyCard()\n\n");
    
    // Clear the game state
    memset(&state, 23, sizeof(struct gameState));
    
    // Initalize Game: 2 players, seed of 1000
    initializeGame(numPlayer, k, seed, &state);
    
    // Set 0 as the numbuys player have
    printf("NumBuy = 0\n");
    printf("Game should NOT allow you to buy a card due to insufficient numBuys\n");
    state.numBuys = 0;
    assertTrue(buyCard(3, &state), -1);
    
    // Set numbuy larger than 1
    printf("NumBuy = 3\n");
    printf("Game should let you purchase a card\n");
    state.numBuys = 3;
    assertTrue(buyCard(5, &state), 0);
    
    // Set coins to 0
    printf("Coin = 0\n");
    printf("Game should NOT allow you to buy a card due to insufficient fund\n");
    state.coins = 0;
    assertTrue(buyCard(3, &state), -1);
    
    // Give coins a nice number to make purchases
    printf("Coin = 50\n");
    printf("Game should allow you to buy a card\n");
    state.numBuys = 5;
    state.coins = 50;
    assertTrue(buyCard(3, &state), 0);
    
    if (fail == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
    }
    
    return 0;
}
