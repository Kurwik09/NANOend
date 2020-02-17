#pragma once

#include <string>

class MenuItem {

protected:
	const std::string sc;							//zmienna sc, po niej wyszukuje skrótów

public:
	MenuItem(const std::string& sc) : sc(sc) {};
	virtual ~MenuItem() {};

	std::string getSC() const { return sc; }
	int getWidth() const { return sc.size(); }
	
};