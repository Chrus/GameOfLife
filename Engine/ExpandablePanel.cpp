#include "ExpandablePanel.h"
#include "InputManager.h"

ExpandablePanel::ExpandablePanel(Rect expanderRect, Rect contentsRect, Container* parent, std::string text)
	:
	Container(contentsRect, parent),
	expander(expanderRect, text, this)
{
}

bool ExpandablePanel::interactsWith(const Tuple point) const
{
	if (isOpen)
		return iRect.contains(point) || expander.interactsWith(point);
	else
		return expander.interactsWith(point);
}

void ExpandablePanel::handleEvent(const InputHandler::Event event, InputManager* manager)
{
	ActionPanel::handleEvent(event, manager);

	if (expander.interactsWith(event.mousePos))
		expander.handleEvent(event, manager);
	else if (Container::interactsWith(event.mousePos))
		Container::handleEvent(event, manager);
}

bool ExpandablePanel::checkFocus(InputHandler::Event event) const
{
	if (event.type == InputHandler::Event::Type::LPress
		|| event.type == InputHandler::Event::Type::RPress)
		return iRect.contains(event.mousePos)
		|| expander.interactsWith(event.mousePos);

	return false;
}

void ExpandablePanel::loseFocus()
{
	isOpen = false;
}

void ExpandablePanel::draw(Graphics& gfx) const
{
	if (isOpen)
		Container::draw(gfx);

	expander.draw(gfx);
}

DebugInfo ExpandablePanel::getDebugInfo() const
{
	return DebugInfo("Expandable Panel", "");
}

void ExpandablePanel::expanderClick(InputManager* manager)
{
	if (!isOpen)
	{
		manager->takeFocus(this);
		isOpen = true;
	}
	else
	{
		manager->removeFocus(this);
		loseFocus();
	}
}
