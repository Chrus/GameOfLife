#include "SideBar.h"
#include "ShortcutsExpander.h"
#include "PlayPanel.h"
#include "BrushExpander.h"
#include "SpeedExpander.h"

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

void SideBar::init(std::vector<std::string> shortcutsText, BrushManager* manager)
{
	shortcuts->setShortcutsText(shortcutsText);
	brush->init(manager);
}

void SideBar::setContents()
{
	int expanderHeight = (iRect.height() - 100) / 3;

	play = new PlayPanel(
		Rect(iRect.x(), iRect.y(), 50, 100),
		this);

	speed = new SpeedExpander(
		Rect(play->getVisualRect().right(), iRect.y(), 25, 100),
		Rect(iRect.right(), iRect.y() + 25, 150, 50),
		this,
		">");
	play->init(speed);

	brush = new BrushExpander(
		Rect(iRect.x(), iRect.y() + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, iRect.y() + 100, 150, 350),
		this,
		std::string("B\nr\nu\ns\nh\ne\ns"));

	edit = new EditExpander(
		Rect(iRect.x(), expanderHeight + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, expanderHeight + 100, 150, 293),
		this,
		std::string("E\nd\ni\nt"),
		board);

	shortcuts = new ShortcutsExpander(
		Rect(iRect.x(), expanderHeight * 2 + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, expanderHeight * 2 + 100, 150, 200),
		this,
		std::string("S\nh\no\nr\nt\nc\nu\nt\ns"));

	contents.push_back(play);
	contents.push_back(speed);
	contents.push_back(brush);
	contents.push_back(edit);
	contents.push_back(shortcuts);
}
