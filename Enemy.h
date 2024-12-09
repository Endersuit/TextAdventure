#pragma once
#include "Creature.h"
#include <iostream>
class Enemy: public Creature
{
	virtual void AnalyzeAndDecide(int playerHealth,int playerDefence, bool defenceStatus)= 0;
protected:

	bool CheckCreatureIsHighOnHealth(Creature* creature);
	bool CheckCreatureIsFullAP(Creature* creature);
	bool ReturnRandomBool();
};

