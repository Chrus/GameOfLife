#include "SideBar.h"
#include "ControlsExpander.h"

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

void SideBar::setContents()
{
	EditExpander* edit = new EditExpander(
		Rect(iRect.x(), iRect.y(), iRect.width(), iRect.height() / 2),
		Rect(iRect.right() + 1, iRect.y(), 100, 250),
		this,
		std::string("E\nd\ni\nt"),
		board);

	contents.push_back(edit);
}
