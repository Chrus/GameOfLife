#include "ExpandablePanel.h"
#include "InputManager.h"

ExpandablePanel::ExpandablePanel(Rect expanderRect, Rect contentsRect, Container* parent, std::string text)
	:
	Container(contentsRect, parent),
	expander(expanderRect, text, *this)
{
	drawBackground = true;
	drawBorder = true;

	expander.drawBackground = true;
	expander.drawBorder = true;
	expander.borderColor = Colors::BorderBlu;
	expander.color = Colors::BackgroundBlue;
}

bool ExpandablePanel::interactsWith(const Tuple point) const
{
	if (isOpen)
	{
		bool check = false;
		if (iRect.contains(point))
			check = true;
		if (expander.interactsWith(point))
			check = true;

		return check;// iRect.contains(point) || expander.interactsWith(point);
	}
	else
		return expander.interactsWith(point);
}

bool ExpandablePanel::handleEvent(const Mouse::Event event, LRHeld held, InputManager* manager)
{
	ActionPanel::handleEvent(event, held, manager);

	if (event.GetType() == Mouse::Event::Type::LPress
		|| event.GetType() == Mouse::Event::Type::RPress)
	{
		bool inside = iRect.contains(Tuple(event.GetPos()))
			|| expander.interactsWith(Tuple(event.GetPos()));

		if(!inside)
			return inside;
	}

	Tuple mousePos = Tuple(event.GetPos());
	if (expander.interactsWith(mousePos))
		return expander.handleEvent(event, held, manager);
	else if (iRect.contains(mousePos))
	{
		Container::handleEvent(event, held, manager);
		return true;
	}
	return true;
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

bool ExpandablePanel::expanderClick(InputManager* manager)
{
	if (!isOpen)
	{
		manager->setFocus(this);
		isOpen = true;
	}
	else
		isOpen = false;

	return isOpen;
}
