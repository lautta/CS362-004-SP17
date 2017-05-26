/*
 * unittest3.c
 * Testing endTurn()
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "endTurn()"

int main() {

    int i, j, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = 1;
    int newCards = 5;
    int discarded = 5;
    int success;

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf("----------------- Testing Function: %s ----------------\n", FUNCTION);


	// ----------- TEST 1: whoseTurn loops around when number of players exceeded --------------
	printf("TEST 1: whoseTurn loops around when number of players exceeded\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 0;

	// set whoseTurn to player 2 who is the max player in the game
	testG.whoseTurn = nextPlayer;

	endTurn(&testG);

	// after endTurn() who turn should return to player 1
	if(testG.whoseTurn == thisPlayer)
		success = 1;

	if(success == 0)
		printf("TEST 1 FAILED\n");
	else
		printf("TEST 1 PASSED\n");

	// ----------- TEST 2: if nothing is played state remains the same --------------
	printf("TEST 2: if nothing is played state remains the same\n");

	success = 0;

	// state variables affected by endTurn() should stay the same
	if(testG.outpostPlayed == G.outpostPlayed && testG.phase == G.phase && testG.numActions == G.numActions && testG.numBuys == G.numBuys && testG.playedCardCount == G.playedCardCount)
		success = 1;

	if(success == 0)
		printf("TEST 2 FAILED\n");
	else
		printf("TEST 2 PASSED\n");

	// ----------- TEST 3: whoseTurn increments normally and state variables properly resets --------------
	printf("TEST 3: whoseTurn increments normally and state variables properly reset\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 1;

	// change state variable affected by endTurn()
	testG.outpostPlayed += 1;
	testG.phase += 1;
	testG.numActions += 1;
	testG.numBuys += 1;
	testG.playedCardCount += 1;

	endTurn(&testG);

	// endTurn() should increment to the next player normally
	if(testG.whoseTurn != nextPlayer)
		success = 0;

	// endTurn() should reset state variables affected by endTurn()
	if(testG.outpostPlayed == G.outpostPlayed && testG.phase == G.phase && testG.numActions == G.numActions && testG.numBuys == G.numBuys && testG.playedCardCount == G.playedCardCount)
		success = 1;
	else
		success = 0;

	if(success == 0)
		printf("TEST 3 FAILED\n");
	else
		printf("TEST 3 PASSED\n");

	// ----------- TEST 4: handCount and discard count properly update for both players --------------
	printf("TEST 4: handCount and discard count properly update for both players\n");

	success = 1;

	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] - discarded && testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + discarded)
		success = 0;

	if(testG.handCount[nextPlayer] != G.handCount[nextPlayer] + newCards && testG.discardCount[nextPlayer] != G.discardCount[nextPlayer])
		success = 0;

	if(success == 0) {
		printf("TEST 4 FAILED\n");
		printf("-- player 1 hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);
		printf("-- player 1 discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);
		printf("-- player 2 hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
		printf("-- player 2 discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
	}
	else
		printf("TEST 4 PASSED\n");

	// ----------- TEST 5: coins are properly updated for the next player --------------
	printf("TEST 5: coins are properly updated for the next player\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 1;

	// set all of player 2's coins to copper
    for (j = 0; j < 10; j++)
	{
	  testG.deck[nextPlayer][j] = copper;
	}

	endTurn(&testG);

	// with a deck full of copper player 2's coins should be 5 after endTurn()
	if (testG.coins != 5)
		success = 0;

	if(success == 0)
		printf("TEST 5 FAILED\n");
	else
		printf("TEST 5 PASSED\n");


	// ----------- TEST 6: treasure and kingdom supply count hasn't changed --------------
	printf("TEST 6: treasure and kingdom supply count hasn't changed\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	endTurn(&testG);

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
		printf("TEST 6 FAILED\n");
	else
		printf("TEST 6 PASSED\n");


	printf("\n >>>>> Testing complete: %s <<<<<\n\n", FUNCTION);


	return 0;
}


