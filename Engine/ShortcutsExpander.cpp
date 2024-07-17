#include "ShortcutsExpander.h"

ShortcutsExpander::ShortcutsExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text)
{}

DebugInfo ShortcutsExpander::getDebugInfo() const
{
	return DebugInfo("ShortcutsExpander", "");
}

void ShortcutsExpander::setShortcutsText(std::vector<std::string> shortcuts)
{
	std::string text;
	for (int x = 0; x < shortcuts.size(); x++)
	{
		text.append(shortcuts[x]);
		if (x + 1 != shortcuts.size())
			text.push_back('\n');
	}

	TextPanel* p = new TextPanel(TextPanel::TEXT_SPRITE8X14, visualRect, text);
	contents.push_back(p);
}