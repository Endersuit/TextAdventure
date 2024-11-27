#pragma once //non toccare questa riga
#include <string>
#include "Consumable.h"
#include <memory>  // includere per usare  std::unique_ptr
class Creature
{
public : 
	Creature(std::string creatureName,int maxHealth, float defence, int actionPointsPerTurn,float attack ,bool isOnDefensive);
	//funzioni
	void Attack(Creature &target);
	void SetInDefenceMode(bool activate);
	void GetDamage(float damage);
	void RestoreActionPoints();
	void UseConsumable();
	void EquipConsumable(Consumable* consumable);
	//funzione usa consumabile
private : 
	std::string creatureName;
	int maxHealth;
	float currentHealth;
	float defence;
	float attack;
	int actionPointsPerTurn;
	int actualActionPoints;
	bool isOnDefensive;
	std::unique_ptr<Consumable> equippedConsumable = nullptr; //smart pointer, 
	//permette la gestione automatica della memoria senza usare "new" o "delete"
	

};

