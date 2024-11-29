
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"
int main()
{
    //nemici Round One

    //puntatori smart unici -> gestione automatica della memoria
    std::unique_ptr<Creature> player = std::make_unique<Creature>("Kalagan", 20, 4, 5, true);
    std::unique_ptr<Creature> endersuit = std::make_unique<Creature>("Endersuit", 20, 6, 5, true);
    std::unique_ptr<Creature> enderman = std::make_unique<Creature>("Enderman", 20, 1, 2, true);
    std::unique_ptr<Creature> enderman1 = std::make_unique<Creature>("Endermite", 5, 1, 1, true);
    
    //trasferire i puntatori in una nuova posizione 
    std::vector<std::unique_ptr<Creature>> roundOneEnemies;

    roundOneEnemies.push_back(std::move(endersuit));
    roundOneEnemies.push_back(std::move(enderman));
    roundOneEnemies.push_back(std::move(enderman1));
    
    CombactManager::Get().SetEnemies(std::move(roundOneEnemies));

    CombactManager::Get().ReturnSelectedEnemy(0);

}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

