#include "ControlsExpander.h"

ControlsExpander::ControlsExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text),
	board(board)
{
	setContents();
}

DebugInfo ControlsExpander::getDebugInfo() const
{
	return DebugInfo("ControlsExpander", "");
}

void ControlsExpander::setContents()
{
	ClearButton* clear = new ClearButton(
		Rect(iRect.x() + 5, iRect.y() + 5, iRect.width() - 10, 30),
		std::string("Clear"), *this);
	clear->drawBorder = true;
	clear->drawBackground = true;
	clear->color = Colors::LightGray;

	FillButton* fill = new FillButton(
		Rect(iRect.x() + 5, iRect.y() + 35, iRect.width() - 10, 30),
		std::string("Fill"), *this);
	fill->drawBorder = true;
	fill->drawBackground = true;
	fill->color = Colors::LightGray;

	contents.push_back(clear);
	contents.push_back(fill);
}

void ControlsExpander::clearButtonClick() const
{
	board.setAllCells(false);
}

void ControlsExpander::fillButtonClick() const
{
	board.setAllCells(true);
}
