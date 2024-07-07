#include "InputManager.h"

InputManager::InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel)
	:
	mouse(mouse),
	keyboard(keyboard),
	basePanel(basePanel)
{}

void InputManager::update()
{
	if (!mouse.IsEmpty())
	{
		Mouse::Event e = mouse.Read();
		Tuple mousePos = Tuple(e.GetPosX(), e.GetPosY());

		switch (e.GetType())
		{
			case Mouse::Event::Type::LPress:
			{
				handleLeftClick(e, mousePos);
				break;
			}
			case Mouse::Event::Type::RPress:
			{
				handleRightClick(e, mousePos);
				break;
			}
			//display debug panel
			case Mouse::Event::Type::WheelUp:
			{
				handleMouseWheel(e, mousePos);
				break;
			}
			//hide debug panel
			case Mouse::Event::Type::WheelDown:
			{
				handleMouseWheel(e, mousePos);
				break;
			}
		}
	}
}

void InputManager::addDebugText(DebugInfo info)
{
	debugInfo.push_back(info);
}

void InputManager::handleLeftClick(const Mouse::Event e, const Tuple mousePos)
{
	if (basePanel.interactsWith(mousePos))
		basePanel.handleEvent(InputHandler::Event(mousePos, ' ', InputHandler::Event::Type::LPress), this);
}

void InputManager::handleRightClick(const Mouse::Event e, const Tuple mousePos)
{
	if (basePanel.interactsWith(mousePos))
		basePanel.handleEvent(InputHandler::Event(mousePos, ' ', InputHandler::Event::Type::RPress), this);
}

void InputManager::handleMouseWheel(const Mouse::Event e, const Tuple mousePos)
{
	if (e.GetType() == Mouse::Event::Type::WheelUp)
	{
		if (basePanel.interactsWith(mousePos))
		{
			debugInfo.clear();
			basePanel.handleEvent(InputHandler::Event(mousePos, ' ', InputHandler::Event::Type::MWheel), this);

			assert(!debugInfo.empty());

			std::string text;
			int count = 0;

			for (auto e : debugInfo)
			{
				for (int x = 0; x < count; x++)
					text += "-";

				text += e.first;
				text += e.second + "\n";
				count++;
			}

			basePanel.updateDebugPanel(text, true);
		}
	}
	else if (e.GetType() == Mouse::Event::Type::WheelDown)
	{
		debugInfo.clear();
		basePanel.updateDebugPanel("", false);
	}
}
