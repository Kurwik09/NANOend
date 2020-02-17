#include "Command.h"

const std::regex Command::regexp(
	"^"				//pocz�tek linii
	"(?:#nano#)?"	//poniewa� podanie skr�tu mo�e zaczyna� si� od #nano#, ale nie musi, to mamy tu to zaznaczone
	"<([A-Z]{4})"	//wykrycie ctrl
	">([A-Z]{1})"	//wykrycie literki do skr�tu
	"%(.+)"			//opis po %
	"$"				//koniec linii
);

Command::Command(const std::string& command, std::function<void()> handler, const std::string description) : command(command), handler(handler), description(description) {

	std::smatch result;									//s�u�y do magazynowania wyra�e� spe�niaj�ych wyra�enie, smatch konkretnie do magazynowania string�w 				
	if (std::regex_match(command, result, regexp)) {
		shortcut = "<";									//shortuct = "<"					
		shortcut += result[1];							//sortcut = "<CTRL"
		letter = result[2];								//zapisanie litery do letter
		shortcut += "+";								//sortcut = "<CTRL+"
		shortcut += letter;								//sortcut = "<CTRL+letter"
		shortcut += ">";								//sortcut = "<CTRL+letter>"
		text = result[3];								//text = nazwa dzia�ania
			
	}
	else throw Error();
}

Command::~Command() {}