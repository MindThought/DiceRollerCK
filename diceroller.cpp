#include "diceroller.h"

int rollKeepExplode(int dicePool, int diceSize, int keep, int explode) {		//Does the same as rollKeep, but explodes if the dice rolls maximum.
	/* initialize random seed: */
	srand(time(NULL));
	priority_queue<int> currentSet;
	int total = 0;
	for (int i = 0; i < dicePool; i++) {
		int roll = 0;
		do {
			roll += rand() % diceSize + 1;
		} while(roll % diceSize == 0 && explode == 1)
		currentSet.push(roll);
	}
	for (int i = 0; i < keep; i++) {
		total += currentSet.top();
		currentSet.pop();
	}
	return total;
}

float findAverageExplode(int dicePool, int diceSize, int keep, int explode, int numberOfRolls) {		//Uses rollKeepExplode to empiricaly find the average of a set of dice
	float grandTotal = 0;
	/* initialize random seed: */
	srand(time(NULL));

	for (int i = 0; i < numberOfRolls; i++)	{
		grandTotal += rollKeepExplode(dicePool, diceSize, keep, explode);
	}
	float answer = grandTotal / numberOfRolls;
	return answer;
}

int keepDice(vector<int> &pool, int keep)	{				//Takes a vector(pool) and an int(keep) and returns the total of the keep highest values in pool.
	priority_queue<int> set;
	int total = 0;
	for (int i = 1; i < pool.size(); i++) {
		set.push(pool[i]);
	}
	for (int i = 0; i < keep; i++)	{
		total += set.top();
		set.pop();
	}
	return total;
}

void diceCounter(int &dicePool, int &diceSize, int &keep, vector<int> &rolls, vector<long long> &curve, int position) {
	for (int i = 1; i <= diceSize; i++) {
		rolls[position] = i;
		if (dicePool == position) {
			curve[keepDice(rolls, keep)] += 1;
		} else {
			diceCounter(dicePool, diceSize, keep, rolls, curve, position + 1);
		} 
	}
}

vector<long long> findOdds(int dicePool, int diceSize, int keep) {
	vector<int> rolls;
	rolls.resize(dicePool+1);
	vector<long long> curve;
	int size = diceSize*keep + 1;
	curve.resize(size);
	diceCounter(dicePool, diceSize, keep, rolls, curve, 1);
	return curve;
}