#include <iostream>
#include "NormalEnemy.h"
#include "Enemy.h"




NormalEnemy::NormalEnemy(std::string creatureName, int maxHealth, float defence, float attack, bool isOnDefensive, std::unique_ptr<Consumable> consumable)
    : Enemy(creatureName, maxHealth, defence, attack, isOnDefensive, std::move(consumable))
{
    debug = true;
    AvaibleActionPoints = 2;
    actionPointsPerTurn = 2;
}

NormalEnemy::NormalEnemy(const NormalEnemy& other)
    :Enemy(other)
{

}

void NormalEnemy::AnalyzeAndDecide(Creature* player)
{
    while (AvaibleActionPoints > 0 && player->ReturnCurrentHealth() > 0)
    {
        std::cout << "punti azione : " << AvaibleActionPoints << std::endl;
        //controlla quanti nemici sono ancora disponibili

        if (debug)
        {
            std::cout << "l'IA inizia a  fare la sua scelta" << std::endl;
            std::cout << std::endl;
        }

        //informazioni sul nemico 
        std::string creatureName = this->ReturnCreatureName();
        bool creatureIsHighOnHealth = CheckCreatureIsHighOnHealth(this);
        bool creatureIsOnDefence = isOnDefensive;
        bool creatureIsFullAP = CheckCreatureIsFullAP(this);

        /////////////////////////////////la creatura ha HP > 50%////////////////////////////////////////
        if (creatureIsHighOnHealth)
        {
            /*std::cout << " salute della creatura scelta > 50% " << std::endl;*/

            if (creatureIsOnDefence && creatureIsFullAP)
            {
                CreatureOnDefenceAndFullAP(player);
            }
            else 
                
                if(creatureIsOnDefence && !creatureIsFullAP) 
                {
                    CreatureOnDefenceAndPartialAP(player);
                }
                
                else
                    if(!creatureIsOnDefence && creatureIsFullAP) 
                    {
                        CreatureNotOnDefenceAndFullAP(player);
                    }
                    else
                        if (!creatureIsOnDefence && !creatureIsFullAP)
                    {
                            CreatureNotOnDefenceAndPartialAP(player);
                    }
        }
                
        /////////////////////////////////la creatura ha HP < 50%////////////////////////////////////////
        else
        {

            //la creatura E' sulla DIFENSIVA
            if (creatureIsOnDefence && creatureIsFullAP)
            {
                LowHealth_CreatureOnDefenceAndFullAP(player);
            }
            else
                if(creatureIsOnDefence && !creatureIsFullAP)
                { 
                    LowHealth_CreatureOnDefenceAndPartialAP(player);
                }
            else
                    if (!creatureIsOnDefence && creatureIsFullAP)
                    {
                        LowHealth_CreatureNotOnDefenceAndFullAP(player);
                    }
                    
                    else
                        if(!creatureIsOnDefence && !creatureIsFullAP)
                    {
                            LowHealth_CreatureNotOnDefenceAndPartialAP(player);
                    }
        }
    }
}

