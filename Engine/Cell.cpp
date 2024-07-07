#include "Cell.h"

Cell::Cell(Tuple position)
	:
	ActionPanel(Rect(position.x, position.y, DEFAULT_SIZE, DEFAULT_SIZE))
{}

void Cell::handleEvent(const InputHandler::Event event, InputManager* manager)
{
	ActionPanel::handleEvent(event, manager);

	if (event.type == InputHandler::Event::Type::LPress)
	{
		alive = true;
	}
	else if (event.type == InputHandler::Event::Type::RPress)
	{
		alive = false;
	}
}
bool Cell::checkFocus(InputHandler::Event event) const
{
	return false;
}
void Cell::loseFocus()
{
}

DebugInfo Cell::getDebugInfo() const
{
	return std::make_pair("Cell", "TODO");
}

void Cell::draw(Graphics& gfx) const
{
	if (alive)
		gfx.drawRect(visualRect, Colors::Red);
	else
		gfx.drawRect(visualRect, DEFAULT_COLOR);
}
