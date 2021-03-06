#pragma once
#include "MenuItem.h"
#include "Command.h"

#include <functional>


class Element : public MenuItem
{
	const std::string description;			//zmienna zawierająca opis funkcji
	const std::function<void()> handler;	//zmienna z funkcją

public:
	Element(const Command&);				//kontruktor, który jako zmienna przyjmuje obiekt typu Command
	~Element();

	std::string getDescription() const;		//funkcja zwracająca opis, sprecyzowana w pliku cpp
	void runHandler() const;				//funkcja uruchamiającą funkcje, sprecyzowana w pliku cpp
};

