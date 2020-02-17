#include "ParamOptionMenuItem.h"



ParamOptionMenuItem::ParamOptionMenuItem(const Command& c) :
	OptionMenuItem(c),
	paramLabel(c.text)
{
}


ParamOptionMenuItem::~ParamOptionMenuItem()
{
}


std::string ParamOptionMenuItem::getParamLabel() const
{
	return paramLabel;
}


std::string ParamOptionMenuItem::getEntryName() const
{
	return entryName;
}