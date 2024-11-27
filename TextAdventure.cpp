
#include <iostream>
#include "Creature.h"
#include "HealingPotion.h"
int main()
{
	Creature Monster ("Endersuit", 10, 2, 2, 5, true);
	Creature Player("Kalagan",20, 2, 2, 5, true);
	
	Player.EquipConsumable(new HealingPotion);
	Monster.Attack(Player);
	Player.UseConsumable();
	Player.UseConsumable();
	return 0;
}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

