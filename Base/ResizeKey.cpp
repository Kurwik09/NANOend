#include "ResizeKey.h"



ResizeKey::ResizeKey(const int newwidth, const int newheight) :
	Key(0),
	width(newwidth), height(newheight)
{
}


std::string ResizeKey::toString() const				//toString nadpisane zwraca <RESIZE>, informacje o tym, ¿e nast¹pi³a zmiana wielkoœci okna
{
	return "<RESIZE>";						
}