#include "TestTool.h"



TestTool::TestTool()
{
}


TestTool::~TestTool()
{
}


std::string TestTool::getEntry(const std::string& key) const
{
	try {
		return entries.at(key);
	}
	catch (std::string out_of_range) {
		throw BaseTool::UndefinedEntry();
	}
}


void TestTool::setEntry(const std::string& key, const std::string& value)
{
	entries[key] = value;
}


void TestTool::assignWindow(WINDOW* windowptr)
{
	window = windowptr;
}


void TestTool::edition()
{
	if (getEntry("KEY").size() == 1)
		waddch(window, getEntry("KEY")[0]);
	wrefresh(window);
}