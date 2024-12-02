#include "CombactManager.h"
#include "Creature.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//TO DO : convertire in un singleton Pattern : 
//2) creare una funzione per passare in Input un giocatore o dei nemici

//////////////////////////////////////////////////SET//////////////////////////////////////////////////

void CombactManager::SetPlayer(Creature* player)
{
    if (player != nullptr)
    {
        this->player = player;
    }
}

//trasferire in puntatori unici al combactManager
void CombactManager::SetEnemies(std::vector<std::unique_ptr<Creature>>&& enemies)
{
    this->enemies.clear();

    if (!enemies.empty()) {
        this->enemies = std::move(enemies);  // Trasferisci la proprietà
    }
}

//iniziare e gestire il combattimento
void CombactManager::StartAndManageFight()
{
    //1) : inizia il combattimento
    //2) : cede il controllo al gicatore o all'IA
    //3) : si rimara nel flusso finche uno dei due vince
    
    //TO DO : creare una funzione che restituisca bool/false se ci sono nemici ancora vivi
    bool fightInProgress = true; //il combattimento procedera fino alla sconfitta di uno dei contedenti
    bool isPlayerTurn = true; //il giocatore inizia sempre per primo

    while (fightInProgress)
    {
        //logica per la gestione dei turni (WIP)

        //e il turno del giocatore se :
        //1) actionPoints > 0
        //2) health > 0 
        //i punti azione vengono ripristinati alla fine del turno nemico 
        
        isPlayerTurn = CheckIfSelectionIsAvaible(player) ? true : false;

        if (isPlayerTurn)
        {
            PrintCreatureInfo();
            ChooseAnAction();
            continue; //torna dentro il ciclo while
        }
        else
            if(!isPlayerTurn &&  CheckIfEnemiesAlive())
        {
            std::cout << " turno dell 'IA " << std::endl;
            AnalyzeAndDecide();
            return;
        }

        //TO DO : controllare se c'e un vincitore
    }
}

