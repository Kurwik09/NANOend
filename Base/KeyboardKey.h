#pragma once

#include "Key.h"

class KeyboardKey final : public Key {

public:

	KeyboardKey(const int);
	std::string toString() const override;		//nadpisanie po Key funkcji toString, kt�ra b�dzie sprecyzowana w pliku cpp

};