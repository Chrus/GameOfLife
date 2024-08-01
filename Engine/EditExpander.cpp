#include "EditExpander.h"
#include "Seperator.h"

EditExpander::EditExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text),
	board(board)
{
	setContents();
	savedCells = new bool[1];
	undoCells = new bool[1];
}

EditExpander::~EditExpander()
{
	delete[] savedCells;
}

DebugInfo EditExpander::getDebugInfo() const
{
	return DebugInfo("EditExpander", "");
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

	load = new LoadButton(
		Rect(iRect.x() + 5, save->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Load"), *this);
	load->setState(false);

	undo = new UndoButton(
		Rect(iRect.x() + 5, load->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Undo"), *this);
	undo->setState(false);

	contents.push_back(clear);
	contents.push_back(fill);
	contents.push_back(seperator);
	contents.push_back(save);
	contents.push_back(load);
	contents.push_back(undo);
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
	load->setState(true);

	for (int x = 0; x < board.getCellCount(); x++)
		savedCells[x] = board.getCell(x)->getState();
}
void EditExpander::loadButtonClick() 
{
	delete[] undoCells;
	undoCells = new bool[board.getCellCount()]();
	for (int x = 0; x < board.getCellCount(); x++)
	{
		//First save the previous state for undo
		undoCells[x] = board.getCell(x)->getState();
		//Then update the cell from the saved state
		board.getCell(x)->setAlive(savedCells[x]);
	}
	undo->setState(true);		
}

void EditExpander::undoButtonClick()
{
	for (int x = 0; x < board.getCellCount(); x++)
		board.getCell(x)->setAlive(undoCells[x]);

	undo->setState(false);
}

void EditExpander::setUndoButton(bool state)
{
	undo->setState(state);
}

void EditExpander::setUndoCells()
{
	delete[] undoCells;
	undoCells = new bool[board.getCellCount()]();
	for (int x = 0; x < board.getCellCount(); x++)
		undoCells[x] = board.getCell(x)->getState();
	undo->setState(true);
}
