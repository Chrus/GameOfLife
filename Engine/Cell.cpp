#include "Cell.h"

Cell::Cell(Tuple position, Tuple arrayPos)
	:
	ActionPanel(Rect(position.x, position.y, DEFAULT_SIZE, DEFAULT_SIZE)),
	arrayPos(arrayPos)
{
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

void Cell::handleEvent(const InputHandler::Event event, InputManager* manager)
{
	ActionPanel::handleEvent(event, manager);

	if (event.type == InputHandler::Event::Type::LPress)
		alive = true;
	else if (event.type == InputHandler::Event::Type::RPress)
		alive = false;
}

void Cell::setNeighbors(std::vector<Cell*> newNeighbors)
{	
	if (!neighbors.empty())
		neighbors.clear();
	
	for (Cell* x : newNeighbors)
		neighbors.push_back(x);
	/*for (Cell* x = newNeighbors; x != nullptr; x++)
		neighbors.push_back(x);*/
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
