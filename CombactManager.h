#pragma once
#include <vector>
#include <memory> 
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
	void SetEnemies(std::vector<std::unique_ptr<Creature>>&& enemies);
		;
	void TargetAttack(Creature* attacker, Creature* target);
	void ChooseAnAction();

	void PrintCreatureInfo(Creature* creatureToPrint, int index);
	void PrintCreaturesInfo();
	
	//Get
	Creature* ReturnSelectedEnemy(int index);
	Creature* ChooseAnEnemyOnConsole();
	
	void AnalyzeAndDecide();
	bool CheckIfSelectionIsAvaible(Creature* selcetedCreature);
	bool CheckIfEnemiesAlive();
	bool ReturnRandomBool();
	
	int ReturnRandomnumber(int n);
	
	//gestione turni e combattimento
	void StartAndManageFight();
	int CheckAndUseConsumable(Creature* creature); //controlla se un nemico ha un consumabile e se usarlo. a seconda dle consumabile, il nemico fa qualcosa
	bool CheckForPossibleWinner();
	bool CheckCreatureIsHighOnHealth(Creature* creature);
	bool CheckCreatureIsFullAP(Creature* creature);
	void SwapEnemiesArray();


private :
	CombactManager() {}

	Creature* player = nullptr; //reference : passare una istanza gia esistente che non deve essere null
	std::vector<std::unique_ptr<Creature>> enemies; //i nemici sarano gia instaziti, percio passo i puntatori per evitare
	//di crearne delle coppie
	
	bool isPlayerTurn = true; //in ogni battaglia il giocatore sara il primo a iniziare. true -> turno dle giocatore. false -> turno degli avversari
	bool fightInProgress = true; //true -> il combattimento continuera all infinito finche non c'e un vincitore
};

