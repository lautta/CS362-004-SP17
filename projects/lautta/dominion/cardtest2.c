/*
 * cardtest2.c
 * Testing adventurer effect
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 2;

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

	testG.hand[thisPlayer][handpos] = adventurer;

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	// ----------- TEST 1: current player gains 2 cards and adventurer added to played pile --------------
	printf("TEST 1: current player gains 2 cards and adventurer added to played pile\n");

	success = 0;

	if((testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards) && testG.playedCardCount == 1 && testG.playedCards[testG.playedCardCount-1] == adventurer)
		success = 1;

	if(success == 0) {
		printf("TEST 1 FAILED\n");
		printf("-- played card count = %d, expected = %d\n", testG.playedCardCount, 1);
		printf("-- hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
		printf("-- card id = %d, expected = %d\n", testG.playedCards[testG.playedCardCount-1], adventurer);
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


	// ----------- TEST 3: Revealed cards being discarded and coming from players cards--------------
	printf("TEST 3: Revealed cards being discarded and coming from players cards\n");

	success = 1;

	if(testG.discardCount[thisPlayer] != G.discardCount[thisPlayer] + testG.discardCount[thisPlayer])
		success = 0;

	if((testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) != (G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards))
		success = 0;

	if(success == 0) {
		printf("TEST 3 FAILED\n");
		printf("-- discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + testG.discardCount[thisPlayer]);
		printf("-- discard + deck count = %d, expected = %d\n", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards);
	}
	else
		printf("TEST 3 PASSED\n");


	// ----------- TEST 4: 2 newest cards in hand are treasures --------------
	printf("TEST 4: 2 newest cards in hand are treasures\n");

	success = 1;

	int card1 = testG.hand[thisPlayer][testG.handCount[thisPlayer]-1];
	int card2 = testG.hand[thisPlayer][testG.handCount[thisPlayer]-2];

	if(card1 != copper && card1 != silver && card1 != gold)
		success = 0;

	if(card2 != copper && card2 != silver && card2 != gold)
		success = 0;

	if(success == 0) {
		printf("TEST 4 FAILED\n");
		printf("-- card 1 id = %d, expected = %d or %d or %d\n", card1, copper, silver, gold);
		printf("-- card 2 id = %d, expected = %d or %d or %d\n", card2, copper, silver, gold);
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


	// ----------- TEST 6: actions and buys unchanged --------------
	printf("TEST 6: actions and buys unchanged\n");

	success = 0;

	if(testG.numBuys == G.numBuys && testG.coins == G.coins && testG.numActions == G.numActions)
		success = 1;

	if(success == 0) {
		printf("TEST 6 FAILED\n");
		printf("-- numBuys = %d, expected = %d\n", testG.numBuys, G.numBuys);
		printf("-- coins = %d, expected = %d\n", testG.coins, G.coins);
		printf("-- numActions = %d, expected = %d\n", testG.numActions, G.numActions);
	}
	else
		printf("TEST 6 PASSED\n");


	// ----------- TEST 7: discard contains no treasure --------------
	printf("TEST 7: discard contains no treasure\n");

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

    for (i = 0; i < testG.deckCount[thisPlayer]; i++) {
        testG.deck[thisPlayer][i] = estate;
    }

    testG.deck[thisPlayer][0] = copper;
    testG.deck[thisPlayer][2] = silver;
    testG.deck[thisPlayer][4] = gold;

	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	success = 1;

	for (i = 0; i < testG.discardCount[thisPlayer]; i++) {
        card1 = testG.discard[thisPlayer][i];
        if(card1 == copper || card1 == silver || card1 == gold)
        	success = 0;
    }

	if(success == 0)
		printf("TEST 7 FAILED\n");
	else
		printf("TEST 7 PASSED\n");

	printf("\n >>>>> Testing complete: %s <<<<<\n\n", TESTCARD);

	return 0;
}


