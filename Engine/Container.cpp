#include "Container.h"

Container::Container(Rect rect, Container* parent)
	:
	ActionPanel(rect),
	parent(parent)
{
	setContents();
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

std::string Container::getDebugInfo() const
{
	std::string s = "Container: " + ActionPanel::getDebugInfo();
	s.append("\n  ");

	for(const Panel* e : contents)
	{
		s.append(e->getDebugInfo());
	}
}