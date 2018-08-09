// Testing shuffle()

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
    
    printf("Testing: shuffle()\n");
    
    // Clear the game state
    memset(&state, 23, sizeof(struct gameState));
    
    // Initalize Game: 2 players, seed of 1000
    initializeGame(numPlayer, k, seed, &state);
    
    // Set 0 as the number of cards in deck
    printf("Deck Count = 0\n");
    printf("Game should cannot shuffle due to no cards in deck\n");
    state.deckCount[0] = 0;
    assertTrue(shuffle(0, &state), -1);
    
    // Set 20 as the number of cards in deck
    printf("Deck Count = 20\n");
    printf("Game can shuffle the deck\n");
    state.deckCount[0] = 20;
    shuffle(0, &state);
    assertTrue(state.deckCount[0], 20);
    
    
    if (fail == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
    }
    
    return 0;
}
