#include "ActionPanel.h"

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

std::string ActionPanel::getDebugInfo() const
{
	std::string s = "ActionPanel: \n -";

	if (visualRect == iRect)
		s.append("Visual/Interactive Rect: " + visualRect.toString());
	else
	{
		s.append("Visual Rect: " + visualRect.toString() + "\n -");
		s.append("Interactive Rect: " + iRect.toString());
	}	

	return s;
}
