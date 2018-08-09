// Testing Adventure Card

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
    struct gameState testState;
    
    int handpos = 0;
    int bonus = 0;
    int discard = 1;
    
    int i;
    int treasure;
    int testTreasure;
    
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    
//    int duchy, estate, province;
    
    printf("Testing: Adventure Card\n\n");
    
    // Clear the game state
    memset(&state, 23, sizeof(struct gameState));
    memset(&testState, 23, sizeof(struct gameState));
    
    // Initalize Game: 2 players, seed of 1000
    initializeGame(numPlayer, k, seed, &state);
    
    // Copy the game state to test case
    memcpy(&testState, &state, sizeof(struct gameState));
    
    printf("**** Current Player Test Results **** \n");
    cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);

    // Current Player should get 2 treasure cards
    printf("Current Player gained 2 treasure cards\n");
    
    treasure = 0;
    testTreasure = 0;
    
    for (i = 0; i < testState.handCount[0]; i++) {
        int cardDrawn = state.hand[0][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            treasure++;
        }
    }
    
    for (i = 0; i < testState.handCount[0]; i++) {
        int cardDrawn = testState.hand[0][i];
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
            testTreasure++;
        }
    }
    
    printf("Treasure Card = %d, Expected = %d\n", testTreasure, treasure + 2);
    assertTrue(testTreasure, treasure + 2);
    
    // Current Player should get 2 cards
    printf("Current Player gained 2 cards\n");
    printf("Hand Count = %d, Expected = %d\n", testState.handCount[0], state.handCount[0] + 2 - discard);
    assertTrue(testState.handCount[0], state.handCount[0] + 2 - discard);
    
    printf("**** Other Player State Test Results **** \n");
    // Check the Player 2's Hand Count
    printf("Hand Count = %d, Expected = %d\n", testState.handCount[1], state.handCount[1]);
    assertTrue(testState.handCount[1], state.handCount[1]);
    
    // Check the Player 2's Deck Count
    printf("Deck Count = %d, Expected = %d\n", testState.deckCount[1], state.deckCount[1]);
    assertTrue(testState.deckCount[1], state.deckCount[1]);
    
    // Check the Player 2's Coin Count
    printf("Coin Count = %d, Expected = %d\n", testState.coins, state.coins);
    assertTrue(testState.coins, state.coins);
    
    // Check State Change in other card piles
    printf("**** Other Card Piles State Test Results **** \n");
    
    // Check the Victory Pile
    printf("* Victory Pile *\n");
    printf("Duchy:\n");
    printf("Duchy Count = %d, Expected = %d\n", testState.supplyCount[duchy], state.supplyCount[duchy]);
    assertTrue(testState.supplyCount[duchy], state.supplyCount[duchy]);
    
    printf("Estate:\n");
    printf("Estate Count = %d, Expected = %d\n", testState.supplyCount[estate], state.supplyCount[estate]);
    assertTrue(testState.supplyCount[estate], state.supplyCount[estate]);
    
    printf("Province:\n");
    printf("Province Count = %d, Expected = %d\n", testState.supplyCount[province], state.supplyCount[province]);
    assertTrue(testState.supplyCount[province], state.supplyCount[province]);
    
    // Check the Kingdom Pile
    printf("* Kingdom Pile *\n");
    for (i = 0; i < 10; i++) {
        printf("Kingdom #%d = %d, Expected = %d\n", i, testState.supplyCount[k[i]], state.supplyCount[k[i]]);
        assertTrue(testState.supplyCount[k[i]], state.supplyCount[k[i]]);
    }
    
    if (fail == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
    }
    
    return 0;
}
