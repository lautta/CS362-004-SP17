/*
 * unittest2.c
 * Testing whoseTurn()
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "whoseTurn()"

int main() {

    int i, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int success;
    int result;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf("----------------- Testing Function: %s ----------------\n", FUNCTION);


	// ----------- TEST 1: whoseTurn points to current player and next player when appropriate --------------
	printf("TEST 1: whoseTurn points to current player and next player when appropriate\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	result = whoseTurn(&testG);

	success = 1;

	// whoseTurn() should return player 1 = 0
	if(result != thisPlayer)
		success = 0;

	// set whoseTurn to player 2, 1
	testG.whoseTurn = nextPlayer;

	result = whoseTurn(&testG);

	// whoseTurn() should return player 2 = 1
	if(result != nextPlayer)
		success = 0;

	if(success == 0)
		printf("TEST 1 FAILED\n");
	else
		printf("TEST 1 PASSED\n");



	// ----------- TEST 2: treasure and kingdom supply count hasn't changed --------------
	printf("TEST 2: treasure and kingdom supply count hasn't changed\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	whoseTurn(&testG);

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
		printf("TEST 2 FAILED\n");
	else
		printf("TEST 2 PASSED\n");


	// ----------- TEST 3: actions, buys, and coins unchanged --------------
	printf("TEST 3: actions, buys, and coins unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins && testG.numActions == G.numActions)
		success = 1;

	if(success == 0)
		printf("TEST 3 FAILED\n");
	else
		printf("TEST 3 PASSED\n");

	printf("\n >>>>> Testing complete: %s <<<<<\n\n", FUNCTION);


	return 0;
}


