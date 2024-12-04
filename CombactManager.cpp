#include "CombactManager.h"
#include "Creature.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
//TO DO : convertire in un singleton Pattern : 
//2) creare una funzione per passare in Input un giocatore o dei nemici

//////////////////////////////////////////////////SET//////////////////////////////////////////////////

//imposta il giocatore principale
void CombactManager::SetPlayer(Creature* player)
{
    if (player != nullptr)
    {
        this->player = player;
    }
}

//trasferire in puntatori unici all array dinamico di  combactManager
void CombactManager::SetEnemies(std::vector<std::unique_ptr<Creature>>&& enemies)
{
    this->enemies.clear();

    if (!enemies.empty()) {
        this->enemies = std::move(enemies);  // Trasferisci la proprietà
    }
}

//////////////////////////////////////////GESTIONE COMBATTIMENTO/////////////////////////////////////////

//iniziare e gestire il combattimento
void CombactManager::StartAndManageFight()
{
    
    bool fightInProgress = true; //il combattimento procedera fino alla sconfitta di uno dei contedenti
    bool isPlayerTurn = true; //il giocatore inizia sempre per primo

    while (fightInProgress)
    {
        //logica per la gestione dei turni (WIP)
        
        fightInProgress = !CheckForPossibleWinner();
        if (!fightInProgress)
            break;
        isPlayerTurn = CheckIfSelectionIsAvaible(player) ? true : false;

        if (isPlayerTurn)
        {
            std::cout << "_________________________________________________________________________________________________" << std::endl;
            std::cout << std::endl;
            PrintCreatureInfo(player);
            std::cout << "_________________________________________________________________________________________________" << std::endl;
            std::cout << std::endl;
            PrintCreaturesInfo();
            std::cout << "_________________________________________________________________________________________________" << std::endl;
            std::cout << std::endl;
            ChooseAnAction();
            continue; //torna dentro il ciclo while
        }
        else
            if(!isPlayerTurn &&  CheckIfEnemiesAlive())
        {
            std::cout << " turno dell 'IA " << std::endl;
            std::cout << std::endl;
            AnalyzeAndDecide();
            continue;
        }
    }
}

