#include "NANOBackend.h"
#include "Command.h"

#include <thread>
#include <chrono>




//zainicjowanie okna, menu oraz bindowanie dwóch podstawowych skrótów

NANOBackend::NANOBackend(BaseTool* const tool) :
	BaseBackend(tool),
	isOpen(true)
{
	initscr();
	editionHandler = nullptr;
	menu = new Menu();
	currentFunction = &NANOBackend::main;

	bind("<CTRL>Q%Quit", std::bind(&NANOBackend::quit, this), "Close nano");
	bind("<CTRL>H%Help", std::bind(&NANOBackend::help, this), "Show Help");

	
}

//dekonsturktor
NANOBackend::~NANOBackend()
{
	eraseTerm();
	endwin();
	delete menu;
}

//próbuje zbindowaæ, je¿eli wyst¹pi b³¹d, sprawdza, czy nie ma trybu edycji
void NANOBackend::bind(const std::string& command, std::function<void()> handler, const std::string& description)
{
	try
	{
		Command parsed(command, handler, description);
		menu->addItem(parsed);
	}
	catch (Command::Error&) {
		if (command == "<EDITION>" || command == "#nano#<EDITION>") {
			editionHandler = handler;
			editionDescription = description;
		}
	}
}

//
void NANOBackend::start()
{
	drawTerm();
	renderMenu();

	while (isOpen)
		(this->*currentFunction)();
}

//pobieranie przycisku/ów z klawiatury
Key* NANOBackend::getKey() const
{
	int keycode = getch();
	if (keycode == KEY_RESIZE)
		return new ResizeKey(COLS, LINES - 1);
	else
		return new KeyboardKey(keycode);
}

//generowanie ekranów toola i menu
void NANOBackend::drawTerm()
{
	noecho();
	cbreak();
	raw();
	keypad(stdscr, TRUE);
	curs_set(0);

	drawMenuWindow();
	drawToolWindow();

	refresh();
}

//generowanie okna menu
void NANOBackend::drawMenuWindow()
{
	menuWindow = newwin(1, COLS, LINES-1, 0);
}

//generowanie okna dla toola
void NANOBackend::drawToolWindow()
{
	toolWindow = newwin(1, COLS, 0, 0);
	tool->assignWindow(toolWindow);
}

//nadokno wykorzystywane do w³¹czania okna HELP
void NANOBackend::drawOverlayWindow(const int width, const int height, const int dx, const int dy)
{
	overlayWindow = newwin(height, width, dy, dx);
}

//zwalnianie okna i wczytywanie okien toola i menu
void NANOBackend::hideOverlayWindow()
{
	eraseWindow(overlayWindow);
	touchwin(menuWindow);
	wnoutrefresh(menuWindow);
	touchwin(toolWindow);
	wnoutrefresh(toolWindow);
	doupdate();
}

//zwalnia okno oraz pusty wskaŸnik
void NANOBackend::eraseWindow(WINDOW*& window)
{
	if (window) {
		wclear(window);
		wrefresh(window);
		delwin(window);
		window = nullptr;
	}
}

//zwalnianie okien menu i toola
void NANOBackend::eraseTerm()
{
	eraseWindow(menuWindow);
	eraseWindow(toolWindow);
	eraseWindow(overlayWindow);
	clear();
	refresh();
}

//wykorzystywane do zapewnienia poprawnego wyœwietlania menu
void NANOBackend::handleResizeKey(const ResizeKey* const key)
{
	std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(500));
	eraseTerm();
	resize_term(0, 0);
	drawTerm();

	if (isTooSmall()) {
		currentFunction = &NANOBackend::tooSmall;
	}
	else {
		renderMenu();
		currentFunction = &NANOBackend::main;
	}

	tool->setEntry("KEY", key->toString());
	callEditionHandler();
}

//wczytywanie przycisku, iterujemy po kolekcji obiektów i sprawdzamy, czy któryœ obiekt posiada wskazany skrót (jest to jedna ze zmiennych obiektu), je¿eli tak, to wywo³ujemy funkcje jej przypisan¹
void NANOBackend::handleKeyboardKey(const KeyboardKey* const key)
{
	for (auto& item : menu->getItems()) {
		

		if (item->getSC() == ' ' + key->toString() + ' ') {   
			item->handler();
		
		}
	
	}
	tool->setEntry("KEY", key->toString());  
	callEditionHandler();
}

void NANOBackend::callEditionHandler() const
{
	if (editionHandler)
		editionHandler();
}

//sprawdza czy wielkoœæ mieœcie siê miêdzy podwójn¹ wartoœci¹ ALERT_MARGIN, zwraca TRUE albo FALSE w zale¿noœci od wielkoœci
bool NANOBackend::isTooSmall() const
{
	return COLS < menu->getMinimumWidth() || LINES < menu->getMinimumHeight() || COLS < 2 * ALERT_MARGIN + static_cast<int>(unsavedAlert.size()) || LINES < 2 * ALERT_MARGIN + 1;
}

//do okna menu dodaje wszystkie skróty zgromadzone w obiektach
void NANOBackend::renderMenu()
{

	for (int i = 0; i < COLS; ++i)
		waddch(menuWindow, ' ');
	wmove(menuWindow, 0, 0);
	for (auto& item : menu->getItems())
		waddstr(menuWindow, item->getSCandName().c_str());
		
	wrefresh(menuWindow);
}

