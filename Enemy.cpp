#include "Enemy.h"
#include <ctime>
using namespace std;

bool Enemy::CheckCreatureIsHighOnHealth(Creature* creature)
{
    if (creature->ReturnCurrentHealth() > (creature->ReturnMaxHealth() / 2))
        return true;

    return false;
}
//restituisce TRUE  se la creatura ha AAP al massimo
bool Enemy::CheckCreatureIsFullAP(Creature* creature)
{
    if (creature->ReturnAAP() >= creature->ReturnActionPointsPerTurn())
        return true;

    return false;
}

//restituisce casualmente TRUE o FALSE
bool Enemy::ReturnRandomBool()
{
    srand(time(NULL)); //imposto il seme di generazione casuale
    int num = rand();
    bool intention = (num % 2 == 0) ? true : false;

    if (debug)
        std::cout << "IA ha fatto la sua scelta :  " << intention << std::endl;
    return intention;
}
