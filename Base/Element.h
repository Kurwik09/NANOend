#pragma once
#include "MenuItem.h"
#include "Command.h"

#include <functional>


class Element : public MenuItem
{
	const std::string description;			//zmienna zawieraj�ca opis funkcji
	const std::function<void()> handler;	//zmienna z funkcj�

public:
	Element(const Command&);				//kontruktor, kt�ry jako zmienna przyjmuje obiekt typu Command
	~Element();

	std::string getDescription() const;		//funkcja zwracaj�ca opis, sprecyzowana w pliku cpp
	void runHandler() const;				//funkcja uruchamiaj�c� funkcje, sprecyzowana w pliku cpp
};

