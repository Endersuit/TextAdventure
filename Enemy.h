#pragma once
#include "Creature.h"
#include <iostream>
class Enemy: public Creature
{

public : 
	Enemy(std::string creatureName, int maxHealth, float defence, float attack, bool isOnDefensive, std::unique_ptr<Consumable> consumable);
	Enemy(const Enemy& other);
	virtual void AnalyzeAndDecide(Creature* player) = 0;
protected:



	bool CheckCreatureIsHighOnHealth(Creature* creature);
	bool CheckCreatureIsFullAP(Creature* creature);
	bool ReturnRandomBool();
};

