#include "Container.h"
#include "InputManager.h"

Container::Container(Rect rect, Container* parent)
	:
	ActionPanel(rect),
	parent(parent)
{}

Container::~Container()
{
	//for (auto* e : contents)
	//	delete e;
}

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

bool Container::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	ActionPanel::handleEvent(event, held, manager);

	if (event.GetType() == Mouse::Event::Type::LPress)
	{
		ActionPanel* p = dynamic_cast<ActionPanel*>(contents[1]);

	}

	//ActionPanel* last = nullptr;
	for (const auto& element : contents)
	{
		if (ActionPanel* p = dynamic_cast<ActionPanel*>(element))
		{
			if (p->interactsWith(Tuple(event.GetPos())))
			{
				//last = p;
				p->handleEvent(event, held, manager);
				break;
			}
		}
	}
	//if (last != nullptr)
	//	return last->handleEvent(event, held, manager);

	return true;
}