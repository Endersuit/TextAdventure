#pragma once //non toccare questa riga
#include <string>
#include "Consumable.h"
#include <memory>  // includere per usare  std::unique_ptr
class Creature
{
public : 
	Creature(std::string creatureName,int maxHealth, float defence,float attack ,bool isOnDefensive);
	//funzioni
	void Attack(Creature &target);
	void SetInDefenceMode(bool activate);
	void GetDamage(float damage);
	void RestoreActionPoints();
	void UseConsumable();
	void EquipConsumable(Consumable* consumable);

	bool ReturnIsOnDefence();
	std::string ReturnCreatureName();
	float ReturnAttack();
	float ReturnCurrentHealth();
	int ReturnAAP(); //restituisce i "avaible actionPoints"

private : 
	std::string creatureName;
	int maxHealth;
	float currentHealth;
	float defence;
	float attack;
	int actionPointsPerTurn = 2;
	int AvaibleActionPoints;
	bool isOnDefensive;
	std::unique_ptr<Consumable> equippedConsumable = nullptr; //smart pointer, 
	//permette la gestione automatica della memoria senza usare "new" o "delete"
	

};

