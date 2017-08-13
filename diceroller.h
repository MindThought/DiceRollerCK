#pragma once
#include <map>
#include "RollData.h"

int rollKeep(RollData &data);

float findAverage(RollData &data);

int keepDice(std::vector<int>& pool, int keep);

void diceCounter(RollData &data, std::vector<int>& rolls, std::vector<long long>& curve, int position);

void diceCounterEmpirical(RollData &data, std::map<int, int>& OUT_rollMap);

std::vector<long long> findOdds(RollData data);

std::vector<long long> findOddsThreaded(RollData data);