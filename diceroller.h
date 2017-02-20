#ifndef DICEROLLER_H
#define DICEROLLER_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>

int rollKeepExplode(int dicePool, int diceSize, int keep, int explode);

float findAverageExplode(int dicePool, int diceSize, int keep, int explode, int numberOfRolls);

int keepDice(vector<int> &pool, int keep);

void diceCounter(int &dicePool, int &diceSize, int &keep, vector<int> &rolls, vector<long long> &curve, int position);

vector<long long> findOdds(int dicePool, int diceSize, int keep);

#endif