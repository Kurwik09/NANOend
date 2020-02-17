#include "ElementMenuItem.h"



ElementMenuItem::ElementMenuItem(const std::string& sc, const int x0, const std::string& nazwa, std::function<void()> handler) :
	MenuItem(std::string(TOP_ITEM_LEFT_MARGIN, ' ') + sc + std::string(TOP_ITEM_RIGHT_MARGIN, ' ')),
	x0(x0), x1(x0 + getWidth()), nazwa(nazwa), handler(handler)
{
	
}


ElementMenuItem::~ElementMenuItem()
{
	for (auto* item : items)
		delete item;
}


void ElementMenuItem::addItem(Element* const item)
{
	if (item->getWidth() + static_cast<int>(OPTION_ITEM_RIGHT_MARGIN) > submenuWidth)
		submenuWidth = item->getWidth() + OPTION_ITEM_RIGHT_MARGIN;
	++submenuHeight;
	items.push_back(item);
}


bool ElementMenuItem::matchLabel(const std::string& label) const
{
	auto thisIt = this->sc.begin() + TOP_ITEM_LEFT_MARGIN, otherIt = label.begin();
	while (otherIt != label.end() && thisIt != this->sc.end()) {
		if (*thisIt != *otherIt)
			return false;
		++thisIt;
		++otherIt;
	}
	return true;
}


const std::vector<Element*>& ElementMenuItem::getItems() const
{
	return items;
}