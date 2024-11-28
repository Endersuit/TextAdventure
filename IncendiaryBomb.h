#pragma once
#include"Consumable.h"
#include"Creature.h"
class IncendiaryBomb : public Consumable
{
public :
	
	virtual void UseConsumable(Creature* target) //funzione ereditata da consumable, prende in input
		//un puntatore alla  creatura
	{
		//logica per scegliere il bersaglio
	}

private:

	float damage = 8;
};

