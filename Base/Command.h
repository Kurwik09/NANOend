#pragma once

#include <string>
#include <functional>
#include <regex>


struct Command {

	class Error {};															//w razie b��du
				
	const std::string command, description;									//zmienne const string, kt�re przechowuj� kombinacje klawiszy i opis
	std::function<void()> handler;											//zmienna przechowuj�ca funkcje dla konkretnej kombinacji klawiszy
	std::string shortcut, letter, text;										//zmienne u�ywane do zapisywania wyniku wyra�enia regularnego

	Command(const std::string&, std::function<void()>, const std::string);	//konstruktor
	~Command();																//dekonstruktor

	static const std::regex regexp;											//zmienna dla wyra�enia regularnego 

};