
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"
int main()
{
    Creature* player = new Creature("Kalagan", 20, 4, 5, true);
    Creature* endersuit = new Creature("Endersuit", 20, 6, 5, true);
    Creature* enderman = new Creature("Enderman", 20, 1, 2, true);
    Creature* enderman1 = new Creature("Endermite", 5, 1, 1, true);

    std::vector<Creature*> enemies = { endersuit, enderman, enderman1 };

    CombactManager combactManager(player,enemies);
    combactManager.ChooseAnEnemy();
    //int number = combactManager.ReturnRandomnumber(3);
    //Creature* selection = combactManager.ReturnSelectedEnemy(number);
    //combactManager.CheckIfSelectionIsAvaible(selection);


}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

