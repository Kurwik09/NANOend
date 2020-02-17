#pragma once

#include <string>

class Key {

protected:

	const int code;									//zmienna typu const int, bêdzie potrzebna do okreœlenia wejœciowej kombinacji klawiszy

public:

	Key(const int keycode) : code(keycode) {};		//konstruktor
	virtual ~Key() {};								//wirtualny dekonstruktor, informujemy na razie, ¿e bêdzie
	virtual std::string toString() const = 0;		//deklaracja wirtualnej funkcji toString, która bêdzie póŸniej okreœlona
	int getCode() const { return code; };			//zwróc wartoœæ kodu

};