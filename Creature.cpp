#include "Creature.h"
#include <iostream>
#include <algorithm> //per accedere alla funzione "CLAMP"
using namespace std;

Creature::Creature(std::string creatureName,int maxHealth, float defence,  float attack ,bool isOnDefensive, std::unique_ptr<Consumable> consumable)
{
	this->creatureName = creatureName;
	this->maxHealth = maxHealth;
	this->currentHealth = maxHealth;  // La salute iniziale � uguale a quella massima
	this->defence = defence;
	this->attack = attack;
	this->isOnDefensive = isOnDefensive;
	AvaibleActionPoints = actionPointsPerTurn;
	consumableSlot = std::move(consumable);
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
	if (other.consumableSlot) // Se il consumabile esiste
	{
		// Esegui il dynamic_cast sul puntatore grezzo dell'oggetto contenuto in consumableSlot
		if (auto potionCure = dynamic_cast<HealingPotion*>(other.consumableSlot.get())) {
			// Se � una HealingPotion, crea una copia della HealingPotion
			consumableSlot = std::make_unique<HealingPotion>(*potionCure);
		}
		else if (auto bomb = dynamic_cast<IncendiaryBomb*>(other.consumableSlot.get())) {
			// Se � una IncendiaryBomb, crea una copia della IncendiaryBomb
			consumableSlot = std::make_unique<IncendiaryBomb>(*bomb);
		}
	}
	}
//////////////////////////////////////////Gestione statistiche/////////////////////////////////////////////

//ripristinare i punti azione
void Creature::RestoreActionPoints()
{
	AvaibleActionPoints = actionPointsPerTurn;
}

void Creature::ConsumeActionPoint()
{
	if (AvaibleActionPoints > 0)
	{
		AvaibleActionPoints--;
	}
}

//usare un consumabile
void Creature::UseConsumable(Creature* target)
{
	if (consumableSlot) //se il puntatore e valido (!= null)
	{
		consumableSlot->UseConsumable(target);
		consumableSlot = nullptr; //liberare l'inventario consumabile
		ConsumeActionPoint();
	}
	else
	{
		std::cout << "nessun consumabile equipagiato";
	}
}

//equipaggiare un consumabile
void Creature::EquipConsumable(Consumable* consumable)
{
	if (!consumableSlot)//slot libero
	{
		consumableSlot.reset(consumable); //sostituisce il vecchio puntattore con quello nuovo 
		//ed elimina quello vecchio se non ci sono piu riferimenti
	}
	else
	{
		cout << "non hai spazio per un altro consumabile" << endl;
	}
}

//attacare un altra creatura
void Creature::Attack(Creature* target)
{
	if (this != target)//confronto i puntatori per vedere se puntano alla stessa cosa
	{
		target->GetDamage(attack);
		ConsumeActionPoint();
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
			std::cout << "la creatura " << creatureName << " e morta " << std::endl;
			//richiamare qualcosa che faccia sparire la creatura dal campo di battaglia
		}
		else
		{
			currentHealth -= damageAmount;
			std::cout << "la creatura " << creatureName << " ha subito " << damageAmount << " danni" << std::endl;
			std::cout << "vita residua : " <<currentHealth <<std::endl;
		}
	}
	else //viene curato
	{
		currentHealth += (-1 * damage);
		//controllare che la salute non superi il massimo consentitto
		currentHealth = (currentHealth > maxHealth) ? currentHealth = maxHealth : currentHealth;
		std::cout << "la creatura " << creatureName << " e stata curata di  " << -damage << " danni" << std::endl;
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
	ConsumeActionPoint();
}

float Creature::ReturnAttack()
{
	return attack;
}

float Creature::ReturnCurrentHealth()
{
	return currentHealth;
}

float Creature::ReturnMaxHealth()
{
	return maxHealth;
}

int Creature::ReturnAAP()
{
	return AvaibleActionPoints;
}

int Creature::ReturnActionPointsPerTurn()
{
	return actionPointsPerTurn;
}

void Creature::ClearActionPoints()
{
	AvaibleActionPoints = 0;
}

bool Creature::ReturnIsOnDefence()
{
	return isOnDefensive;
}

std::string Creature::ReturnCreatureName()
{
	return creatureName;
}

int Creature::ReturnConsumableType()
{
	if (dynamic_cast<HealingPotion*>(consumableSlot.get()))
	{
		std::cout << "la creatura " << creatureName << " ha una pozione di cura" << std::endl;
		std::cout << std::endl;
		return 1;
	}
	else  
		if(dynamic_cast<IncendiaryBomb*>(consumableSlot.get())) 
		{
			std::cout << "la creatura " << creatureName << " ha una bomba" << std::endl;
			std::cout << std::endl;
			return 2;
		}
		else
		{
			std::cout << "la creatura " << creatureName << " non ha nessun consumabile" << std::endl;
			std::cout << std::endl;
			return 0;
		}
}

