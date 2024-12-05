#pragma once //non toccare questa riga
#include <string>
#include "Consumable.h"
#include "HealingPotion.h"
#include "IncendiaryBomb.h"
#include <memory>  // includere per usare  std::unique_ptr
class Creature
{
public : 
	//construttore
	Creature(std::string creatureName,int maxHealth, float defence,float attack ,bool isOnDefensive, std::unique_ptr<Consumable> consumable);
	
	//construttore di spostamento
	Creature(const Creature& other);
	
	void Attack(Creature* target);
	void SetInDefenceMode(bool activate);
	void SetNewConsumable(int consumableType);
	
	void GetDamage(float damage);
	
	void RestoreActionPoints();
	void RestoreHealthPoints();
	void ConsumeActionPoint();
	void ClearActionPoints(); //pensato per saltare il turno

	void UseConsumable(Creature* target);
	void EquipConsumable(Consumable* consumable);


	bool ReturnIsOnDefence();
	int ReturnDefenceValue();
	std::string ReturnCreatureName();
	float ReturnAttack();
	float ReturnCurrentHealth();
	float ReturnMaxHealth();
	int ReturnAAP(); //restituisce i "avaible actionPoints"
	int ReturnActionPointsPerTurn();
	int ReturnConsumableType();

private : 

	std::string creatureName;
	int maxHealth;
	int actionPointsPerTurn = 2;
	int AvaibleActionPoints = 2;
	float currentHealth;
	float defence;
	float attack;
	bool isOnDefensive;
	std::unique_ptr<Consumable> consumableSlot = nullptr; //smart pointer, 
	//permette la gestione automatica della memoria senza usare "new" o "delete"
	

};

