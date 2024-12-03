
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"
int main()
{
    Creature* player = new Creature("Kalagan", 20, 4, 5, false);

    //puntatori smart unici -> gestione automatica della memoria
    //nemici Round One
    std::unique_ptr<Creature> endersuit = std::make_unique<Creature>("Endersuit", 20, 6, 5, false);
    std::unique_ptr<Creature> enderman = std::make_unique<Creature>("Enderman", 0, 1, 50, false);
    std::unique_ptr<Creature> endermite = std::make_unique<Creature>("Endermite", 1, 1, 1, false);
    
    //array dinamico ci puntatori unici
    std::vector<std::unique_ptr<Creature>> roundOneEnemies;
   

    //trasferire i puntatori dei nemici in una nuova posizione
    //roundOneEnemies.push_back(std::move(endersuit));
    roundOneEnemies.push_back(std::move(enderman));
    roundOneEnemies.push_back(std::move(endermite));
    
    //passare la lista di nemici per questo round
    CombactManager::Get().SetEnemies(std::move(roundOneEnemies));
    CombactManager::Get().SetPlayer(player);

    //DEBUG 
    CombactManager::Get().StartAndManageFight();
}


