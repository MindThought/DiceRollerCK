#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>		/* std::vector, std::queue, std::priority_queue */
#include <thread>		/* std::thread, std::join */
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
	int total = 0;
	std::vector<int> set(pool);
	std::sort(set.begin(), set.end(), std::greater<int>());
	for (size_t i = 0; i < keep; i++)
	{
		total += set[i];
	}
	return total;
}

void diceCounter(RollData &data, std::vector<int> &rolls, std::vector<long long> &curve, int position)
{
	for (int i = 1; i <= data.DiceSize; i++) 
	{
		rolls[position] = i;
		if (data.DicePool == position + 1) 
		{
			int pos = keepDice(rolls, data.DiceKeep);
			curve[pos] += 1;
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

std::vector<long long> findOdds(RollData data) 
{
	std::vector<int> rolls;
	rolls.resize(data.DicePool);
	std::vector<long long> curve;
	curve.resize(data.DiceSize*data.DiceKeep + 1);
	diceCounter(data, rolls, curve, 0);
	return curve;
}

std::vector<long long> findOddsThreaded(RollData data)
{
	int numberOfThreads = data.DiceSize;
	std::vector<std::thread> tasks(numberOfThreads);
	std::vector<std::vector<long long>> curves(numberOfThreads);
	std::vector<int> rolls;
	rolls.resize(data.DicePool);

	for (int i = 0; i < numberOfThreads; ++i)
	{
		
		rolls[0] = i+1;
		curves[i].resize(data.DiceSize*data.DiceKeep + 1);
		tasks[i] = std::thread(diceCounter,
			data,						//RollData object
			rolls,						//RollTracker
			std::ref(curves[i]),		//ResultTracker
			1
		);
	}
	
	for_each(tasks.begin(), tasks.end(), std::mem_fn(&std::thread::join));

	std::vector<long long> results(data.DiceSize*data.DiceKeep + 1);
	for each (auto curve in curves)
	{
		for (size_t i = data.DiceKeep; i < data.DiceSize*data.DiceKeep + 1; i++)
		{
			results[i] += curve[i];
		}
	}
	return results;
}