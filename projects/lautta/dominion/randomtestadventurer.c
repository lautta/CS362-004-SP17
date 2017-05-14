/*
 * randomtestadventurer.c
 * Testing adventurer effect
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NOISY 0

int checkAdventurer(int p, int p2, struct gameState *post, int handPos, int treasures)
{
  int i;
  int treasure1;
  int treasure2;
  int postTreasures = 0;
  int temphand[MAX_HAND];
  int drawntreasure=0;
  int z = 0;
  int cardDrawn = 0;
  int testSuccess = 1;

  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  playAdventurer(drawntreasure, post, p, cardDrawn, temphand, z);

  // check hand increased
  if (post->handCount[p] != pre.handCount[p] + 2)
  {
    if(NOISY)
      printf("FAILED! hand count = %d, expected = %d\n", post->handCount[p], pre.handCount[p] + 2);
    testSuccess = 0;
  }

  // check player's supply decreased by two
  if(post->deckCount[p] + post->discardCount[p] != pre.deckCount[p] + pre.discardCount[p] - 2)
  {
    if(NOISY)
      printf("FAILED! deck + discard count = %d, expected = %d\n", (post->deckCount[p] + post->discardCount[p]), (pre.deckCount[p] + pre.discardCount[p] - 2));
    testSuccess = 0;
  }

  // check treasure went down accordingly, along with the previous test this will also ensure that no non-treasure cards were discarded if both pass
  for (i = 0; i < post->deckCount[p]; i++)
  {
    if(post->deck[p][i] == copper || post->deck[p][i] == silver || post->deck[p][i] == gold)
      postTreasures++;
  }

  for (i = 0; i < post->discardCount[p]; i++)
  {
    if(post->deck[p][i] == copper || post->deck[p][i] == silver || post->deck[p][i] == gold)
      postTreasures++;
  }

  if (postTreasures != treasures - 2)
  {
    if(NOISY)
      printf("FAILED! treasures in discard and deck = %d, expected = %d\n", postTreasures, treasures - 2);
    testSuccess = 0;
  }

  // check that top 2 cards in hand are treasures
  treasure1 = post->hand[p][post->handCount[p]-1];
  treasure2 = post->hand[p][post->handCount[p]-2];

  if(treasure1 != copper && treasure1 != silver && treasure1 != gold)
    if(NOISY)
      printf("FAILED! new hand card 1 = %d, expected = 4, 5, or 6\n", treasure1);
    testSuccess = 0;

  if(treasure2 != copper && treasure2 != silver && treasure2 != gold)
    if(NOISY)
      printf("FAILED! new hand card 2 = %d, expected = 4, 5, or 6\n", treasure2);
    testSuccess = 0;


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

  // check other state variables
  if (post->numActions != pre.numActions)
  {
    if(NOISY)
      printf("FAILED! actions = %d, expected = %d\n", post->numActions, pre.numActions + 2);
    testSuccess = 0;
  }

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
  int treasures;

  printf ("Testing adventurer\n");

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

    // need at least 1 for hand
    G.handCount[player] = floor(Random() * (MAX_HAND - 1)) + 1;

    G.deckCount[player2] = floor(Random() * MAX_DECK);
    G.discardCount[player2] = floor(Random() * MAX_DECK);
    G.handCount[player2] = floor(Random() * MAX_HAND);

    // fill randomized hand count with randomized cards
    for (i = 0; i < G.handCount[player]; i++)
    {
      G.hand[player][i] = floor(Random() * 27);
    }

    // adventurer card in random hand position
    position = floor(Random() * (G.handCount[player] - 1));
    G.hand[player][position] = adventurer;

    // fill deck and discard with randomized cards and make sure at least two treasures between the two
    // I discovered a bug in adventurer when there are less than 2 treasure, there is an infinite loop, so that's why I make sure there are two treasure
    do {
      treasures = 0;

      G.deckCount[player] = floor(Random() * MAX_DECK);
      G.discardCount[player] = floor(Random() * MAX_DECK);

      for (i = 0; i < G.deckCount[player]; i++)
      {
        G.deck[player][i] = floor(Random() * 27);
        if(G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold)
          treasures++;
      }

      for (i = 0; i < G.discardCount[player]; i++)
      {
        G.discard[player][i] = floor(Random() * 27);
        if(G.deck[player][i] == copper || G.deck[player][i] == silver || G.deck[player][i] == gold)
          treasures++;
      }
    }while (treasures < 2);

    success = checkAdventurer(player, player2, &G, position, treasures);

    if (success == 1)
      successCount++;
  }

  printf("\n >>>>> Adventurer test success: %d out of 2000 tests <<<<<\n\n", successCount);

  return 0;
}
