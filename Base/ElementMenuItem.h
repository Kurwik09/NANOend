#pragma once
#include "MenuItem.h"

#include "Element.h"

#include <vector>
#include <curses.h>


constexpr size_t
TOP_ITEM_LEFT_MARGIN = 1,
TOP_ITEM_RIGHT_MARGIN = 1,
OPTION_ITEM_RIGHT_MARGIN = 1;

class ElementMenuItem :
	public MenuItem
{
	std::vector<Element*> items;
	
	const int x0, x1;
	int submenuWidth, submenuHeight;

	

public:
	std::function<void()> handler;
	const std::string nazwa;
	ElementMenuItem(const std::string&, const int, const std::string&, std::function<void()>);
	~ElementMenuItem();
	std::string getSC() { return sc; };
	void addItem(Element* const);
	std::string getName() { return nazwa; };
	std::string getSCandName() { return sc + nazwa; };
	bool matchLabel(const std::string&) const;
	const std::vector<Element*>& getItems() const;

};