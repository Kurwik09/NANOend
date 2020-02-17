#include "Command.h"

const std::regex Command::regexp(
	"^"				//pocz¹tek linii
	"(?:#nano#)?"	//poniewa¿ podanie skrótu mo¿e zaczynaæ siê od #nano#, ale nie musi, to mamy tu to zaznaczone
	"<([A-Z]{4})"	//wykrycie ctrl
	">([A-Z]{1})"	//wykrycie literki do skrótu
	"%(.+)"			//opis po %
	"$"				//koniec linii
);

Command::Command(const std::string& command, std::function<void()> handler, const std::string description) : command(command), handler(handler), description(description) {

	std::smatch result;									//s³u¿y do magazynowania wyra¿eñ spe³niaj¹ych wyra¿enie, smatch konkretnie do magazynowania stringów 				
	if (std::regex_match(command, result, regexp)) {
		shortcut = "<";									//shortuct = "<"					
		shortcut += result[1];							//sortcut = "<CTRL"
		letter = result[2];								//zapisanie litery do letter
		shortcut += "+";								//sortcut = "<CTRL+"
		shortcut += letter;								//sortcut = "<CTRL+letter"
		shortcut += ">";								//sortcut = "<CTRL+letter>"
		text = result[3];								//text = nazwa dzia³ania
			
	}
	else throw Error();
}

Command::~Command() {}