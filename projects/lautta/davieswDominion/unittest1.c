/*
 * unittest1.c
 * Testing isGameOver()
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "isGameOver()"

int main() {

    int i, m;
    int seed = 1000;
    int numPlayers = 2;
    int success;
    int result;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};


	printf("----------------- Testing Function: %s ----------------\n", FUNCTION);


	// ----------- TEST 1: game is over when province supply is empty --------------
	printf("TEST 1: game is over when province supply is empty\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set province count to 0
	testG.supplyCount[province] = 0;

	result = isGameOver(&testG);

	success = 0;

	// isGameOver returns 1 when successful
	if(result == 1)
		success = 1;

	if(success == 0)
		printf("TEST 1 FAILED\n");
	else
		printf("TEST 1 PASSED\n");


	// ----------- TEST 2: game is over when 3 supply other than province are empty --------------
	printf("TEST 2: game is over when 3 supply other than province are empty\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set 3 supply to 0, treasure in this case
	testG.supplyCount[copper] = 0;
	testG.supplyCount[silver] = 0;
	testG.supplyCount[gold] = 0;

	result = isGameOver(&testG);

	success = 0;

	// isGameOver returns 1 when successful
	if(result == 1)
		success = 1;

	if(success == 0)
		printf("TEST 2 FAILED\n");
	else
		printf("TEST 2 PASSED\n");


	// ----------- TEST 3: game is over when combination of 1 supply/treasure/kingdom are empty -----
	printf("TEST 3: game is over when combination of 1 supply/treasure/kingdom are empty\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set 3 supply to 0, combination of different supply types
	testG.supplyCount[copper] = 0;
	testG.supplyCount[village] = 0;
	testG.supplyCount[estate] = 0;

	result = isGameOver(&testG);

	success = 0;

	// isGameOver returns 1 when successful
	if(result == 1)
		success = 1;

	if(success == 0)
		printf("TEST 3 FAILED\n");
	else
		printf("TEST 3 PASSED\n");


	// ----------- TEST 4: game is not over when 2 supply other than province are empty --------------
	printf("TEST 4: game is not over when 2 supply other than province are empty\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set only 2 supply empty
	testG.supplyCount[copper] = 0;
	testG.supplyCount[silver] = 0;

	result = isGameOver(&testG);

	success = 0;

	// isGameOver returns 0 when untrue
	if(result == 0)
		success = 1;

	if(success == 0)
		printf("TEST 4 FAILED\n");
	else
		printf("TEST 4 PASSED\n");


	// ----------- TEST 5: game is not over when 1 supply other than province are empty --------------
	printf("TEST 5: game is not over when 1 supply other than province are empty\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	// set only 1 supply to 0
	testG.supplyCount[copper] = 0;

	result = isGameOver(&testG);

	success = 0;

	// isGameOver returns 0 when untrue
	if(result == 0)
		success = 1;

	if(success == 0)
		printf("TEST 5 FAILED\n");
	else
		printf("TEST 5 PASSED\n");


	// ----------- TEST 6: game is not over with full supplies --------------
	printf("TEST 6: game is not over with full supplies\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	result = isGameOver(&testG);

	success = 0;

	if(result == 0)
		success = 1;

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

	printf("\n >>>>> Testing complete: %s <<<<<\n\n", FUNCTION);


	return 0;
}


