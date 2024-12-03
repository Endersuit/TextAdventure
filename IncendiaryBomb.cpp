#include "IncendiaryBomb.h"
#include "CombactManager.h"
#include <iostream>
void IncendiaryBomb::UseConsumable(Creature* creature)
{
	std::cout << " bomba incediaria usata su  " << creature->ReturnCreatureName() << std::endl;
	creature->GetDamage(damage);	
}
