#pragma once
#include "Enemy.h"
class NormalEnemy:Enemy
{
	virtual void AnalyzeAndDecide(Creature* player);


private :
	bool debug;

	void CreatureOnDefenceAndFullAP(Creature* player);
	void CreatureOnDefenceAndPartialAP(Creature* player);

	void CreatureNotOnDefenceAndFullAP(Creature* player);
	void CreatureNotOnDefenceAndPartialAP(Creature* player);

	void LowHealth_CreatureOnDefenceAndFullAP(Creature* player);
	void LowHealth_CreatureOnDefenceAndPartialAP(Creature* player);

	void LowHealth_CreatureNotOnDefenceAndFullAP(Creature* player);
	void LowHealth_CreatureNotOnDefenceAndPartialAP(Creature* player);
};

