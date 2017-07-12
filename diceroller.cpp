#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>		/* std::vector, std::queue, std::priority_queue */
#include <iostream>		/* std::cout, std::endl */
#include <map>			/* std::map */
#include "DiceRoller.h"

/* Takes in the number of dice to roll, the size of the dice and and the number of dice to keep. Then it rolls them and keeps the specified amount. *//* Same as rollKeep, but if the max result is rolled it rolls again */
int rollKeep(RollData &data)
{
	std::priority_queue<int> currentSet;
	int total = 0;
	for (int i = 0; i < data.DicePool; i++)
	{
		int roll = 0;
		do
		{
			roll += rand() % data.DiceSize + 1;
		} while (roll % data.DiceSize == 0 && data.Explode == true);
		currentSet.push(roll);
	}
	for (int i = 0; i < data.DiceKeep; i++)
	{
		total += currentSet.top();
		currentSet.pop();
	}
	return total;
}

/* Calls rollKeep numberOfRolls times, adding them together, then dividing by the number of rolls*/
float findAverage(RollData &data) 
{
	float grandTotal = 0;

	for (int i = 0; i < data.Rolls; i++)
	{
		grandTotal += rollKeep(data);
	}
	float answer = grandTotal / data.Rolls;
	return answer;
}

int keepDice(std::vector<int> &pool, int keep) {			//Takes a vector(pool) and an int(keep) and returns the total of the keep highest values in pool.
	std::priority_queue<int> set;
	int total = 0;
	for (int i = 1; i < pool.size(); i++) {
		set.push(pool[i]);
	}
	for (int i = 0; i < keep; i++) {
		total += set.top();
		set.pop();
	}
	return total;
}

void diceCounter(RollData &data, std::vector<int> &rolls, std::vector<long long> &curve, int position)
{
	for (int i = 1; i <= data.DiceSize; i++) 
	{
		rolls[position] = i;
		if (data.DicePool == position) 
		{
			curve[keepDice(rolls, data.DiceKeep)] += 1;
		}
		else 
		{
			diceCounter(data, rolls, curve, position + 1);
		} 
	}
}

void diceCounterEmpirical(RollData &data, std::map<int, int> &OUT_rollMap)
{
	int result = 0;
	for (size_t i = 0; i < data.Rolls; i++)
	{
		OUT_rollMap[rollKeep(data)]++;
	}
}

std::vector<long long> findOdds(RollData data) {

	std::vector<int> rolls;
	rolls.resize(data.DicePool+1);
	std::vector<long long> curve;
	int size = data.DiceSize*data.DiceKeep + 1;
	curve.resize(size);
	diceCounter(data, rolls, curve, 1);
	return curve;
}