void CombactManager::AnalyzeAndDecide()
{
    int enemiesAmount = enemies.size();
    int avaibleEnemies = 0;
    
    //controlla se almeno un nemico e utilizabile
    for (auto& creature : enemies) {
        
        if(CheckIfSelectionIsAvaible(creature.get())) 
            avaibleEnemies++;
    }

    //TO DO : convertire in un cliclo while e aggiornare il numero di nemici disponibili  
    if (avaibleEnemies > 0)
    {
        Creature* chosenCreature = nullptr;
        bool selectionAvaible = false;
        
        while(!selectionAvaible)
        {
            chosenCreature = ReturnSelectedEnemy(ReturnRandomnumber(enemiesAmount - 1));
            selectionAvaible = (CheckIfSelectionIsAvaible(chosenCreature)) ? true : false;
        } 

        // la creatura ha HP > 50%
        if (chosenCreature->ReturnCurrentHealth() > (chosenCreature->ReturnMaxHealth() / 2))
        {
            /*std::cout << " salute della creatura scelta > 50% " << std::endl;*/
            
            //la creatura E' sulla DIFENSIVA
            if (chosenCreature->ReturnIsOnDefence())
            {
                std::cout << " la creatura e sulla difensiva e ha hp > 50% " << std::endl;
                std::cout << std::endl;
                
                //APP completamente disponibili
                if (chosenCreature->ReturnAAP() >= chosenCreature->ReturnActionPointsPerTurn())
                {
                    std::cout << " AAP della creatura scelta completamente disponibili " << std::endl;
                    std::cout << std::endl;
                    chosenCreature->SetInDefenceMode(false);
                    TargetAttack(chosenCreature, player);
                }
                //APP PARZIALMENTE disponibili
                else
                {
                    std::cout << " AAP della creatura scelta parzialmente disponibili " << std::endl;
                    std::cout << std::endl;
                    chosenCreature->ClearActionPoints();
                }
            }
            // la creatura NON e sulla DIFENSIVA e ha hp > 50%
            else 
            {
                std::cout << " la creatura NON e sulla difensiva e ha hp > 50%  " << std::endl;
                std::cout << std::endl;

                //APP COMPLETAMENTE disponibili
                if (chosenCreature->ReturnAAP() >= chosenCreature->ReturnActionPointsPerTurn())
                {
                    TargetAttack(chosenCreature, player);

                    if (ReturnRandomBool()) //l'IA sceglie se farlo o meno
                    {
                        std::cout << " l'IA ha scelto di ATTACARE di NUOVO " << std::endl;
                        std::cout << std::endl;
                        TargetAttack(chosenCreature, player);
                    }
                    else
                    {
                        //nietne
                        std::cout << " l'IA ha scelto di NON ATTACARE di NUOVO " << std::endl;
                        std::cout << std::endl;
                    }
                }
                //APP PARZIALMENTE disponibili
                else 
                {
                    if (ReturnRandomBool())
                    {
                        std::cout << " l'IA ha scelto di ATTACARE di NUOVO " << std::endl;
                        std::cout << std::endl;
                        TargetAttack(chosenCreature, player);
                    }
                    else
                    {
                        chosenCreature->SetInDefenceMode(true);
                        std::cout << " l'IA ha scelto di NON ATTACARE di NUOVO  e tenere la creatura sulla DIFESA" << std::endl;
                        std::cout << std::endl;
                    }
                }
            }
        }
        //la creatura ha HP <= 50%
        else
        {
            /*std::cout << " salute della creatura scelta <= 50% " << std::endl;*/
            
            //la creatura E' sulla DIFENSIVA
            if (chosenCreature->ReturnIsOnDefence())
            {
                std::cout << " la creatura e sulla DIFENSIVA e ha HP < 50% " << std::endl;
                std::cout << std::endl;
            }
            //la creatura NON e sulla DIFENSIVA
            else
            {
                std::cout << " la creatura NON e  sulla Difensiva e ha HP < 50% " << std::endl;
                std::cout << std::endl;

                //APP COMPLETAMENTE disponibili
                if (chosenCreature->ReturnAAP() >= chosenCreature->ReturnActionPointsPerTurn())
                {
                    std::cout << " la creatura ATTACA e DIFENDE " << std::endl;
                    std::cout << std::endl;
                    TargetAttack(chosenCreature, player);
                    chosenCreature->SetInDefenceMode(true);
                }
                //APP PARZIALMENTE disponibili
                else
                {
                    //il GIOCATORE puo essere UCCISO con un ATTACO
                    if (player->ReturnCurrentHealth() <= chosenCreature->ReturnAttack())
                    {
                        std::cout << " il giocatore puo esser eucciso con un attaco, la creatura attaca " << std::endl;
                        std::cout << std::endl;
                        TargetAttack(chosenCreature, player);
                    }
                    //il GIOCATORE  NON puo essere UCCISO con un ATTACO
                    else
                    {
                        std::cout << " la creatura cerca di DIFENDERSI " << std::endl;
                        std::cout << std::endl;
                        chosenCreature->SetInDefenceMode(true);
                    }
                }
            }
        }
    }
    return;
}

