#pragma once
#include <vector>
#include <memory> 
#include "Enemy.h"
class Creature;
class CombactManager
{
public : 
	//la parola "delete" evita che venga creata una copia dell' istanza o di utilizare un operatore
	CombactManager(const CombactManager&) = delete;

	static CombactManager& Get() {
		static CombactManager instance;  // L'istanza statica
		return instance;
	}

	//set
	void SetPlayer(Creature* player);
	void SetEnemies(std::vector<std::unique_ptr<Enemy>>&& enemies);
		;
	void TargetAttack(Creature* attacker, Creature* target);
	void ChooseAnAction();

	void PrintCreatureInfo(Creature* creatureToPrint, int index = 0);
	void PrintCreaturesInfo();
	
	//Get
	Creature* ReturnSelectedEnemy(int index);
	Creature* ChooseAnEnemyOnConsole();
	
	void EnemyTurn();
	bool CheckIfSelectionIsAvaible(Creature* selcetedCreature);
	bool CheckIfEnemiesAlive();
	
	int ReturnRandomnumber(int n);
	
	//gestione turni e combattimento
	void StartAndManageFight();
	void CheckAndUseConsumableForPlayer(Creature* creature); //controlla se un nemico ha un consumabile e se usarlo. a seconda dle consumabile, il nemico fa qualcosa
	bool CheckForPossibleWinner();
	void SwapEnemiesArray();


private :
	CombactManager() {}

	Creature* player = nullptr; //reference : passare una istanza gia esistente che non deve essere null
	std::vector<std::unique_ptr<Enemy>> enemies; //i nemici sarano gia instaziti, percio passo i puntatori per evitare
	//di crearne delle coppie
	
	bool isPlayerTurn = true; //in ogni battaglia il giocatore sara il primo a iniziare. true -> turno dle giocatore. false -> turno degli avversari
	bool fightInProgress = true; //true -> il combattimento continuera all infinito finche non c'e un vincitore
	bool debug = true;
};

