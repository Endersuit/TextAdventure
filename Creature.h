#pragma once //non toccare questa riga
#include <string>
#include "Consumable.h"
#include <memory>  // includere per usare  std::unique_ptr
class Creature
{
public : 
	//construttore
	Creature(std::string creatureName,int maxHealth, float defence,float attack ,bool isOnDefensive);
	//construttore di spostamento
	Creature(const Creature& other);
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
	int actionPointsPerTurn = 2;
	int AvaibleActionPoints;
	float currentHealth;
	float defence;
	float attack;
	bool isOnDefensive;
	std::unique_ptr<Consumable> equippedConsumable = nullptr; //smart pointer, 
	//permette la gestione automatica della memoria senza usare "new" o "delete"
	

};

