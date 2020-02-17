#include "KeyboardKey.h"

KeyboardKey::KeyboardKey(const int keycode) : Key(keycode) {}

std::string KeyboardKey::toString() const {			//toString sprawdza kod przechowywany w obiekcie i na jego podstawie ustala, jaka kobinacja klawiszy zosta³a podana

	switch (code) {

	case 27:										//np.: je¿eli KeyboardKey = 27; to toString zwróci <ESC>, informuj¹c nas na podstawie kodu, ¿e ESC zosta³o wciœniête
		return "<ESC>";								//dla pozosta³ych podobna zasada
	case 330:
		return "<DEL>";
	case 258:
		return "<DARROW>";
	case 259:
		return "<UARROW>";
	case 260:
		return "<LARROW>";
	case 261:
		return "<RARROW>";
	case 1:
		return "<CTRL+A>";
	case 2:
		return "<CTRL+B>";
	case 3:
		return "<CTRL+C>";
	case 4:
		return "<CTRL+D>";
	case 5:
		return "<CTRL+E>";
	case 6:
		return "<CTRL+F>";
	case 7:
		return "<CTRL+G>";
	case 8:
		return "<CTRL+H>";
	case 9:
		return "<CTRL+I>";
	case 10:
		return "<CTRL+J>";
	case 11:
		return "<CTRL+K>";
	case 12:
		return "<CTRL+L>";
	case 13:
		return "<CTRL+M>";
	case 14:
		return "<CTRL+N>";
	case 15:
		return "<CTRL+O>";
	case 16:
		return "<CTRL+P>";
	case 17:
		return "<CTRL+Q>";
	case 18:
		return "<CTRL+R>";
	case 19:
		return "<CTRL+S>";
	case 20:
		return "<CTRL+T>";
	case 21:
		return "<CTRL+U>";
	case 22:
		return "<CTRL+V>";
	case 23:
		return "<CTRL+W>";
	case 24:
		return "<CTRL+X>";
	case 25:
		return "<CTRL+Y>";
	case 26:
		return "<CTRL+Z>";
	default:
		if (code > 0 && code < 27)
			return "<CTRL+" + static_cast<char>('A' - 1 + code);
		return std::string(1, code);
	}
}