//descrizione
void CombactManager::AnalyzeAndDecide()
{
    int enemiesAmount = enemies.size();
    int avaibleEnemies = 0;

    //controlla se almeno un nemico e utilizabile
    for (auto& creature : enemies) {

        creature.get()->RestoreActionPoints();
        if (CheckIfSelectionIsAvaible(creature.get()))
            avaibleEnemies++;
    }

    SwapEnemiesArray();
    while (avaibleEnemies > 0 && player->ReturnCurrentHealth() > 0)
    {
        //controlla quanti nemici sono ancora disponibili

        std::cout << "l'IA inizia a  fare la sua scelta" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < enemies.size() - 1;i++)
        {

            if (!CheckIfSelectionIsAvaible(enemies[i].get()))
            {
                avaibleEnemies -= 1;
                continue;
            }
            /////////////////////////////////la creatura ha HP > 50%////////////////////////////////////////
            if (CheckCreatureIsHighOnHealth(enemies[i].get()))
            {
                /*std::cout << " salute della creatura scelta > 50% " << std::endl;*/

                //la creatura E' sulla DIFENSIVA
                if (enemies[i]->ReturnIsOnDefence())
                {
                    std::cout << " la creatura e sulla difensiva e ha hp > 50% " << std::endl;
                    std::cout << std::endl;

                    //APP completamente disponibili
                    if (CheckCreatureIsFullAP(enemies[i].get()))
                    {
                        std::cout << " AAP della creatura scelta completamente disponibili " << std::endl;
                        std::cout << std::endl;
                        enemies[i]->SetInDefenceMode(false);
                        TargetAttack(enemies[i].get(), player);
                    }
                    //APP PARZIALMENTE disponibili
                    else
                    {
                        std::cout << " AAP della creatura scelta parzialmente disponibili " << std::endl;
                        std::cout << std::endl;
                        
                        int consumableType = enemies[i].get()->ReturnConsumableType();
                        switch (consumableType)
                        {
                        case(0): //nessun consumabile-> rimane in difesa, salta il turno                           
                            enemies[i].get()->ClearActionPoints();
                            continue;

                        case(1): //pozione di cura-> resta in difesa, non ha bisgno di curarsi
                            enemies[i].get()->ClearActionPoints();
                            continue;


                        case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico
                            enemies[i].get()->UseConsumable(player);
                            continue;
                        }
                    }
                }
                // la creatura NON e sulla DIFENSIVA e ha hp > 50%
                else
                {
                    std::cout << " la creatura NON e sulla difensiva e ha hp > 50%  " << std::endl;
                    std::cout << std::endl;

                    //APP COMPLETAMENTE disponibili
                    if (CheckCreatureIsFullAP(enemies[i].get()))
                    {
                        TargetAttack(enemies[i].get(), player);

                        if (ReturnRandomBool()) //l'IA sceglie se farlo o meno
                        {
                            std::cout << " l'IA ha scelto di ATTACARE di NUOVO " << std::endl;
                            std::cout << std::endl;
                            TargetAttack(enemies[i].get(), player);
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
                            TargetAttack(enemies[i].get(), player);
                        }
                        else
                        {
                            enemies[i]->SetInDefenceMode(true);
                            std::cout << " l'IA ha scelto di NON ATTACARE di NUOVO  e tenere la creatura sulla DIFESA" << std::endl;
                            std::cout << std::endl;
                        }
                    }
                }
            }
            /////////////////////////////////la creatura ha HP < 50%////////////////////////////////////////
            else
            {

                //la creatura E' sulla DIFENSIVA
                if (enemies[i]->ReturnIsOnDefence())
                {
                    std::cout << " la creatura e sulla DIFENSIVA e ha HP < 50% " << std::endl;
                    std::cout << std::endl;

                    //APP COMPLETAMENTE disponibili
                    if (CheckCreatureIsFullAP(enemies[i].get()))
                    {
                        //il GIOCATORE puo essere UCCISO con un ATTACO
                        if (player->ReturnCurrentHealth() <= enemies[i]->ReturnAttack())
                        {
                            std::cout << " il giocatore puo essere ucciso con un attaco, lascia la difesa e attaca " << std::endl;
                            std::cout << std::endl;
                            enemies[i]->SetInDefenceMode(false);
                            TargetAttack(enemies[i].get(), player);
                        }
                        //il GIOCATORE  NON puo essere UCCISO con un ATTACO
                        else
                        {
                            int consumableType = enemies[i].get()->ReturnConsumableType();
                            switch (consumableType)
                            {
                            case(0): //nessun consumabile-> sceglie se attacare                            
                                if (ReturnRandomBool())
                                {//lascia la difesa e attaca
                                    enemies[i].get()->SetInDefenceMode(false);
                                    TargetAttack(enemies[i].get(), player);
                                }
                                else
                                {//resta in difesa, salta il turno
                                    enemies[i].get()->ClearActionPoints();
                                }
                                continue;

                            case(1): //pozione di cura-> resta in difesa, si cura, il nemico salta il turno
                                enemies[i].get()->UseConsumable(enemies[i].get());
                                enemies[i].get()->ClearActionPoints();
                                continue;


                            case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico, salta il turno
                                enemies[i].get()->UseConsumable(player);
                                enemies[i].get()->ClearActionPoints();
                                continue;
                            }
                        }
                    }
                    //APP PARZIALMENTE disponibili
                    else
                    {
                        std::cout << " AAP della creatura scelta parzialmente disponibili " << std::endl;
                        std::cout << std::endl;
                        int consumableType = enemies[i].get()->ReturnConsumableType();
                        switch (consumableType)
                        {
                        case(0): //nessun consumabile-> rimane in difesa, salta il turno                           
                            enemies[i].get()->ClearActionPoints();
                            continue;

                        case(1): //pozione di cura-> resta in difesa, si cura
                            enemies[i].get()->UseConsumable(enemies[i].get());
                            enemies[i].get()->ClearActionPoints();
                            continue;


                        case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico
                            enemies[i].get()->UseConsumable(player);
                            continue;
                        }
                    }
                }
                //la creatura NON e sulla DIFENSIVA
                else
                {
                    std::cout << " la creatura NON e  sulla Difensiva e ha HP < 50% " << std::endl;
                    std::cout << std::endl;

                    //APP COMPLETAMENTE disponibili
                    if (enemies[i]->ReturnAAP() >= enemies[i]->ReturnActionPointsPerTurn())
                    {
                        std::cout << " la creatura ATTACA e DIFENDE " << std::endl;
                        std::cout << std::endl;
                        TargetAttack(enemies[i].get(), player);
                        enemies[i]->SetInDefenceMode(true);
                    }
                    //APP PARZIALMENTE disponibili
                    else
                    {
                        //il GIOCATORE puo essere UCCISO con un ATTACO
                        if (player->ReturnCurrentHealth() <= enemies[i]->ReturnAttack())
                        {
                            std::cout << " il giocatore puo esser eucciso con un attaco, la creatura attaca " << std::endl;
                            std::cout << std::endl;
                            TargetAttack(enemies[i].get(), player);
                        }
                        //il GIOCATORE  NON puo essere UCCISO con un ATTACO
                        else
                        {
                            std::cout << " la creatura cerca di DIFENDERSI " << std::endl;
                            std::cout << std::endl;
                            enemies[i]->SetInDefenceMode(true);
                        }
                    }
                }
            }
        }
        if (avaibleEnemies <= 0)
        {
            std::cout << "non ci sono nemici disponibili -> turno del giocatore" << std::endl;
            std::cout << std::endl;
            if (player->ReturnCurrentHealth() > 0)
                player->RestoreActionPoints();
            return;
        }
    }
}

