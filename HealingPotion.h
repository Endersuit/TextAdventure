#pragma once
#include"Consumable.h"
#include"Creature.h"
class HealingPotion : public Consumable
{
public :

	
	virtual void UseConsumable(Creature* creature) //funzione ereditata da consumable, prende in input
		//un riferimento
	{
		creature->GetDamage(-healAmount);
	}
private : 
	float healAmount = 5;
};

