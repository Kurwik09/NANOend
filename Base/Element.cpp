#include "Element.h"



Element::Element(const Command& c) : MenuItem(c.shortcut), description(c.description), handler(c.handler) {}


Element::~Element() {}


std::string Element::getDescription() const { return description; }		//zwróæ opis funkcji


void Element::runHandler() const { handler(); }							//wywo³anie funkcji przechowywanej w obiekcie