//perettere all attacante di dannegiare il bersaglio
void CombactManager::TargetAttack(Creature* attacker, Creature* target)
{
    if (attacker->ReturnIsOnDefence())
    {
        std::cout << "la creatura e sulla difensiva, non puo attacare " << std::endl;
    }
    else
    {
        attacker->Attack(target);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//far scegliere al giocatore cosa fare (WIP)
void CombactManager::ChooseAnAction()
{
    //TO DO : controllare se il giocatore ha punti azione
    int selection = 0;
    std::string message = (player->ReturnIsOnDefence()) ? " alzata) " : " abbasata) ";
    
    std::cout << "fai la tua scelta digitando il numero corrispodente : \n (1) : scegli un nemico e attaca \n (2) : usa un consumabile \n (3) : entra/esci  in/dalla difensiva (attualmente la tua difesa e  "<< message << std::endl;
    
    while (selection < 1 || selection > 3)
    {
       std:: cin >> selection;
    }

    switch (selection)
    { 
        case 1 :
            TargetAttack(player,ChooseAnEnemy());
            //TO DO : chiedere al giocatore cosa vule fare con il nemico scelto
            break;
        case 2:
            //TO DO : usare il consumabile
            break;
        case 3:
            player->SetInDefenceMode(!player->ReturnIsOnDefence());
            break;


    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//restituire un puntatore del nemico tramire index
Creature* CombactManager::ReturnSelectedEnemy(int index)
{
    if (!enemies.empty())
    {
        //restituisce il puntatore
        std::cout << "nemico scelto : " << enemies[index].get()->ReturnCreatureName() << std::endl;
        return enemies[index].get();
    }
    else
    {
        std::cout << "non ho nemici nella lista";
    }
    return nullptr;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//stampare su console tutte le statistiche della creatura
void CombactManager::PrintCreatureInfo(Creature* creatureToPrint, int index)
{
    if (creatureToPrint)
    {
        std::string defenceStatus = (creatureToPrint->ReturnIsOnDefence()) ? "alzata" : "abbasata";
        std::cout << "|| Nome : " << creatureToPrint->ReturnCreatureName() << " || salute attuale : " << creatureToPrint->ReturnCurrentHealth() << " || difesa : " << defenceStatus << " || attaco : " << creatureToPrint->ReturnAttack() << " || indice : " << index << " ||" << std::endl;
    }
    else
    {
        std::cout << "ERRORE, PUNTATORE NULLO" << std::endl;
    }
}


void CombactManager::PrintCreatureInfo()//uso uan reference(&) costante per passare i valori ma evitare modifiche accidentali 
{
    int index = 0;
    for (auto& creature : enemies) {
        index++;
        PrintCreatureInfo(creature.get(), index);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

//controlla se il nemico scelto e utilizabile
bool CombactManager::CheckIfSelectionIsAvaible(Creature* selcetedCreature)
{
    //un nemico e considerato "utilizabile" se ha : 
    //salute > 0
    //AAP (avaible action points) > 0

    if (selcetedCreature->ReturnAAP() > 0 && selcetedCreature->ReturnCurrentHealth() > 0)
    {
        //std::cout << "la  creatura "<< selcetedCreature->ReturnCreatureName() <<" e disponibile " << std::endl;
        return true;
    }
    else
    {
        //std::cout << "la creatura " << selcetedCreature->ReturnCreatureName() << " non e disponibile " << std::endl;
        return false;
    }       
}


///////////////////////////////////////////////////Return/Output //////////////////////////////////////////////

//restituisce True se ce almeno un nemico con salute > 0
bool CombactManager::CheckIfEnemiesAlive()
{
    bool enemyAvaible = false;
    if (!enemies.empty())
    {
        for (auto& creature : enemies) {
            enemyAvaible = (creature->ReturnCurrentHealth() > 0) ? true : false;
        }
    }
    return enemyAvaible;
}

//restituire true o false casulmente
bool CombactManager::ReturnRandomBool()
{
    srand(time(NULL)); //imposto il seme di generazione casuale
    int num = rand();
    bool intention = (num % 2 == 0) ? true : false ;
    std::cout << "IA ha fatto la sua scelta :  " << intention << std::endl;
    return intention;
}


//restituire un numero  casuale compresso tra 0 e N
int CombactManager::ReturnRandomnumber(int n)
{
    srand(time(NULL)); //imposto il seme di generazione casuale
    int number = rand() % n ;
    std::cout << " numero scelto  :  " << number << std::endl;
    return number;
}

//restituire un puntatore al nemico (selezionato tramite console)
Creature* CombactManager::ChooseAnEnemy()
{
    if (!enemies.empty())
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            PrintCreatureInfo(enemies[i].get(), i);
            std::cout << " indice  : " << i << std::endl;
        }

        int index = -1;
        std::cout << " digita l'indice corrispodente per selezionare una creatura " << std::endl;

        while (index < 0 || index >= enemies.size())
        {
            std::cin >> index;
        }

        return ReturnSelectedEnemy(index);
    }
    else
    {
        std::cout << "non ho nemici nella lista";
    }
    return nullptr;
}
