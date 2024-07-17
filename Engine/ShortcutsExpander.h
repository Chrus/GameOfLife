#pragma once
#include "ExpandablePanel.h"
class ShortcutsExpander : public ExpandablePanel
{
public:
	ShortcutsExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	void setShortcutsText(std::vector<std::string> shortcuts);
};

