#include "Cell.h"
#include "Mouse.h"

Cell::Cell(Tuple position, Tuple arrayPos)
	:
	ActionPanel(Rect(position.x, position.y, DEFAULT_SIZE, DEFAULT_SIZE)),
	arrayPos(arrayPos)
{
	borderSize = 1;
	drawBorder = true;
}

void Cell::update()
{
	int aliveCount = 0;
	for (auto* x : neighbors)
		if (x->alive)
			aliveCount++;

	if (alive)
	{
		if (aliveCount < 2 || aliveCount > 3)
			switchState = true;
	}
	else //if dead
	{
		if (aliveCount == 3)
			switchState = true;
	}
}

bool Cell::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	ActionPanel::handleEvent(event, held, manager);

	if (event.LeftIsPressed() && !alive)
		switchState = true;
	else if (event.RightIsPressed() && alive)
		switchState = true;

	return true;
}

void Cell::setNeighbors(std::vector<Cell*> newNeighbors)
{	
	if (!neighbors.empty())
		neighbors.clear();
	
	for (Cell* x : newNeighbors)
		neighbors.push_back(x);
}

void Cell::updateState()
{
	if (switchState)
		alive = !alive;
	switchState = false;
}

void Cell::setAlive(bool cellAlive)
{
	alive = cellAlive;
	switchState = false;
}

DebugInfo Cell::getDebugInfo() const
{
	return std::make_pair("Cell:", "{" + std::to_string(arrayPos.x)
		+ "," + std::to_string(arrayPos.y) + "}");
}

void Cell::draw(Graphics& gfx) const
{
	if (alive)
		gfx.drawRect(visualRect, Colors::White);
	else
		gfx.drawRect(visualRect, Colors::Black);

	if (drawBorder)
		gfx.drawBorder(visualRect, DEFAULT_BORDER_COLOR, borderSize);
}