//wyœwietlanie alertu o nie zapisaniu projektu
void NANOBackend::showAlert(const std::string& alert)
{
	int width = alert.size() + 2 * ALERT_MARGIN,
		height = 2 * ALERT_MARGIN + 1;
	hideOverlayWindow();
	drawOverlayWindow(width, height, (COLS - width) / 2, (LINES - height) / 2);

	for (int i = 0; i < height * width; ++i) waddch(overlayWindow, ' ');
	mvwprintw(overlayWindow, height / 2, (width - alert.size()) / 2, alert.c_str());

	wrefresh(overlayWindow);

	Key* key = getKey();
	hideOverlayWindow();

	ResizeKey* rkey = dynamic_cast<ResizeKey*>(key);
	if (rkey) handleResizeKey(rkey);

	delete key;
}

//g³ówna funkcja, której zadaniem jest pobieranie wprowadzanych danych (sprawdza czy pobrano przycisk, czy informacje o zmianie okna)
void NANOBackend::main()
{
	Key* key = getKey();

	if (ResizeKey* rkey = dynamic_cast<ResizeKey*>(key))
		handleResizeKey(rkey);
	else if (KeyboardKey* kkey = dynamic_cast<KeyboardKey*>(key))
		handleKeyboardKey(kkey);

	delete key;
}


void NANOBackend::tooSmall()
{
	Key* key;
	ResizeKey* rkey;

	while ((rkey = dynamic_cast<ResizeKey*>(key = getKey())) == nullptr)
		delete key;

	handleResizeKey(rkey);

	delete key;
}

//pobieranie przycisków innych ni¿ wczeœniejsze skróty klawiszowe, tz. : litery, cyfry, i znaki interpunkcyjne
void NANOBackend::popup()
{

	Key* key = getKey();

	if (KeyboardKey* kkey = dynamic_cast<KeyboardKey*>(key)) {
		std::string keyString = kkey->toString();

		
			if (keyString == "<BS>") {
				paramBuffer = paramBuffer.substr(0, paramBuffer.size() - 1);
			}
			else if (kkey->getCode() > 31 && kkey->getCode() < 127) {
				paramBuffer += static_cast<char>(kkey->getCode());
			}

			std::string toPrint;
			if (paramBuffer.size() < PARAM_INPUT_WIDTH) {
				toPrint = paramBuffer + std::string(PARAM_INPUT_WIDTH - paramBuffer.size(), ' ');
			}
			else if (paramBuffer.size() > PARAM_INPUT_WIDTH) {
				toPrint = paramBuffer.substr(paramBuffer.size() - PARAM_INPUT_WIDTH, PARAM_INPUT_WIDTH);
			}
			else {
				toPrint = paramBuffer;
			}
			mvwprintw(overlayWindow, paramHeaderHeight, 0, "%s", toPrint);
			wrefresh(overlayWindow);
		
	}
	else if (ResizeKey* rkey = dynamic_cast<ResizeKey*>(key)) {
		handleResizeKey(rkey);
	}
	delete key;
}

void NANOBackend::help()
{
	std::vector<std::string> lines;
	WINDOW* tmpWindow = newwin(LINES, COLS, 0, 0);

	lines.push_back("MENU HELP");
	lines.push_back("b - back");
	lines.push_back("<UARROW> - go up");
	lines.push_back("<DARROW> - go down");
	lines.push_back("");
	for (auto& item : menu->getItems()) {
		lines.push_back(item->getSCandName().substr(TOP_ITEM_LEFT_MARGIN));
	}

	size_t firstLine = 0;
	refresh();
	renderHelp(tmpWindow, lines, firstLine);

	Key* key;
	std::string keyString;

	while ((keyString = (key = getKey())->toString()) != "b") {
		if (keyString == "<RESIZE>") {
			delwin(tmpWindow);
			handleResizeKey(dynamic_cast<ResizeKey*>(key));
			tmpWindow = newwin(LINES, COLS, 0, 0);
			renderHelp(tmpWindow, lines, firstLine);
		}
		else if (keyString == "<UARROW>") {
			if (firstLine > 0) {
				--firstLine;
				renderHelp(tmpWindow, lines, firstLine);
			}
		}
		else if (keyString == "<DARROW>") {
			if (firstLine + 1 < lines.size()) {
				++firstLine;
				renderHelp(tmpWindow, lines, firstLine);
			}
		}
	}

	wclear(tmpWindow);
	wrefresh(tmpWindow);
	delwin(tmpWindow);
	hideOverlayWindow();

	delete key;
}


void NANOBackend::renderHelp(WINDOW* const helpWindow, const std::vector<std::string>& lines, const size_t firstLine)
{
	wclear(helpWindow);
	wmove(helpWindow, 0, 0);
	int lineNum = 0, tmp;
	std::string line;
	for (auto it = lines.begin() + firstLine; it != lines.end() && lineNum < LINES - 1; ++it) {
		tmp = 1;
		while (tmp * COLS < static_cast<int>(it->size())) ++tmp;
		if (lineNum + tmp > COLS) line = it->substr(0, tmp * COLS);
		else line = *it;
		waddstr(helpWindow, (line + "\n").c_str());
	}
	wrefresh(helpWindow);
}


void NANOBackend::quit()
{
	try {
		if (tool->getEntry("IS_SAVED") == "NO")
			showAlert(NANOBackend::unsavedAlert);
		else isOpen = false;
	}
	catch (BaseTool::UndefinedEntry&) {
		isOpen = false;
	}
}

const std::string NANOBackend::unsavedAlert = "Project can't be closed! Save before quit!";