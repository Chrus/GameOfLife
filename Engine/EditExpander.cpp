#include "EditExpander.h"
#include "Seperator.h"

EditExpander::EditExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text),
	board(board)
{
	setContents();
	savedCells = new bool[1];
}

EditExpander::~EditExpander()
{
	delete[] savedCells;
}

DebugInfo EditExpander::getDebugInfo() const
{
	return DebugInfo("ControlsExpander", "");
}

void EditExpander::setContents()
{
	ClearButton* clear = new ClearButton(
		Rect(iRect.x() + 5, iRect.y() + 5, iRect.width() - 10, 30),
		std::string("Clear"), *this);

	FillButton* fill = new FillButton(
		Rect(iRect.x() + 5, iRect.y() + 40, iRect.width() - 10, 30),
		std::string("Fill"), *this);

	Seperator* seperator = new Seperator(Tuple(iRect.x(), iRect.y() + 75), iRect.width(), 5);

	SaveButton* save = new SaveButton(
		Rect(iRect.x() + 5, seperator->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Save"), *this);

	LoadButton* load = new LoadButton(
		Rect(iRect.x() + 5, save->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Load"), *this);

	contents.push_back(clear);
	contents.push_back(fill);
	contents.push_back(seperator);
	contents.push_back(save);
	contents.push_back(load);
}

void EditExpander::clearButtonClick() const
{
	board.setAllCells(false);
}
void EditExpander::fillButtonClick() const
{
	board.setAllCells(true);
}
void EditExpander::saveButtonClick() 
{
	delete[] savedCells;
	savedCells = new bool[board.getCellCount()]();

	for (int x = 0; x < board.getCellCount(); x++)
		savedCells[x] = board.getCell(x)->getState();
}
void EditExpander::loadButtonClick() const
{
	for (int x = 0; x < board.getCellCount(); x++)
		board.getCell(x)->setAlive(savedCells[x]);
}
