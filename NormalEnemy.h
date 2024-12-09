#pragma once
#include "Enemy.h"
class NormalEnemy:public Enemy
{
public : 

	
	NormalEnemy(std::string creatureName, int maxHealth, float defence, float attack, bool isOnDefensive, std::unique_ptr<Consumable> consumable);
	NormalEnemy(const NormalEnemy& other);
	virtual void AnalyzeAndDecide(Creature* player);

private :
	bool debug = false;


	void CreatureOnDefenceAndFullAP(Creature* player);
	void CreatureOnDefenceAndPartialAP(Creature* player);

	void CreatureNotOnDefenceAndFullAP(Creature* player);
	void CreatureNotOnDefenceAndPartialAP(Creature* player);

	void LowHealth_CreatureOnDefenceAndFullAP(Creature* player);
	void LowHealth_CreatureOnDefenceAndPartialAP(Creature* player);

	void LowHealth_CreatureNotOnDefenceAndFullAP(Creature* player);
	void LowHealth_CreatureNotOnDefenceAndPartialAP(Creature* player);
};

