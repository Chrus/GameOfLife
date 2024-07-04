#include "Cell.h"

Cell::Cell(Tuple position)
	:
	ActionPanel(Rect(position.x, position.y, DEFAULT_SIZE, DEFAULT_SIZE))
{}

ActionPanel* Cell::handleEvent(InputHandler::Event event)
{
	if (event.type == InputHandler::Event::Type::LPress)
	{
		alive = true;
	}
	else if (event.type == InputHandler::Event::Type::RPress)
	{
		alive = false;
	}

	return nullptr;
}
bool Cell::checkFocus(InputHandler::Event event) const
{
	return false;
}
void Cell::loseFocus()
{
}

std::string Cell::getDebugInfo() const
{
	return std::string();
}

void Cell::draw(Graphics& gfx) const
{
	if (alive)
		gfx.drawRect(visualRect, Colors::Red);
	else
		gfx.drawRect(visualRect, DEFAULT_COLOR);
}