//far scegliere al giocatore cosa fare 
void CombactManager::ChooseAnAction()
{
    int selection = 0;
    std::string message = (player->ReturnIsOnDefence()) ? " alzata) " : " abbasata) ";

    std::cout << "fai la tua scelta digitando il numero corrispodente : \n (1) : scegli un nemico e attaca \n (2) : usa un consumabile \n (3) : entra/esci  in/dalla difensiva (attualmente la tua difesa e " << message << "\n (4) : salta il turno "<< std::endl;
    std::cout << std::endl;
    while (selection < 1 || selection > 4)
    {
        std::cin >> selection;
    }

    switch (selection)
    {
    case 1:
        std::cout << " hai scelto di attacare un bersaglio" << ::std::endl;
        std::cout << std::endl;
        TargetAttack(player, ChooseAnEnemyOnConsole());
        //TO DO : chiedere al giocatore cosa vule fare con il nemico scelto
        break;
    case 2:
        //TO DO : usare il consumabile
        CheckAndUseConsumableForPlayer(player);
        break;
    case 3:
        std::cout << " hai scelto di cambiare la tua difesa " << ::std::endl;
        std::cout << std::endl;
        player->SetInDefenceMode(!player->ReturnIsOnDefence());
        break;
    case 4 :
        std::cout << " hai scelto di saltare il turno " << ::std::endl;
        std::cout << std::endl;
        player->ClearActionPoints();
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
        attacker->Attack(target);
    }
}

//////////////////////////////////////////////////UTILITA///////////////////////////////////////////////

//rimescola i nemici all interno dell array in maniera casuale 
void CombactManager::SwapEnemiesArray()
{
    int numberOfInteractions = ReturnRandomnumber(enemies.size());
    std::cout << "interazioni : " << numberOfInteractions +1 << std::endl;
    for (int i = 0; i < (numberOfInteractions + 1); i++)
    {
        int firstIndex = ReturnRandomnumber(enemies.size());
        int secondIndex = ReturnRandomnumber(enemies.size());

        while (firstIndex == secondIndex)
        {
            secondIndex = ReturnRandomnumber(enemies.size());
        }
        
        std::cout << "primo indice : " << firstIndex << std::endl;
        std::cout << "secondo indice : " << secondIndex << std::endl;
        
        if (enemies[firstIndex] && enemies[secondIndex])
        {
            std::cout << "scambio i nemici " << std::endl;
           enemies[firstIndex].swap(enemies[secondIndex]);
        }
    }
}

