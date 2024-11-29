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

//perettere all attacante di dannegiare il bersaglio
void CombactManager::TargetAttack(Creature* attacker, Creature* target)
{
    if (attacker->ReturnIsOnDefence())
    {
        std::cout << "la creatura e sulla difensiva, non puo attacare " << std::endl;
    }
    else
    {
        target->GetDamage(attacker->ReturnAttack());
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//far scegliere al giocatore cosa fare (WIP)
void CombactManager::ChooseAction()
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
            std::cout << "scegli un bersaglio" << std::endl;
            TargetAttack(player,ChooseAnEnemy());
            //TO DO : chiedere al giocatore cosa vule fare con il nemico scelto
            break;
        case 2:
            std::cout << "usa un consumabile" << std::endl;
            //TO DO : usare il consumabile
            break;
        case 3:
            player->SetInDefenceMode(!player->ReturnIsOnDefence());
            break;


    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

//TO DO : restituire un puntatore del nemico tramire index
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

//restituire un puntatore al nemico (selezionato tramite console)
Creature* CombactManager::ChooseAnEnemy()
{
    if (!enemies.empty())
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            //TO DO : creare una funzione che stampi le statistiche attuali del nemico
            std::cout << " creatura : " + enemies[i].get()->ReturnCreatureName() << " indice  : " << i << std::endl;
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
/////////////////////////////////////////////////////////////////////////////////////////////////////

//controlla se il nemico scelto e utilizabile
bool CombactManager::CheckIfSelectionIsAvaible(Creature* selcetedCreature)
{
    //un nemico e considerato "utilizabile" se ha : 
    //salute > 0
    //AAP (avaible action points) > 0

    if (selcetedCreature->ReturnAAP() > 0 && selcetedCreature->ReturnCurrentHealth() > 0)
    {
        std::cout << "la  creatura "<< selcetedCreature->ReturnCreatureName() <<" e disponibile " << std::endl;
        return true;
    }
    else
    {
        std::cout << "la creatura " << selcetedCreature->ReturnCreatureName() << " non e disponibile " << std::endl;
        return false;
    }
        
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

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
