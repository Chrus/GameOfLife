#include "Board.h"
#include <algorithm>
#include "InputManager.h"

Board::Board(Rect rect, Container* parent)
	:
	Container(rect, parent)
{
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
	//Dont update the board if in the middle of clickndraging
	if (lastCellUpdated != nullptr)
		return;

	if (playPanel->checkForIteration())
	{
		Container::update();

		for (auto x : contents)
			dynamic_cast<Cell*>(x)->updateState();
	}	
}

void Board::draw(Graphics& gfx) const
{
	ActionPanel::draw(gfx);

	for (int x = 0; x < contents.size(); x++)
	{
		Cell* cell = dynamic_cast<Cell*>(contents[x]);
		assert(cell != nullptr);

		cell->draw(gfx);
		if (selectedCells.find(x) != selectedCells.end())
			gfx.drawRect(cell->getVisualRect().getExpanded((Cell::DEFAULT_SIZE / 4) * -1), Colors::Gray);
	}
}

void Board::setContents()
{
	Tuple extraSize = { visualRect.width() - (numCells.x * Cell::DEFAULT_SIZE),
		visualRect.height() - (numCells.y * Cell::DEFAULT_SIZE) };

	if (extraSize.x > 0 || extraSize.y > 0)
	{
		//centering the cell area inside the extra board space
		iRect = Rect(visualRect.x() + extraSize.x / 2,
			visualRect.y() + extraSize.y / 2,
			numCells.x * Cell::DEFAULT_SIZE,
			numCells.y * Cell::DEFAULT_SIZE);
	}

	initCellArray(numCells.x, numCells.y);
}

bool Board::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	//Using ActionPanel:: not Container:: to handle debug events but not cells
	ActionPanel::handleEvent(event, held, manager);
	
	if (event.GetType() == Mouse::Event::Type::LPress
		|| event.GetType() == Mouse::Event::Type::RPress)
	{
		manager->setFocus(this);
		lastCellUpdated = cellAtMouse(Tuple(event.GetPos()));
		lastCellUpdated->handleEvent(event, held, manager);
		selectedCells.insert(tupToIndex(lastCellUpdated->arrayPosition()));
	}
	else if (event.GetType() == Mouse::Event::Type::Move
		&& iRect.contains(event.GetPos())
		&& lastCellUpdated != nullptr)
	{
		Cell* currentCell = cellAtMouse(Tuple(event.GetPos()));
		//if not on the last cell selected
		if (lastCellUpdated != currentCell)
		{
			lastCellUpdated = currentCell;
			lastCellUpdated->handleEvent(event, held, manager);
			selectedCells.insert(tupToIndex(lastCellUpdated->arrayPosition()));
		}
	}
	else if (event.GetType() == Mouse::Event::Type::LRelease
		|| event.GetType() == Mouse::Event::Type::RRelease)
		return false;

	return true;
}

void Board::loseFocus()
{
	for (int x : selectedCells)
		dynamic_cast<Cell*>(contents[x])->updateState();

	lastCellUpdated = nullptr;
	selectedCells.clear();
}

int Board::getCellCount() const
{
	return numCells.x * numCells.y;
}

Cell* Board::getCell(const int xPos, const int yPos) 
{
	//assert(yPos * numCells.x + xPos < getCellCount());
	if (yPos * numCells.x + xPos >= getCellCount())
	{
		selectedCells.insert(10);
	}
	
	return dynamic_cast<Cell*>(contents[yPos * numCells.x + xPos]);
		
}
Cell* Board::getCell(const Tuple position) 
{
	return getCell(position.x, position.y);
}
Cell* Board::getCell(const int position)
{
	return dynamic_cast<Cell*>(contents[position]);
}

Cell* Board::cellAtMouse(const Tuple mousePosition)
{
	Tuple temp = mousePosition - iRect.position;
	temp.x = temp.x / Cell::DEFAULT_SIZE;
	temp.y = temp.y / Cell::DEFAULT_SIZE;

	return getCell(temp);
}

void Board::setAllCells(bool alive)
{
	for (auto* x : contents)
		dynamic_cast<Cell*>(x)->setAlive(alive);
}

int Board::tupToIndex(const Tuple arrayPosition) const
{
	int cellIndex = arrayPosition.y * numCells.x + arrayPosition.x;
	assert(cellIndex < numCells.x * numCells.y);

	return cellIndex;
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
			Cell* cell = new Cell(Tuple(iRect.x() + (x * Cell::DEFAULT_SIZE),
				iRect.y() + (y * Cell::DEFAULT_SIZE)),
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