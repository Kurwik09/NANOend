#include "TestTool.h"
#include "NANOBackend.h"


int main()
{
	TestTool* tool = new TestTool;
	NANOBackend* backend = new NANOBackend(tool);
	backend->bind("#nano#<CTRL>S%FunkcjaS", []() {mvprintw(15, 15, "FUNKCJA S"); }, "opis");
	backend->bind("<CTRL>D%FunkcjaD", []() {mvprintw(5, 5, "FUNKCJA D"); }, "opis");
	backend->bind("<CTRL>E%FunkcjaE", [&tool]() {mvprintw(1, 0, "%d", 20); }, "opis");
	tool->setEntry("IS_SAVED", "NO");
	backend->start();

	delete backend, tool;
}