//stampa su console tutte le statistiche della creatura scelta 
//creatureToPrint : la creatura da stampare
//e il suo indice nell array
//per stampare il giocatore , non serve assegnare un indice quando richiami la funzione
void CombactManager::PrintCreatureInfo(Creature* creatureToPrint, int index)
{
    if (!creatureToPrint)//controlla se il puntatore e null
    {
        std::cout << "ERRORE, PUNTATORE NULLO" << std::endl;
        return;
    }
     
    if (creatureToPrint != player)//se NON e un giocatore
    {
        std::string defenceStatus = (creatureToPrint->ReturnIsOnDefence()) ? "alzata" : "abbasata";
        std::cout << "|| Nome : " << creatureToPrint->ReturnCreatureName() << " || salute attuale : " << creatureToPrint->ReturnCurrentHealth() << " || difesa : " << defenceStatus << " || attaco : " << creatureToPrint->ReturnAttack() << " || indice : " << index << " ||" << std::endl;
    }
    else  
        //se e un giocatore
    {
            std::string defenceStatus = (creatureToPrint->ReturnIsOnDefence()) ? "alzata" : "abbasata";
            std::cout << "|| Nome : " << creatureToPrint->ReturnCreatureName() << " || salute attuale : " << creatureToPrint->ReturnCurrentHealth() << " || difesa : " << defenceStatus << " || attaco : " << creatureToPrint->ReturnAttack() << " || " << std::endl;
            
            int consumableType = player->ReturnConsumableType();
        switch (consumableType)
        { 
            case 0:
                std::cout << "slot consumabile : vuoto " << std::endl;
                break;
            case 1:
                std::cout << "slot consumabile : pozione di cura " << std::endl;
                break;
            case 2:
                std::cout << "slot consumabile : bomba incendiaria " << std::endl;
                break;
            default:
                std::cout << "slot consumabile : tipo sconosciuto " << std::endl;
                break;
        }
    }
}

//stampa le informazioni di tutti i nemici sullo schermo
void CombactManager::PrintCreaturesInfo()//uso uan reference(&) costante per passare i valori ma evitare modifiche accidentali 
{
    int index = 0;
    for (auto& creature : enemies) {
        if (creature.get()->ReturnCurrentHealth() > 0)
        {
            index++;
            PrintCreatureInfo(creature.get(), index);
        }
    }
}


//restituisce casualmente TRUE o FALSE
bool CombactManager::ReturnRandomBool()
{
    srand(time(NULL)); //imposto il seme di generazione casuale
    int num = rand();
    bool intention = (num % 2 == 0) ? true : false ;
    std::cout << "IA ha fatto la sua scelta :  " << intention << std::endl;
    return intention;
}

//restituisce un numero  casuale compresso tra 0 e N
int CombactManager::ReturnRandomnumber(int n)
{
    srand(time(NULL)); //imposto il seme di generazione casuale
    int number = rand() % n ;
    /*std::cout << " numero scelto  :  " << number << std::endl;*/
    return number;
}

//restituire un puntatore al nemico (selezionato tramite console)
Creature* CombactManager::ChooseAnEnemyOnConsole()
{
    if (!enemies.empty())
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            if (enemies[i].get()->ReturnCurrentHealth() > 0)
            {
                PrintCreatureInfo(enemies[i].get(), i);
                std::cout << " indice  : " << i << std::endl;
                std::cout << std::endl;
            }
        }

        int index = -1;
        std::cout << " digita l'indice corrispodente per selezionare una creatura " << std::endl;
        std::cout << std::endl;

        while (index < 0 || index >= enemies.size() || enemies[index].get()->ReturnCurrentHealth() <= 0)
        {
            std::cin >> index;
        }

        return ReturnSelectedEnemy(index);
    }
    else
    {
        std::cout << "non ho nemici nella lista";
        std::cout << std::endl;
    }
    return nullptr;
}

