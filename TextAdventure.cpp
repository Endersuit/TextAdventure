
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"
int main()
{
    Creature* player = new Creature("Kalagan", 15, 4, 10, false, nullptr);

    //puntatori smart unici -> gestione automatica della memoria
    //nemici Round One
    std::unique_ptr<Creature> endersuit = std::make_unique<Creature>("Endersuit", 10, 6, 5, true, std::make_unique<HealingPotion>());
    std::unique_ptr<Creature> enderman = std::make_unique<Creature>("Enderman", 10, 1, 1, true, std::make_unique<IncendiaryBomb>());
    std::unique_ptr<Creature> endermite = std::make_unique<Creature>("Endermite", 1, 1, 1, false, nullptr);
    
    //array dinamico ci puntatori unici
    std::vector<std::unique_ptr<Creature>> roundOneEnemies;
   
    //trasferire i puntatori dei nemici in una nuova posizione
    roundOneEnemies.push_back(std::move(endersuit));
    roundOneEnemies.push_back(std::move(enderman));
    roundOneEnemies.push_back(std::move(endermite));
    

    //passare la lista di nemici per questo round
    CombactManager::Get().SetEnemies(std::move(roundOneEnemies));
    CombactManager::Get().SetPlayer(player);

    //DEBUG 
    CombactManager::Get().StartAndManageFight();
}


