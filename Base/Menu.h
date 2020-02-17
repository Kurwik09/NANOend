#pragma once

#include "ElementMenuItem.h"
#include "Command.h"

#include <vector>


class Menu
{
	std::vector<ElementMenuItem*> items;
	const ElementMenuItem* selected;
	int width, minWidth, minHeight, submenuX;

	void addItem(ElementMenuItem* const);
	ElementMenuItem* addItem(const std::string&, std::string nazwa_sc, std::function<void()> handler);

	ElementMenuItem* getItemBySC(const std::string&) const;

public:
	Menu();
	~Menu();

	void addItem(const Command&);
	int getMinimumWidth() const;
	int getMinimumHeight() const;
	const std::vector<ElementMenuItem*>& getItems() const;
};
