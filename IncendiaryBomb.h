#pragma once
#include"Consumable.h"
#include"Creature.h"
class IncendiaryBomb : public Consumable
{
public :
	
	virtual void UseConsumable(Creature* target); //funzione ereditata da consumable, prende in input

private:

	float damage = 8;
};

