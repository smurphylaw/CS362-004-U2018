//gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99

// Random Generator for Smithy Card

#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <assert.h>
#include <math.h>

int failCount = 0;
int discardFailed = 0;
int drawCardFailed = 0;
int deckCountFailed = 0;
int handCountFailed = 0;

void randomSmithyCheck(int currentPlayer, struct gameState *state) {
    int k;
    
    int handPos = 0;
    int bonus = 0;
    
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    
    int success;
    struct gameState testState;
    
    
    // Clear the game testState
    memset(&testState, 23, sizeof(struct gameState));
    // Copy thetemphandgame state to test case
    memcpy(&testState, state, sizeof(struct gameState));
    
    // Call the function to run the test
    success = cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);
    
    if (success == -1) {
        failCount++;
    }
    
    // Taken from Smithy Card Function
    
    //+3 Cards
    // ** Bug #3: Change 3 to 2 (reducing it to +2 cards)
    for (k = 0; k < 2; k++)
    {
        success = drawCard(currentPlayer, &testState);
        if (success == -1 && testState.deckCount[currentPlayer] > 0) {
            drawCardFailed++;
            failCount++;
        }
    }
    
    //discard card from hand
    success = discardCard(handPos, currentPlayer, &testState, 0);
    
    // Was discarding a card a success?
    if (success) {
        discardFailed++;
        failCount++;
    }
    
    // Check if Deck Count for testState and state match
    int testStateDeckCount = testState.deckCount[currentPlayer];
    int stateDeckCount = state->deckCount[currentPlayer];
    
    if (testStateDeckCount != stateDeckCount) {
        deckCountFailed++;
        failCount++;
    }
    
    // Check if Hand Count for testState and state match
    int testStateHandCount = testState.handCount[currentPlayer];
    int stateHandCount = state->handCount[currentPlayer];
    
    if (testStateHandCount != stateHandCount) {
        handCountFailed++;
        failCount++;
    }
}

int main() {
    // Use time as seed for random
    srand(time(NULL));
    
    int i;
    int currentPlayer;
    
    struct gameState state;
    
    int iterations = 5000;
    
    printf("Testing: smithyCard\n\n");
    printf("****** RANDOM TESTS *****\n");
    
    // Initalize Game: 2 players, seed of 1000
    //    initializeGame(numPlayer, k, seed, &state);
    
    for (i = 0; i < iterations; i++) {
        // Clear the game state
        memset(&state, 23, sizeof(struct gameState));
        
        // Get the player number
        currentPlayer = Random() * MAX_PLAYERS;
        
        // Set the deck count for the player
        state.deckCount[currentPlayer] = Random() * MAX_DECK;
        
        // Set hand count to random number
        state.handCount[currentPlayer] = Random() * MAX_HAND;
        
        // Set the discard count for the player
        state.discardCount[currentPlayer] = Random() * MAX_DECK;
        
        // Set the number of cards current players played
        state.playedCardCount = Random() * (MAX_DECK - 1);
        
        // Set the player as current player (whose turn)
        state.whoseTurn = currentPlayer;
        
        // Run Adventurer Test
        randomSmithyCheck(currentPlayer, &state);
    }
    
    if (failCount == 0) {
        printf("PROGRAM TEST SUCCESFULLY COMPLETED\n\n");
    } else {
        printf("PROGRAM TEST FAILED\n\n");
        printf("NUMBER OF TESTS FAILED: %d\n", failCount);
        printf("DISCARD TESTS FAILED: %d\n", discardFailed);
        printf("DRAW CARD TESTS FAILED: %d\n", drawCardFailed);
        printf("DECK COUNT TESTS FAILED: %d\n", deckCountFailed);
        printf("HAND COUNT TESTS FAILED: %d\n", handCountFailed);
    }
    
    return 0;
}
