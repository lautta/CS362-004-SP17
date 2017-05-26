/*
 * unittest4.c
 * Testing gainCard()
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "gainCard()"

int main() {

    int i, m;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int success;
    int result;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf("----------------- Testing Function: %s ----------------\n", FUNCTION);


	////////////// Test case with invalid supply card
	// ----------- TEST 1: gainCard returns -1 with supply card not in game--------------
	printf("TEST 1: gainCard returns -1 with supply card not in game\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 1;

	// test for each card state and baron card which isn't in our kingdom set
	for (i = 0; i < 3; i++)
	{
		result = gainCard(baron, &testG, i, thisPlayer);
		if(result != -1)
			success = 0;
	}

	if(success == 0)
		printf("TEST 1 FAILED\n");
	else
		printf("TEST 1 PASSED\n");



	// ----------- TEST 2: other player's deck is unchanged --------------
	printf("TEST 2: all players deck, hand, and discard are unchanged\n");

	success = 1;

	// if supply was empty, make sure no one's hand or deck changed
	for (i = 0; i < numPlayers; i++)
	{
		if(testG.deckCount[i] != G.deckCount[i] && testG.handCount[i] != G.handCount[i] && testG.discardCount[i] != G.discardCount[i])
			success = 0;
	}

	if(success == 0)
		printf("TEST 2 FAILED\n");
	else
		printf("TEST 2 PASSED\n");


	// ----------- TEST 3: treasure and kingdom supply count hasn't changed --------------
	printf("TEST 3: treasure and kingdom supply count hasn't changed\n");

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
		printf("TEST 3 FAILED\n");
	else
		printf("TEST 3 PASSED\n");


	// ----------- TEST 4: actions, buys, and coins unchanged --------------
	printf("TEST 4: actions, buys, and coins unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins && testG.numActions == G.numActions)
		success = 1;

	if(success == 0)
		printf("TEST 4 FAILED\n");
	else
		printf("TEST 4 PASSED\n");



	////////////// Test case with empty supply card
	// ----------- TEST 5: gainCard returns -1 with empty supply card --------------
	printf("TEST 5: gainCard returns -1 with empty supply card\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 1;

	// set council_room to empty
	testG.supplyCount[council_room] = 0;
	G.supplyCount[council_room] = 0;

	// test all 3 card states with empty card supply
	for (i = 0; i < 3; i++)
	{
		result = gainCard(council_room, &testG, i, thisPlayer);
		if(result != -1)
			success = 0;
	}

	if(success == 0)
		printf("TEST 5 FAILED\n");
	else
		printf("TEST 5 PASSED\n");


	// ----------- TEST 6: all players deck, hand, and discard are unchanged --------------
	printf("TEST 6: all players deck, hand, and discard are unchanged\n");

	success = 1;

	for (i = 0; i < numPlayers; i++)
	{
		if(testG.deckCount[i] != G.deckCount[i] && testG.handCount[i] != G.handCount[i] && testG.discardCount[i] != G.discardCount[i])
			success = 0;
	}

	if(success == 0)
		printf("TEST 6 FAILED\n");
	else
		printf("TEST 6 PASSED\n");


	// ----------- TEST 7: treasure and kingdom supply count hasn't changed --------------
	printf("TEST 7: treasure and kingdom supply count hasn't changed\n");

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
		printf("TEST 7 FAILED\n");
	else
		printf("TEST 7 PASSED\n");


	// ----------- TEST 8: actions, buys, and coins unchanged --------------
	printf("TEST 8: actions, buys, and coins unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins && testG.numActions == G.numActions)
		success = 1;

	if(success == 0)
		printf("TEST 8 FAILED\n");
	else
		printf("TEST 8 PASSED\n");



	////////////// Test case with valid supply card
	// ----------- TEST 9: gainCard returns 0 with valid supply card --------------
	printf("TEST 9: gainCard returns 0 with valid supply card\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	success = 1;

	// test all 3 card states with full supply card
	for (i = 0; i < 3; i++)
	{
		result = gainCard(council_room, &testG, i, thisPlayer);
		if(result != 0)
			success = 0;
	}

	if(success == 0)
		printf("TEST 9 FAILED\n");
	else
		printf("TEST 9 PASSED\n");


	// ----------- TEST 10: other players deck, hand, and discard are unchanged --------------
	printf("TEST 10: other players deck, hand, and discard are unchanged\n");

	success = 1;

	// test for every player other than current player
	for (i = 1; i < numPlayers; i++)
	{
		if(testG.deckCount[i] != G.deckCount[i] && testG.handCount[i] != G.handCount[i] && testG.discardCount[i] != G.discardCount[i])
			success = 0;
	}

	if(success == 0)
		printf("TEST 10 FAILED\n");
	else
		printf("TEST 10 PASSED\n");


	// ----------- TEST 11: council supply down three for each flag test  --------------
	printf("TEST 11: council supply count down three for each flag test\n");

	success = 1;

	// 3 cards should be subtracted from supplyCount
	if(testG.supplyCount[council_room] != G.supplyCount[council_room] - 3)
		success = 0;

	if(success == 0)
		printf("TEST 11 FAILED\n");
	else
		printf("TEST 11 PASSED\n");

	// ----------- TEST 12: 1 council room added to current player's deck, discard, and hand --------------
	printf("TEST 12: 1 council room added to current player's deck, discard, and hand\n");

	success = 1;

	// 1 card should be added to each pile
	if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] + 1 && testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1] != council_room)
		success = 0;

	if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 1 && testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] != council_room)
		success = 0;

	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + 1 && testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] != council_room)
		success = 0;

	if(success == 0)
		printf("TEST 12 FAILED\n");
	else
		printf("TEST 12 PASSED\n");


	// ----------- TEST 13: other treasure and kingdom supply count hasn't changed --------------
	printf("TEST 13: other treasure and kingdom supply count hasn't changed\n");

	success = 1;

	// check victory and treasure supplies
	for(m = curse; m <= gold; m++)
	{
		if(testG.supplyCount[m] != G.supplyCount[m])
			success = 0;
	}

	// check kingdom cards - other than council_room
	for(i = 0; i < 9; i++)
	{
		if(testG.supplyCount[k[i]] != G.supplyCount[k[i]])
			success = 0;
	}

	if(success == 0)
		printf("TEST 13 FAILED\n");
	else
		printf("TEST 13 PASSED\n");


	// ----------- TEST 14: actions, buys, and coins unchanged --------------
	printf("TEST 14: actions, buys, and coins unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins && testG.numActions == G.numActions)
		success = 1;

	if(success == 0)
		printf("TEST 14 FAILED\n");
	else
		printf("TEST 14 PASSED\n");


	printf("\n >>>>> Testing complete: %s <<<<<\n\n", FUNCTION);

	return 0;
}


