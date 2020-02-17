#include "Menu.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}


void Menu::addItem(ElementMenuItem* const item)
{
	items.push_back(item);
}


ElementMenuItem* Menu::addItem(const std::string& label, std::string nazwa_sc, std::function<void()> handler)
{
	ElementMenuItem* item = new ElementMenuItem(label, width, nazwa_sc, handler);
	items.push_back(item);
	width += item->getWidth();
	return item;
}


ElementMenuItem* Menu::getItemBySC(const std::string& sc) const
{
	for (auto* item : items)
		if (item->matchLabel(sc))
			return item;
	return nullptr;
}


void Menu::addItem(const Command& c)
{
	ElementMenuItem* Item;
	if ((Item = getItemBySC(c.shortcut)) == nullptr)
		Item = addItem(c.shortcut, c.text, c.handler);
	
}


int Menu::getMinimumWidth() const
{
	return minWidth;
}


int Menu::getMinimumHeight() const
{
	return minHeight;
}


const std::vector<ElementMenuItem*>& Menu::getItems() const
{
	return items;
}

