#include "Container.h"
#include "InputManager.h"

Container::Container(Rect rect, Container* parent)
	:
	ActionPanel(rect),
	parent(parent)
{}

//checks to see if point is in a clickable area of the container.
bool Container::interactsWith(const Tuple point) const
{
	if (!iRect.contains(point))
		return false;

	for (const auto& element : contents)
	{
		if (ActionPanel* p = dynamic_cast<ActionPanel*>(element))
		{
			if (p->interactsWith(point))
				return true;
		}
	}

	return false;
}

void Container::update()
{
	for (auto* e : contents)
		e->update();
}
void Container::draw(Graphics& gfx) const
{
	ActionPanel::draw(gfx);

	for (auto* e : contents)
		e->draw(gfx);
}
DebugInfo Container::getDebugInfo() const
{
	return std::make_pair("Container", "# of Contents: " + std::to_string(contents.size()));
}

void Container::handleEvent(const InputHandler::Event event, InputManager* manager)
{
	ActionPanel::handleEvent(event, manager);

	ActionPanel* last = nullptr;
	for (const auto& element : contents)
	{
		if (ActionPanel* p = dynamic_cast<ActionPanel*>(element))
		{
			if (p->interactsWith(event.mousePos))
			{
				last = p;
				//p->handleEvent(event, manager);
				//break;
			}
		}
	}
	if (last != nullptr)
		last->handleEvent(event, manager);
}
bool Container::checkFocus(InputHandler::Event event) const
{
	return false;
}
void Container::loseFocus()
{
}