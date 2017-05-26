/*
 * randomtestcard2.c
 * Testing village effect
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NOISY 1

int checkVillage(int p, int p2, struct gameState *post, int handPos)
{
  int testSuccess = 1;

  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  //playVillage(p, post, handPos);
  cardEffect(village, 0, 0, 0, post, handPos, 0);

  // if deck and discard are empty
  if (pre.deckCount[p] + pre.discardCount[p] <= 0)
  {
    if (post->deckCount[p] != 0)
    {
      if(NOISY)
        printf("FAILED! deck count = %d, expected = %d\n", post->deckCount[p], 0);
      testSuccess = 0;
    }

    if (post->handCount[p] != pre.handCount[p] - 1)
    {
      if(NOISY)
        printf("FAILED! hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] - 1);
      testSuccess = 0;
    }
  }
  // deck is empty, shuffle will happened
  else if (pre.deckCount[p] == 0)
  {
    if (post->handCount[p] != pre.handCount[p])
    {
      if(NOISY)
        printf("FAILED! hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p]);
      testSuccess = 0;
    }

    if (post->discardCount[p] != 0)
    {
      if(NOISY)
        printf("FAILED! discard count = %d, expected = %d\n", post->discardCount[p], 0);
      testSuccess = 0;
    }

    if (post->deckCount[p] != pre.discardCount[p] - 1)
    {
      if(NOISY)
        printf("FAILED! deck count = %d, expected = %d\n", post->deckCount[p], pre.discardCount[p] - 1);
      testSuccess = 0;
    }
  }
  // otherwise, normal behavior
  else
  {
    if (post->deckCount[p] != pre.deckCount[p] - 1)
    {
      if(NOISY)
        printf("FAILED! deck count = %d, expected = %d\n", post->deckCount[p], pre.deckCount[p] - 1);
      testSuccess = 0;
    }


    if (post->handCount[p] != pre.handCount[p])
    {
      if(NOISY)
        printf("FAILED! hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p]);
      testSuccess = 0;
    }
  }

  // check other player counts
  if (post->handCount[p2] != pre.handCount[p2] || post->deckCount[p2] != pre.deckCount[p2] || post->discardCount[p2] != pre.discardCount[p2])
  {
    if(NOISY)
    {
      printf("FAILED! hand count = %d, expected = %d\n", post->handCount[p2], pre.handCount[p2]);
      printf("FAILED! deck count = %d, expected = %d\n", post->deckCount[p2], pre.deckCount[p2]);
      printf("FAILED! discard count = %d, expected = %d\n", post->discardCount[p2], pre.discardCount[p2]);
    }
    testSuccess = 0;
  }

  // village gives 2 actions
  if (post->numActions != pre.numActions + 2)
  {
    if(NOISY)
      printf("FAILED! actions = %d, expected = %d\n", post->numActions, pre.numActions + 2);
    testSuccess = 0;
  }

  // check other state variables, this is where my bug will be found
  if (post->whoseTurn != pre.whoseTurn)
  {
    if(NOISY)
      printf("FAILED! whoseTurn = %d, expected = %d\n", post->whoseTurn, pre.whoseTurn);
    testSuccess = 0;
  }

  if (post->numBuys != pre.numBuys)
  {
    if(NOISY)
      printf("FAILED! buys = %d, expected = %d\n", post->numBuys, pre.numBuys);
    testSuccess = 0;
  }

  if (post->coins != pre.coins)
  {
    if(NOISY)
      printf("FAILED! coins = %d, expected = %d\n", post->coins, pre.coins);
    testSuccess = 0;
  }

  if (post->playedCardCount != pre.playedCardCount + 1)
  {
    if(NOISY)
      printf("FAILED! played card count = %d, expected = %d\n", post->playedCardCount, pre.playedCardCount + 1);
    testSuccess = 0;
  }

  if (post->playedCards[post->playedCardCount-1] != village)
  {
    if(NOISY)
      printf("FAILED! played card = %d, expected = %d\n", post->playedCards[post->playedCardCount-1], village);
    testSuccess = 0;
  }

  return testSuccess;
}

int main(){

  struct gameState G;

  int i;
  int n;
  int success;
  int successCount = 0;
  int player;
  int player2;
  int position;

  printf ("Testing village\n");

  printf ("RANDOM TESTS\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    success = 1;

    for (i = 0; i < sizeof(struct gameState); i++)
    {
      ((char*)&G)[i] = floor(Random() * 256);
    }

    G.numActions = floor(Random() * 100) + 1;
    G.numBuys = floor(Random() * 100) + 1;
    G.coins = floor(Random() * 100);
    G.playedCardCount = floor(Random() * 100);

    player = floor(Random() * 2);
    G.whoseTurn = player;
    player2 = 1 - player;

    G.deckCount[player] = floor(Random() * MAX_DECK);
    G.discardCount[player] = floor(Random() * MAX_DECK);

    // at least 1 for village
    G.handCount[player] = floor(Random() * (MAX_HAND - 1)) + 1;

    G.deckCount[player2] = floor(Random() * MAX_DECK);
    G.discardCount[player2] = floor(Random() * MAX_DECK);
    G.handCount[player2] = floor(Random() * MAX_HAND);

    // fill randomized hand count with randomized cards
    for (i = 0; i < G.handCount[player]; i++)
    {
      G.hand[player][i] = floor(Random() * 27);
    }

    // village card in random hand position
    position = floor(Random() * (G.handCount[player] - 1));
    G.hand[player][position] = village;

    // fill randomized deck count with randomized cards
    for (i = 0; i < G.deckCount[player]; i++)
    {
      G.deck[player][i] = floor(Random() * 27);
    }

    // fill randomized discard count with randomized cards
    for (i = 0; i < G.discardCount[player]; i++)
    {
      G.discard[player][i] = floor(Random() * 27);
    }

    success = checkVillage(player, player2, &G, position);

    if (success == 1)
      successCount++;
  }

  printf("\n >>>>> Village test success: %d out of 2000 tests <<<<<\n\n", successCount);

  return 0;
}