void NormalEnemy::CreatureOnDefenceAndFullAP(Creature* player)
{
    if (debug)
    {
        std::cout << " la creatura " << creatureName << " e sulla difensiva e ha hp > 50% " << std::endl;
        std::cout << std::endl;
        std::cout << "AAP di " << creatureName << " creatura scelta completamente disponibili " << std::endl;
        std::cout << std::endl;
    }
    SetInDefenceMode(false);
    
    if (debug)
    {
        std::cout << creatureName << " lascia la difesa e attaca il gioccatore" << std::endl;
        std::cout << std::endl;
    }
    Attack(player);
}

    void NormalEnemy::CreatureOnDefenceAndPartialAP(Creature* player)
    {
            if (debug)
            {
                std::cout << "AAP di" << creatureName << " creatura scelta parzialmente disponibili " << std::endl;
                std::cout << std::endl;
            }

            int consumableType = ReturnConsumableType();
            switch (consumableType)
            {
            case(0): //nessun consumabile-> rimane in difesa, salta il turno                           
                ClearActionPoints();
                return;

            case(1): //pozione di cura-> resta in difesa, non ha bisgno di curarsi
                ClearActionPoints();
                return;


            case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico
                UseConsumable(player);
                return;
            }
    }

    void NormalEnemy::CreatureNotOnDefenceAndFullAP(Creature* player)
    {
        Attack(player);

        if (ReturnRandomBool()) //l'IA ha detto di attacare
        {
            if (debug)
            {
                std::cout << "l'IA ha scelto di ATTACARE di NUOVO " << std::endl;
                std::cout << std::endl;
            }

            Attack(player);
        }
        else//l'IA ha scelto di non attacare 
        {
            if (debug)
            {
                std::cout << "l'IA ha scelto di NON ATTACARE di NUOVO " << std::endl;
                std::cout << std::endl;
            }
        }
    }

    void NormalEnemy::CreatureNotOnDefenceAndPartialAP(Creature* player)
    {
        if (ReturnRandomBool())
        {
            if (debug)
            {
                std::cout << "l'IA ha scelto di ATTACARE di NUOVO " << std::endl;
                std::cout << std::endl;
            }

            Attack(player);
        }
        else
        {
            SetInDefenceMode(true);
            if (debug)
            {
                std::cout << "l'IA ha scelto di NON ATTACARE di NUOVO  e tenere la creatura sulla DIFESA" << std::endl;
                std::cout << std::endl;
            }
        }
    }

    void NormalEnemy::LowHealth_CreatureOnDefenceAndFullAP(Creature* player)
    {
        if (debug)
        {
            std::cout << "la creatura " << creatureName << " e sulla DIFENSIVA e ha HP < 50% " << std::endl;
            std::cout << std::endl;
        }
        //il GIOCATORE puo essere UCCISO con un ATTACO
        if (player->ReturnCurrentHealth() <= attack)
        {
            if (debug)
            {
                std::cout << "il giocatore puo essere ucciso con un attaco, lascia la difesa e attaca " << std::endl;
                std::cout << std::endl;
            }
            SetInDefenceMode(false);
            Attack(player);
        }
        //il GIOCATORE  NON puo essere UCCISO con un ATTACO
        else
        {
            int consumableType = ReturnConsumableType();
            
            switch (consumableType)
            {
            case(0): //nessun consumabile-> sceglie se attacare                            
                if (ReturnRandomBool())
                {
                    //lascia la difesa e attaca
                    SetInDefenceMode(false);
                    Attack(player);
                }
                else
                {
                    //resta in difesa, salta il turno
                    ClearActionPoints();
                }
                return;

            case(1): //pozione di cura-> resta in difesa, si cura, il nemico salta il turno
                UseConsumable(this);
                ClearActionPoints();
                return;


            case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico, salta il turno
                UseConsumable(player);
                ClearActionPoints();
                return;
            }
        }
    }

    void NormalEnemy::LowHealth_CreatureOnDefenceAndPartialAP(Creature* player)
    {
        if (debug)
        {
            std::cout << "AAP della creatura " << creatureName << " parzialmente disponibili " << std::endl;
            std::cout << std::endl;
        }
        int consumableType = ReturnConsumableType();
        switch (consumableType)
        {
        case(0): //nessun consumabile-> rimane in difesa, salta il turno                           
            ClearActionPoints();
            return;

        case(1): //pozione di cura-> resta in difesa, si cura
            UseConsumable(this);
            ClearActionPoints();
            return;


        case(2): //bomba incendiaria-> resta in difesa, lancia una bomba al nemico
            UseConsumable(player);
            return;
        }
    }

    void NormalEnemy::LowHealth_CreatureNotOnDefenceAndFullAP(Creature* player)
    {
        if (debug)
        {
            std::cout << "la creatura ATTACA e DIFENDE " << std::endl;
            std::cout << std::endl;
        }
        Attack(player);
        SetInDefenceMode(true);
    }

    void NormalEnemy::LowHealth_CreatureNotOnDefenceAndPartialAP(Creature* player)
    {
        //il GIOCATORE puo essere UCCISO con un ATTACO
        if (player->ReturnCurrentHealth() <= ReturnAttack())
        {
            if (debug)
            {
                std::cout << "il giocatore puo esser eucciso con un attaco, la creatura attaca " << std::endl;
                std::cout << std::endl;
            }
            Attack(player);
        }
        //il GIOCATORE  NON puo essere UCCISO con un ATTACO
        else
        {
            if (debug)
            {
                std::cout << "la creatura cerca di DIFENDERSI " << std::endl;
                std::cout << std::endl;
            }
            SetInDefenceMode(true);
        }
    }
