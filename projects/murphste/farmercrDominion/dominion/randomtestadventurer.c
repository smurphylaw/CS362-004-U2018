//gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99

// Random Generator for Adventurer Card

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <math.h>

int failCount = 0;
int shuffleFailed = 0;
int drawCardFailed = 0;
int treasureCardFailed = 0;

void randomAdventurerCheck(int currentPlayer, struct gameState *state) {
    int handpos = 0;
    int bonus = 0;
    
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    
    int drawntreasure = 0;
    int cardDrawn;
    int temphand[MAX_HAND];
    int k;
    int z = 0;
    
    int success;
    struct gameState testState;
    
    int treasureCard;
    int testStateTreasureCard = 0;
    int stateTreasureCard = 0;

    // Clear the game testState
    memset(&testState, 23, sizeof(struct gameState));
    // Copy thetemphandgame state to test case
    memcpy(&testState, state, sizeof(struct gameState));
    
    // Call the function to run the test
    success = cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
    
    if (success == -1) {
        failCount++;
    }
    
    // Taken from Adventurer Card Function
    while(drawntreasure<3){
        if (testState.deckCount[currentPlayer] <1){
            //if the deck is empty we need to shuffle discard and add to deck
            success = shuffle(currentPlayer, &testState);
            
            // Was the shuffle a success? Does the deck have more than 1 card?
            if (!success && testState.deckCount[currentPlayer] >= 1) {
                //                    printf("Shuffle failed for Current Player: %d and the Deck Count: %d\n", currentPlayer, testState.deckCount[currentPlayer]);
                shuffleFailed++;
                failCount++;
            }
        }
        
        // Was drawing card a success?
        success = drawCard(currentPlayer, &testState);
        
        if (success == -1 && testState.deckCount[currentPlayer] > 0) {
            //                printf("Draw Card failed for Current Player: %d and the Deck Count: %d\n", currentPlayer, testState.deckCount[currentPlayer]);
            drawCardFailed++;
            failCount++;
        }
        
        cardDrawn = testState.hand[currentPlayer][testState.handCount[currentPlayer]-1];
        //top card of hand is most recently drawn card.
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
            drawntreasure++;
        else{
            temphand[z]=cardDrawn;
            //this should just remove the top card (the most recently drawn one).
            testState.handCount[currentPlayer]--;
            z++;
        }
    }
    
    while(z-1>=0){
        // discard all cards in play that have been drawn
        testState.discard[currentPlayer][testState.discardCount[currentPlayer]++] = temphand[z-1];
        z=z-1;
    }

    // Check if Treasure Cards for testState and state match
    for (k = 0; k < testState.handCount[currentPlayer]; k++) {
        // Type of treasure card (copper, silver, gold, or others)
        treasureCard = testState.hand[currentPlayer][k];
        if (treasureCard == copper || treasureCard == silver || treasureCard == gold) {
            testStateTreasureCard++;
        }
    }
    
    for (k = 0; k < state->handCount[currentPlayer]; k++) {
        // Type of treasure card (copper, silver, gold, or others)
        treasureCard = state->hand[currentPlayer][k];
        if (treasureCard == copper || treasureCard == silver || treasureCard == gold) {
            stateTreasureCard++;
        }
    }
    
    if (testStateTreasureCard != stateTreasureCard) {
        treasureCardFailed++;
        failCount++;
    }
}

int main() {
    // Use time as seed for random
    srand(time(NULL));
    
//    int k[10] = { adventurer, council_room, feast, gardens, mine,
//        remodel, smithy, village, baron, great_hall };
  
//    int seed = 1000;
    int currentPlayer;

    struct gameState state;

    int discard = 0;
    int i, j;
    
    // Treasure types (used for drawing treasure cards)
    int treasures[] = { copper, silver, gold };
    int treasureCards;

    int iterations = 5000;
    
    
    // Minimum cards in deck and hand
    int min = 3;
    
    printf("Testing: adventureCard\n\n");
    printf("****** RANDOM TESTS *****\n");
    
    // Initalize Game
//    initializeGame(numPlayer, k, seed, &state);

    for (i = 0; i < iterations; i++) {
        // Clear the game state
        memset(&state, 23, sizeof(struct gameState));
        
        // Get the player number
        currentPlayer = Random() * MAX_PLAYERS;

        // Set the deck count for the player - minimum of 3 cards
        state.deckCount[currentPlayer] = (Random() * (MAX_DECK - min + 1)) + min;

        // Set hand count to random number -- bound of 3 to MAX_HAND (if empty, no treasure card drawn thus loop never ends)
        state.handCount[currentPlayer] = (Random() * (MAX_HAND - min + 1)) + min;

        // Set the discard count for the player
        state.discardCount[currentPlayer] = discard;
        
        // Set the number of treasure cards - minimum of 3 -- avoid endless loop
        treasureCards = (Random() * (state.deckCount[currentPlayer] - min) + 1) + min;
        
        for (j = 0; j < treasureCards; j++) {
            state.deck[currentPlayer][j] = treasures[rand() % 3];
        }
        
        // Set the player as current player (whose turn)
        state.whoseTurn = currentPlayer;

        // Run Adventurer Test
        randomAdventurerCheck(currentPlayer, &state);
    }

    if (failCount == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
        printf("NUMBER OF TESTS FAILED: %d\n", failCount);
        printf("SHUFFLE TESTS FAILED: %d\n", shuffleFailed);
        printf("DRAW CARD TESTS FAILED: %d\n", drawCardFailed);
        printf("TREASURE COUNT TESTS FAILED: %d\n", treasureCardFailed);
    }
    
    return 0;
}
