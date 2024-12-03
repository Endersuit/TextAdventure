#pragma once
class Creature;

class  Consumable //classe che verra ereditata da ogni oggetto consumabile
{
public:
	//funzione definita da chi ereddita la classe, = 0 per non essere
	//instanziata e indicargli che va definita nella classe erediatata
	virtual void UseConsumable(Creature* target) = 0;
	virtual ~Consumable() = default;
};