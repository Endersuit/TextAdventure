#pragma once
class Creature; //ho solo bisogno di una reference, percio mi affido a una forward declaration
class  Consumable //classe che verra ereditata da ogni oggetto consumabile
{
public:
	virtual void UseConsumable(Creature* target) = 0; //funzione definita da chi ereddita la classe, = 0 per non essere
	//instanziata e indicargli che va definita nella classe erediatata
};