//restituire un puntatore del nemico tramire index
Creature* CombactManager::ReturnSelectedEnemy(int index)
{
    if (!enemies.empty())
    {
        //restituisce il puntatore
        std::cout << "nemico scelto : " << enemies[index].get()->ReturnCreatureName() << std::endl;
        std::cout << std::endl;
        return enemies[index].get();
    }
    else
    {
        std::cout << "non ho nemici nella lista";
        std::cout << std::endl;
    }
    return nullptr;
}

//ritorna TRUE se il nemico scelto e utilizabile.
//un nemico e considerato "utilizabile" se soddisfa etrambe le condizioni : 
//salute > 0
//AAP (avaible action points) > 0
bool CombactManager::CheckIfSelectionIsAvaible(Creature* selcetedCreature)
{
    if (selcetedCreature->ReturnAAP() > 0 && selcetedCreature->ReturnCurrentHealth() > 0)
    {
        std::cout << "la  creatura "<< selcetedCreature->ReturnCreatureName() <<" e disponibile " << std::endl;
        std::cout << std::endl;
        return true;
    }
    else
    {
        std::cout << "la creatura " << selcetedCreature->ReturnCreatureName() << " non e disponibile " << std::endl;
        std::cout << std::endl;
        return false;
    }
}

//restituisce TRUE se la salute della creatura e superiore al 50%
bool CombactManager::CheckCreatureIsHighOnHealth(Creature* creature)
{
    if (creature->ReturnCurrentHealth() > (creature->ReturnMaxHealth() / 2))
        return true;

    return false;
}

//restituisce TRUE  se la creatura ha AAP al massimo
bool CombactManager::CheckCreatureIsFullAP(Creature* creature)
{
    if (creature->ReturnAAP() >= creature->ReturnActionPointsPerTurn())
        return true;

    return false;
}

//restituisce True se ce almeno un nemico con salute > 0
bool CombactManager::CheckIfEnemiesAlive()
{
    bool enemyAvaible = false;
    if (!enemies.empty())
    {
        for (auto& creature : enemies) {
            if (creature->ReturnCurrentHealth() > 0)
            {
                enemyAvaible = true;
                break;
            }
        }
    }
    return enemyAvaible;
}

//controlla se c'e un vincitore
bool CombactManager::CheckForPossibleWinner()
{
    //controlla chi e ancora vivo tra i giocatori o i nemici
    if (player->ReturnCurrentHealth() <= 0 && CheckIfEnemiesAlive())
    {
        std::cout << "il nemico ha vinto :-(" << std::endl;
        std::cout << std::endl;
        return true;
    }
    else
        if ((player->ReturnCurrentHealth() >= 0 && !CheckIfEnemiesAlive()))
        {
            std::cout << "il giocatore ha vinto! =) " << std::endl;
            std::cout << std::endl;
            return true;
        }
    return false;
}
//controlla e permette di usare il consumabile del giocatore
void::CombactManager::CheckAndUseConsumableForPlayer(Creature* creature)
{
    int consumableType = creature->ReturnConsumableType();
    switch (consumableType)
    {
    case(0): //consumabile nullo -> non possiede nessun consumabile
        std::cout << "non possiedi nessun consumabile" << std::endl;
        std::cout << std::endl;
        break;

    case(1): //pozione di cura
        std::cout << "hai scelto di usare una pozione di cura" << std::endl;
        std::cout << std::endl;
        player->UseConsumable(player);
        break;
    case(2):
        //bomba incendiaria
        std::cout << "hai scelto di usare una bomba. scegli su chi vuoi usarla" << std::endl;
        std::cout << std::endl;
        player->UseConsumable(ChooseAnEnemyOnConsole());
        break;
    }
}
