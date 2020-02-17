#pragma once
#include "BaseTool.h"

#include <unordered_map>


class TestTool :
	public BaseTool
{
	std::unordered_map<std::string, std::string> entries;
	WINDOW* window;

public:
	TestTool();
	~TestTool() override;

	std::string getEntry(const std::string&) const override;
	void setEntry(const std::string&, const std::string&) override;
	virtual void assignWindow(WINDOW*) override;

	void edition();
};