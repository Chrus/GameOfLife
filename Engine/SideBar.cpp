#include "SideBar.h"
#include "EditExpander.h"
#include "ShortcutsExpander.h"
#include "PlayPanel.h"
#include "BrushExpander.h"

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

void SideBar::init(std::vector<std::string> shortcuts, BrushManager* manager)
{
	ShortcutsExpander* s = dynamic_cast<ShortcutsExpander*>(contents[3]);
	assert(s != nullptr);
	s->setShortcutsText(shortcuts);

	BrushExpander* b = dynamic_cast<BrushExpander*>(contents[1]);
	assert(b != nullptr);
	b->init(manager);
}

PlayPanel* SideBar::getPlayPanel() const
{
	PlayPanel* ret = dynamic_cast<PlayPanel*>(contents[0]);
	assert(ret != nullptr);
	return ret;
}

void SideBar::setContents()
{
	int expanderHeight = (iRect.height() - 100) / 3;

	PlayPanel* play = new PlayPanel(
		Rect(iRect.x(), iRect.y(), 50, 100),
		this);

	BrushExpander* brush = new BrushExpander(
		Rect(iRect.x(), iRect.y() + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, iRect.y() + 100, 100, 300),
		this,
		std::string("B\nr\nu\ns\nh\ne\ns"));

	EditExpander* edit = new EditExpander(
		Rect(iRect.x(), expanderHeight + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, expanderHeight + 100, 100, 250),
		this,
		std::string("E\nd\ni\nt"),
		board);

	ShortcutsExpander* shortcuts = new ShortcutsExpander(
		Rect(iRect.x(), expanderHeight * 2 + 100, iRect.width(), expanderHeight),
		Rect(iRect.right() + 1, expanderHeight * 2 + 100, 150, 200),
		this,
		std::string("S\nh\no\nr\nt\nc\nu\nt\ns"));

	contents.push_back(play);
	contents.push_back(brush);
	contents.push_back(edit);
	contents.push_back(shortcuts);
}
