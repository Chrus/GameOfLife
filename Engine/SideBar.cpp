#include "SideBar.h"
#include "EditExpander.h"
#include "ShortcutsExpander.h"

SideBar::SideBar(Rect rect, Container* parent, Board& board)
	:
	Container(rect, parent),
	board(board)
{
	setContents();

	drawBackground = true;
	drawBorder = true;
}

DebugInfo SideBar::getDebugInfo() const
{
	return DebugInfo("Sidebar", "");
}

void SideBar::setShortcutsText(std::vector<std::string> shortcuts)
{
	dynamic_cast<ShortcutsExpander*>(contents[1])->setShortcutsText(shortcuts);
}

void SideBar::setContents()
{
	int expanderHeight = iRect.height() / 3;

	EditExpander* edit = new EditExpander(
		Rect(iRect.x(), iRect.y(), iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, iRect.y(), 100, 250),
		this,
		std::string("E\nd\ni\nt"),
		board);

	ShortcutsExpander* shortcuts = new ShortcutsExpander(
		Rect(iRect.x(), expanderHeight, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, expanderHeight, 150, 200),
		this,
		std::string("S\nh\no\nr\nt\nc\nu\nt\ns"));

	contents.push_back(edit);
	contents.push_back(shortcuts);
}
