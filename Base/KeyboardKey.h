#pragma once

#include "Key.h"

class KeyboardKey final : public Key {

public:

	KeyboardKey(const int);
	std::string toString() const override;		//nadpisanie po Key funkcji toString, która bêdzie sprecyzowana w pliku cpp

};