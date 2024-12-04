
#include <iostream>
#include <vector>

#include "CombactManager.h"
#include "Creature.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"

bool getUserDecision();
int main()
{
////////////////////////////////////////////////////////////////SETUP////////////////////////////////////////////////////////////////
    
    std::cout << "lo sapevi che questo gioco ti permette di scegliere un nome ? dovresti approfitarne"<< std::endl;
    std::string playerName = "";
    bool nameChosen = false;

    while (nameChosen == false)
    {
        std::cout << "digita un nome proprio qui , non premere invio senza aver inserito almeno un nome : ";
        std::getline(std::cin, playerName); //getline prende l'intera linea , inclusa la linea vuota
        std::cout << std::endl;

        if (playerName._Equal("Endersuit") || (playerName._Equal("endersuit"))) //piccolo easter egg
        {
            std::cout << playerName << "? strano, mi  sembra familiare, ";
        }
        else 
            if(playerName.empty()) 
            { 
                playerName = "Odisseo";
                std::cout <<"visto che ti piace fare lo spiritoso spiritoso, da ora ti chiamero Odisseo "<< std::endl;
                std::cout << "quando sei pronto premi 1 sulla tua tastiera : ";
                nameChosen = getUserDecision();
                break;
            }
        std::cout << "sicuro della scelta(1 : si, 0 : no) ? " << std::endl;
        std::cout << std::endl;
        nameChosen = getUserDecision();
    }

    Creature* player = new Creature(playerName, 15, 4, 10, false, std::make_unique<IncendiaryBomb>());
    
/////////////////////////////////////////////////////////INTRODUZIONE////////////////////////////////////////////////////////////////
    
    std::cout << std::endl;
    std::cout << "il tuo nome e " << player->ReturnCreatureName()
        << "che è diviso su più righe per "
        << "essere più leggibile." << std::endl;
/////////////////////////////////////////////////////////TUTORIAL////////////////////////////////////////////////////////////////
    //nemici tutorial
    std::unique_ptr<Creature> trainingMannequin = std::make_unique<Creature>("Endersuit", 17, 14, 4, true, std::make_unique<HealingPotion>());
    std::unique_ptr<Creature> trainingMannequin1 = std::make_unique<Creature>("Enderman", 7, 4, 2, true, std::make_unique<IncendiaryBomb>());
    
    
    //puntatori smart unici -> gestione automatica della memoria
    //nemici Round One
    std::unique_ptr<Creature> endersuit = std::make_unique<Creature>("Endersuit", 17, 14, 4, true, std::make_unique<HealingPotion>());
    std::unique_ptr<Creature> enderman = std::make_unique<Creature>("Enderman", 7, 4, 2, true, std::make_unique<IncendiaryBomb>());
    std::unique_ptr<Creature> endermite = std::make_unique<Creature>("Endermite", 6, 1, 4, true, nullptr);
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
    
    //chiudere l'eseguibile solo quando l'utente lo desidera 
    std::cout << " digita 1 per uscire" << std::endl;
    char input;
    do {
        std::cin >> input;
    } while (input != '1');
    return 0;
}

//restituisce TRUE(equivalente a un si) o FALSE (equivalente a un no)
bool getUserDecision()
{
    int userChoice = -1;
    while (userChoice < 0 || userChoice > 1)
    {
        std::cin >> userChoice;
    }
    return (userChoice == 1) ? true : false;
}
