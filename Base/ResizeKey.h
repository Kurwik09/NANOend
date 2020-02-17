#pragma once
#include "Key.h"
class ResizeKey final :
	public Key
{
	const int width, height;					//zmienne const int, które bêd¹ informowaly o nowym rozmiarze okna

public:
	ResizeKey(const int, const int);

	std::string toString() const override;		//nadpisanie po Key, sprecyzowane w cpp
	int getWidth() const { return width; };		//zwraca szerokoœæ okna
	int getHeight() const { return height; };	//zwraca wysokoœæ okna
};
