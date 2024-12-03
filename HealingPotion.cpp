#include "HealingPotion.h"

void HealingPotion::UseConsumable(Creature* creature)
{
		creature->GetDamage(-healAmount);
}
