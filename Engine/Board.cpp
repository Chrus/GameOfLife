#include "Board.h"
#include <algorithm>
#include "InputManager.h"

Board::Board(Rect rect, Container* parent, PlayPanel* controls)
	:
	Container(rect, parent),
	playPanel(controls)
{
	//for debugging.  Shouldnt see Cyan
	color = Colors::Cyan;
	drawBorder = true;

	numCells.x = iRect.width() / Cell::DEFAULT_SIZE;
	numCells.y = iRect.height() / Cell::DEFAULT_SIZE;

	setContents();
}

Board::~Board()
{
	for (auto x : contents)
		delete x;
}

DebugInfo Board::getDebugInfo() const
{
	return DebugInfo("Board:", "number of Cells - " 
		+ std::to_string(getCellCount()));
}

void Board::update()
{
	Container::update();

	if (playPanel->checkForIteration())
	{
		for (auto x : contents)
			dynamic_cast<Cell*>(x)->updateState();
	}	
}

void Board::setContents()
{
	initCellArray(numCells.x, numCells.y);
}

void Board::handleEvent(const InputHandler::Event event, InputManager* manager)
{
	Container::handleEvent(event, manager);
	
	if (event.type == InputHandler::Event::Type::LPress
		|| event.type == InputHandler::Event::Type::RPress)
	{
		//only need to take focus the first time
		if (!event.keyHeld)
		{
			Container::handleEvent(event, manager);
			lastCellUpdated = cellAtMouse(event.mousePos);
			manager->takeFocus(this);
		}
		else  //only need to update all the cells if the mouse is on a new one
		{
			Cell* currentCell = cellAtMouse(event.mousePos);
			if (lastCellUpdated != currentCell)
			{
				Container::handleEvent(event, manager);
				lastCellUpdated = currentCell;
			}
		}
	}
}

bool Board::checkFocus(InputHandler::Event event) const
{
	if (!iRect.contains(event.mousePos)
		|| playPanel->interactsWith(event.mousePos))
		return false;
	return true;
}

void Board::loseFocus()
{
	lastCellUpdated = nullptr;
}

int Board::getCellCount() const
{
	return numCells.x * numCells.y;
}
Cell* Board::getCell(const int xPos, const int yPos) 
{
	assert(yPos * numCells.x + xPos < getCellCount());

	return dynamic_cast<Cell*>(contents[yPos * numCells.x + xPos]);
		
}
Cell* Board::getCell(const Tuple position) 
{
	return getCell(position.x, position.y);
}

Cell* Board::cellAtMouse(const Tuple mousePosition)
{
	Tuple temp = mousePosition - iRect.position;
	temp.x = temp.x % Cell::DEFAULT_SIZE;
	temp.y = temp.y % Cell::DEFAULT_SIZE;

	return getCell(temp);
}

void Board::setAllCells(bool alive)
{
	for (auto x : contents)
		dynamic_cast<Cell*>(x)->setAlive(alive);
}

void Board::initCellArray(const int xCount, const int yCount)
{
	if (!contents.empty())
	{
		for (auto x : contents)
			delete x;

		contents.clear();
		numCells = Tuple(xCount, yCount);
	}
	contents.resize(getCellCount());

	//create the cells
	for (int x = 0; x < numCells.x; x++)
	{
		for (int y = 0; y < numCells.y; y++)
		{
			Cell* cell = new Cell(Tuple(visualRect.x() + borderSize + (x * Cell::DEFAULT_SIZE),
				visualRect.y() + borderSize + (y * Cell::DEFAULT_SIZE)),
				Tuple(x,y));

			contents[y * numCells.x + x] = cell;
		}
	}

	//set the cell's neighbors
	for (int x = 0; x < numCells.x; x++)
	{
		for (int y = 0; y < numCells.y; y++)
		{
			Cell* cell = getCell(x, y);

			std::vector<Cell*> neighbors;
			//Top Left
			neighbors.push_back(getCell(correctBorderCells(x - 1, y - 1)));
			//Top Middle
			neighbors.push_back(getCell(correctBorderCells(x, y - 1)));
			//Top Right
			neighbors.push_back(getCell(correctBorderCells(x + 1, y - 1)));
			//Middle Left
			neighbors.push_back(getCell(correctBorderCells(x - 1, y)));
			//Middle Right
			neighbors.push_back(getCell(correctBorderCells(x + 1, y)));
			//Bottom Left
			neighbors.push_back(getCell(correctBorderCells(x - 1, y + 1)));
			//Bottom Middle
			neighbors.push_back(getCell(correctBorderCells(x, y + 1)));
			//Bottom Right
			neighbors.push_back(getCell(correctBorderCells(x + 1, y + 1)));

			cell->setNeighbors(neighbors);
		}
	}
}

Tuple Board::correctBorderCells(int x, int y) const
{
	Tuple fixedPosition = { x,y };

	if (x == -1)
		fixedPosition.x = numCells.x - 1;
	else if (x == numCells.x)
		fixedPosition.x = 0;

	if (y == -1)
		fixedPosition.y = numCells.y - 1;
	else if (y == numCells.y)
		fixedPosition.y = 0;

	return fixedPosition;
}