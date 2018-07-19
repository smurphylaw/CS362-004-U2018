// Testing updateCoins()

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>

int fail;

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
    
    int i;
    int seed = 1000;
    int player = 0;
    int numPlayer = 2;
    int bonus = 0;
    
    struct gameState state;
    
    int handCount;
    int maxHandCount = 5;
    
    // Arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    
    printf("Testing: updateCoins()\n\n");
    
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    
    for (handCount = 1; handCount <= maxHandCount; handCount++) {
        
        // Clear the game state
        memset(&state, 23, sizeof(struct gameState));
    
        // Initalize Game: 2 players, seed of 1000
        initializeGame(numPlayer, k, seed, &state);
    
        // Set the number of cards on hand
        state.handCount[player] = handCount;
    
        // Set all the cards to copper
        memcpy(state.hand[player], coppers, sizeof(int) * handCount);
        updateCoins(player, &state, bonus);

        printf("Copper Coins = %d, Expected = %d\n", state.coins, handCount * 1 + bonus);

        // Check if the number of coins is correct
        assertTrue(state.coins, handCount * 1 + bonus);
    
        // Set all the cards to silver
        memcpy(state.hand[player], silvers, sizeof(int) * handCount);
        updateCoins(player, &state, bonus);

        printf("Silver Coins = %d, Expected = %d\n", state.coins, handCount * 2 + bonus);
    
        // Check if the number of coins is correct
        assertTrue(state.coins, handCount * 2 + bonus);
    
        // Set all the cards to gold
        memcpy(state.hand[player], golds, sizeof(int) * handCount);
        updateCoins(player, &state, bonus);

        printf("Gold Coins = %d, Expected = %d\n", state.coins, handCount * 3 + bonus);

        // Check if the number of coins is correct
        assertTrue(state.coins, handCount * 3 + bonus);
        
        // Increase bonus
        bonus++;
    }
    
    if (fail == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
    }
    
    return 0;
}
