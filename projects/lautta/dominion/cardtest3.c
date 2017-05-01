/*
 * cardtest3.c
 * Testing village effect
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
    int newCards = 1;
    int newActions = 2;
    int discarded = 1;

    int i, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int success;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	testG.hand[thisPlayer][handpos] = village;

	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);


	// ----------- TEST 1: current player gains 1 card and village added to played pile --------------
	printf("TEST 1: current player gains 1 cards and village added to played pile\n");

	success = 0;

	if((testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded) && testG.playedCardCount == 1 && testG.playedCards[testG.playedCardCount-1] == village)
		success = 1;

	if(success == 0) {
		printf("TEST 1 FAILED\n");
		printf("-- played card count = %d, expected = %d\n", testG.playedCardCount, 1);
		printf("-- hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
		printf("-- card id = %d, expected = %d\n", testG.playedCards[testG.playedCardCount-1], village);
	}
	else
		printf("TEST 1 PASSED\n");

	// ----------- TEST 2: other player's deck is unchanged --------------
	printf("TEST 2: other player's deck and hand is unchanged\n");

	success = 0;

	if(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] && testG.handCount[nextPlayer] == G.handCount[nextPlayer])
		success = 1;

	if(success == 0) {
		printf("TEST 2 FAILED\n");
		printf("-- hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
		printf("-- deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
	}
	else
		printf("TEST 2 PASSED\n");

	// ----------- TEST 3: current player gets 2 actions  --------------
	printf("TEST 3: current player gets 2 actions\n");

	success = 0;

	if(testG.numActions == G.numActions + newActions)
		success = 1;

	if(success == 0) {
		printf("TEST 3 FAILED\n");
		printf("-- numActions = %d, expected = %d\n", testG.numActions, G.numActions + newActions);
	}
	else
		printf("TEST 3 PASSED\n");


	// ----------- TEST 4: current player drawing from own pile --------------
	printf("TEST 4: current player drawing from own pile\n");

	success = 0;

	if(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards)
		success = 1;

	if(success == 0) {
		printf("TEST 4 FAILED\n");
		printf("-- deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	}
	else
		printf("TEST 4 PASSED\n");


	// ----------- TEST 5: treasure and kingdom supply count hasn't changed --------------
	printf("TEST 5: treasure and kingdom supply count hasn't changed\n");

	success = 1;

	// check victory and treasure supplies
	for(m = curse; m <= gold; m++)
	{
		if(testG.supplyCount[m] != G.supplyCount[m])
			success = 0;
	}

	// check kingdom cards
	for(i = 0; i < 10; i++)
	{
		if(testG.supplyCount[k[i]] != G.supplyCount[k[i]])
			success = 0;
	}

	if(success == 0)
		printf("TEST 5 FAILED\n");
	else
		printf("TEST 5 PASSED\n");



	// ----------- TEST 6: buys and coins unchanged --------------
	printf("TEST 6: buys and coins unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins)
		success = 1;

	if(success == 0) {
		printf("TEST 6 FAILED\n");
		printf("-- numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys);
		printf("-- coins = %d, expected = %d\n", testG.coins, G.coins);
	}
	else
		printf("TEST 6 PASSED\n");

	printf("\n >>>>> Testing complete: %s <<<<<\n\n", TESTCARD);


	return 0;
}


