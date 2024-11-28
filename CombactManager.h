#pragma once
#include <vector>
class Creature;
class CombactManager
{
public : 
	//definire construttore
	CombactManager(Creature* player, std::vector<Creature*> enemies);
	void TargetAttack(Creature* attacker, Creature* target);
	void ChooseAction();
	Creature* ReturnSelectedEnemy(int index);
	Creature* ChooseAnEnemy();
	bool CheckIfSelectionIsAvaible(Creature* selcetedCreature);
	bool ReturnRandomBool();
	int ReturnRandomnumber(int n);
	//funzione per iniziare il combattimento (WIP)
	//funzione per scegliere un nemico (si puo riutilizzare "ReturnSelectedEnemy" generando un numero casuale) (WIP)

private :
	Creature* player; //reference : passare una istanza gia esistente che non deve essere null
	std::vector<Creature*> enemies; //i nemici sarano gia instaziti, percio passo i puntatori per evitare
	//di crearne delle coppie
	
	bool isPlayerTurn = true; //in ogni battaglia il giocatore sara il primo a iniziare. true -> turno dle giocatore. false -> turno degli avversari
	bool fightInProgress = true; //true -> il combattimento continuera all infinito finche non c'e un vincitore
};

