#include "ActionPanel.h"
#include "InputManager.h"

ActionPanel::ActionPanel()
	:
	Panel(),
	iRect(visualRect)
{}

ActionPanel::ActionPanel(Rect rect)
	:
	Panel(rect),
	iRect(rect)
{}

ActionPanel::ActionPanel(Rect visualRect, Rect interactionRect)
	:
	Panel(visualRect)
{
	//iRect must always be contained by visualRect
	assert(visualRect.contains(interactionRect));

	iRect = interactionRect;
}

//Whether or not the point is on the Panel's interactable area
bool ActionPanel::interactsWith(const Tuple point) const
{
	return iRect.contains(point);
}

void ActionPanel::setIRect(const Rect newIRect)
{
	assert(visualRect.contains(newIRect));

	iRect = newIRect;
}

bool ActionPanel::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	if (event.GetType() == Mouse::Event::Type::WheelUp)
		manager->addDebugText(getDebugInfo());

	return true;
}
