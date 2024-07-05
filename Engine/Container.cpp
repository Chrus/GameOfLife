#include "Container.h"

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

void Container::getDebugInfo(std::vector<DebugInfo>* info) const
{
	info->push_back(std::make_pair("Container", "# of Contents: " + contents.size()));
}

ActionPanel* Container::handleEvent(InputHandler::Event event)
{
	for (const auto& element : contents)
	{
		if (ActionPanel* p = dynamic_cast<ActionPanel*>(element))
		{
			if (p->interactsWith(event.mousePos))
			{
				p->handleEvent(event);
				break;
			}
		}
	}

	return nullptr;
}

bool Container::checkFocus(InputHandler::Event event) const
{
	return false;
}

void Container::loseFocus()
{
}

void Container::update()
{
	for (auto* e : contents)
		e->update();
}
void Container::draw(Graphics& gfx) const
{
	for (auto* e : contents)
		e->draw(gfx);
}
