#pragma once
#include"Consumable.h"
#include"Creature.h"
class HealingPotion : public Consumable
{
public :

	virtual void UseConsumable(Creature* creature); //funzione ereditata da consumable, prende in input
private : 

	float healAmount = 5;
};

