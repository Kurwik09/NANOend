#pragma once
#include "MenuItem.h"
#include "Command.h"

#include <functional>


class Element : public MenuItem
{
	const std::string description;			//zmienna zawieraj¹ca opis funkcji
	const std::function<void()> handler;	//zmienna z funkcj¹

public:
	Element(const Command&);				//kontruktor, który jako zmienna przyjmuje obiekt typu Command
	~Element();

	std::string getDescription() const;		//funkcja zwracaj¹ca opis, sprecyzowana w pliku cpp
	void runHandler() const;				//funkcja uruchamiaj¹c¹ funkcje, sprecyzowana w pliku cpp
};

