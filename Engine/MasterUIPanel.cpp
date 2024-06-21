#include "MasterUIPanel.h"

MasterUIPanel::MasterUIPanel()
	:
	Container(Rect(0,0, Graphics::ScreenWidth, Graphics::ScreenHeight), nullptr)
{
	setContents();
}

ActionPanel* MasterUIPanel::handleEvent(InputHandler::Event event)
{
	for (const auto& element : contents)
	{
		if (Cell* p = dynamic_cast<Cell*>(element))
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
bool MasterUIPanel::checkFocus(InputHandler::Event event) const
{
	return false;
}
void MasterUIPanel::loseFocus()
{
}

void MasterUIPanel::setContents()
{
	contents.push_back(&c1);
	contents.push_back(&c2);
	contents.push_back(&c3);
	contents.push_back(&c4);
	contents.push_back(&c5);
}

