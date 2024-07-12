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
	ControlsExpander* controls = new ControlsExpander(
		Rect(iRect.x(), iRect.y(), iRect.width(), iRect.height() / 2),
		Rect(iRect.right() + 1, iRect.y(), 100, 150),
		this,
		std::string("C\no\nn\nt\nr\no\nl\ns"),
		board);

	contents.push_back(controls);
}
