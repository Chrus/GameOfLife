#include "InputManager.h"

InputManager::InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel)
	:
	mouse(mouse),
	keyboard(keyboard),
	basePanel(basePanel)
{}

void InputManager::update()
{
	if (!mouse.LeftIsPressed())
	{
		leftHeld = false;
		return;
	}

	if (mouse.LeftIsPressed() && !leftHeld)
	{
		//temp handling focus until this is reworked
		if (handleFocus(InputHandler::Event({ mouse.GetPosX(), mouse.GetPosY() }, ' ', InputHandler::Event::Type::LPress)))
		{
			leftHeld = true;
			return;
		}

		handleLeftClick(InputHandler::Event({ mouse.GetPosX(), mouse.GetPosY() }, ' ', InputHandler::Event::Type::LPress));
	}

	return;

	//Todo I need to revise all of this
	while (!mouse.IsEmpty())
	{
		Mouse::Event chiliEvent = mouse.Read();
		//if (!chiliEvent.IsValid() || chiliEvent.GetType() == Mouse::Event::Type::Move
		//	)//|| chiliEvent.GetType() == Mouse::Event::Type::LRelease)
		//	return;

		InputHandler::Event e = translateEvent(chiliEvent);
		//if (e.type == InputHandler::Event::Type::Invalid)
		//	return;

		if (chiliEvent.GetType() == Mouse::Event::Type::LRelease)
		{
			leftHeld = false;
			return;
		}
		//if (e.type == InputHandler::Event::Type::LPress && leftHeld)
		//	return;
		
		//if true the focused panel is claiming the event and will handle it directly
		//if false then process the event from the start
		if (handleFocus(e))
			return;

		switch (chiliEvent.GetType())
		{
			case Mouse::Event::Type::LPress:
			{
				handleLeftClick(e);
				break;
			}
			case Mouse::Event::Type::RPress:
			{
				handleRightClick(e);
				break;
			}
			//display debug panel
			case Mouse::Event::Type::WheelUp:
			{
				handleMouseWheel(e, chiliEvent);
				break;
			}
			//hide debug panel
			case Mouse::Event::Type::WheelDown:
			{
				handleMouseWheel(e, chiliEvent);
				break;
			}
		}
	}
}

void InputManager::addDebugText(DebugInfo info)
{
	debugInfo.push_back(info);
}

void InputManager::takeFocus(ActionPanel* panel)
{
	focusedPanel = panel;
}
void InputManager::removeFocus(ActionPanel* panel)
{
	assert(panel == focusedPanel);

	panel->loseFocus();
	focusedPanel = nullptr;
}

InputHandler::Event InputManager::translateEvent(const Mouse::Event e)
{
	switch (e.GetType())
	{
	case Mouse::Event::Type::LPress:
		return InputHandler::Event({ e.GetPosX(), e.GetPosY() }, ' ', InputHandler::Event::Type::LPress);
	case Mouse::Event::Type::RPress:
		return InputHandler::Event({ e.GetPosX(), e.GetPosY() }, ' ', InputHandler::Event::Type::RPress);
	case Mouse::Event::Type::WheelUp:
	case Mouse::Event::Type::WheelDown:
		return InputHandler::Event({ e.GetPosX(), e.GetPosY() }, ' ', InputHandler::Event::Type::MWheel);
	}

	return InputHandler::Event({ -1,-1 }, ' ', InputHandler::Event::Type::Invalid);
}

bool InputManager::handleFocus(const InputHandler::Event e)
{
	if (focusedPanel == nullptr)
		return false;

	if (focusedPanel->checkFocus(e))
	{
		focusedPanel->handleEvent(e, this);
		return true;
	}
	else
	{
		focusedPanel->loseFocus();
		focusedPanel = nullptr;
		return false;
	}
}

void InputManager::handleLeftClick(const InputHandler::Event e)
{
	leftHeld = true;

	if (basePanel.interactsWith(e.mousePos))
		basePanel.handleEvent(e, this);
}
void InputManager::handleRightClick(const InputHandler::Event e)
{
	if (basePanel.interactsWith(e.mousePos))
		basePanel.handleEvent(e, this);
}
void InputManager::handleMouseWheel(InputHandler::Event e, Mouse::Event wheelE)
{
	if (wheelE.GetType() == Mouse::Event::Type::WheelUp)
	{
		if (basePanel.interactsWith(e.mousePos))
		{
			debugInfo.clear();
			basePanel.handleEvent(e, this);

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
	else if (wheelE.GetType() == Mouse::Event::Type::WheelDown)
	{
		debugInfo.clear();
		basePanel.updateDebugPanel("", false);
	}
}
