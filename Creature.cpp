#include "Creature.h"
#include <iostream>
#include <algorithm> //per accedere alla funzione "CLAMP"
using namespace std;

Creature::Creature(std::string creatureName,int maxHealth, float defence,  float attack ,bool isOnDefensive)
{
	this->creatureName = creatureName;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;  // La salute iniziale è uguale a quella massima
	this->defence = defence;
	this->attack = attack;
	this->isOnDefensive = isOnDefensive;
	AvaibleActionPoints = actionPointsPerTurn;
}

//construttore di coppia
Creature::Creature(const Creature& other)
	: creatureName(other.creatureName),
	maxHealth(other.maxHealth),
	AvaibleActionPoints(other.AvaibleActionPoints),
	actionPointsPerTurn(other.actionPointsPerTurn),
	currentHealth(other.currentHealth),
	defence(other.defence),
	attack(other.attack),
	isOnDefensive(other.isOnDefensive)
{
	//niente
}
//////////////////////////////////////////Gestione statistiche/////////////////////////////////////////////

//ripristinare i punti azione
void Creature::RestoreActionPoints()
{
	AvaibleActionPoints = actionPointsPerTurn;
}

//usare un consumabile
void Creature::UseConsumable()
{
	if (equippedConsumable) //se il puntatore e valido (!= null)
	{
		equippedConsumable->UseConsumable(this);
		equippedConsumable = nullptr; //liberare l'inventario consumabile
	}
	else
	{
		std::cout << "nessun consumabile equipagiato";
	}
}

//equipaggiar eun consumabile
void Creature::EquipConsumable(Consumable* consumable)
{
	if (!equippedConsumable)//slot libero
	{
		equippedConsumable.reset(consumable); //sostituisce il vecchio puntattore con quello nuovo 
		//ed elimina quello vecchio se non ci sono piu riferimenti
	}
	else
	{
		cout << "non hai spazio per un altro consumabile" << endl;
	}
}

//attacare un altra creatura
void Creature::Attack(Creature& target)
{
	if (this != &target)//confronto i puntatori per vedere se puntano alla stessa cosa
	{
		target.GetDamage(attack);
	}
	else
	{
		cout << "la creatura non puo dannegiare se stessa" << endl;
	}
}

//far subire danni alla creatura
void Creature::GetDamage(float damage)
{
	
	if (damage >= 0) //subisce danno
	{
		//ridure i danni in arrivo se la difesa e attiva
		float damageAmount = (isOnDefensive) ? damage - (defence / 2) : damage;
		if (damageAmount >= currentHealth)
		{
			currentHealth = 0;
			std::cout << "la creatura " << creatureName << "e morta " << std::endl;
			//richiamare qualcosa che faccia sparire la creatura dal campo di battaglia
		}
		else
		{
			currentHealth -= damageAmount;
			std::cout << "la creatura " << creatureName << "ha subito " << damageAmount << " danni" << std::endl;
			std::cout << "vita residua : " <<currentHealth <<std::endl;
		}
	}
	else //viene curato
	{
		currentHealth += (-1 * damage);
		//controllare che la salute non superi il massimo consentitto
		currentHealth = (currentHealth > maxHealth) ? currentHealth = maxHealth : currentHealth;
		std::cout << "la creatura " << creatureName << "e stat curata di  " << -damage << " danni" << std::endl;
		std::cout << "vita attuale : " << currentHealth << std::endl;
	}

}
////////////////////////////////////////////Get E Set/////////////////////////////////////////////////

//entrare/uscire in difesa
void Creature::SetInDefenceMode(bool activate)
{
	if (isOnDefensive == activate)
	{
		string message = isOnDefensive ?  " alzata " : " abbasata ";
		std::cout << "la tua difesa e gia  "<< message << std::endl;
	}
	isOnDefensive = activate;
	std::cout << "la difesa della creatura " << creatureName << " e " << (isOnDefensive ? "alzata" : "abbasatta") << endl;
}

float Creature::ReturnAttack()
{
	return attack;
}

float Creature::ReturnCurrentHealth()
{
	return currentHealth;
}

int Creature::ReturnAAP()
{
	return AvaibleActionPoints;
}

bool Creature::ReturnIsOnDefence()
{
	return isOnDefensive;
}

std::string Creature::ReturnCreatureName()
{
	return creatureName;
}

