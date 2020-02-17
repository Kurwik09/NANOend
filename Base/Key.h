#pragma once

#include <string>

class Key {

protected:

	const int code;									//zmienna typu const int, b�dzie potrzebna do okre�lenia wej�ciowej kombinacji klawiszy

public:

	Key(const int keycode) : code(keycode) {};		//konstruktor
	virtual ~Key() {};								//wirtualny dekonstruktor, informujemy na razie, �e b�dzie
	virtual std::string toString() const = 0;		//deklaracja wirtualnej funkcji toString, kt�ra b�dzie p�niej okre�lona
	int getCode() const { return code; };			//zwr�c warto�� kodu

};