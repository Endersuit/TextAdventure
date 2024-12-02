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
	//gestione turni del combattimento
    void StartAndManageFight();

	//set
	void SetPlayer(Creature* player);
	void SetEnemies(std::vector<std::unique_ptr<Creature>>&& enemies);
		;
	void TargetAttack(Creature* attacker, Creature* target);
	void ChooseAnAction();

	void PrintCreatureInfo(Creature* creatureToPrint, int index);
	void PrintCreatureInfo();
	
	//Get
	Creature* ReturnSelectedEnemy(int index);
	Creature* ChooseAnEnemy();
	
	void AnalyzeAndDecide();
	bool CheckIfSelectionIsAvaible(Creature* selcetedCreature);
	bool CheckIfEnemiesAlive();
	bool ReturnRandomBool();
	
	int ReturnRandomnumber(int n);
	
	//funzione per iniziare il combattimento (WIP)

private :
	CombactManager() {}

	Creature* player = nullptr; //reference : passare una istanza gia esistente che non deve essere null
	std::vector<std::unique_ptr<Creature>> enemies; //i nemici sarano gia instaziti, percio passo i puntatori per evitare
	//di crearne delle coppie
	
	bool isPlayerTurn = true; //in ogni battaglia il giocatore sara il primo a iniziare. true -> turno dle giocatore. false -> turno degli avversari
	bool fightInProgress = true; //true -> il combattimento continuera all infinito finche non c'e un vincitore
};

