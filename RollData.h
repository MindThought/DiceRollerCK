#pragma once
class RollData
{
public:
	/// Constructor and Desctructor
	RollData();
	~RollData();

	/// Data objects
	int DicePool = 0;
	int DiceKeep = 0;
	int DiceSize = 0;
	int Rolls = 0;
	bool Explode = false;
};