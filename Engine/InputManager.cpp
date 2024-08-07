#include "InputManager.h"

InputManager::InputManager(Mouse& mouse, Keyboard& keyboard, MasterUIPanel& basePanel)
	:
	mouse(mouse),
	keyboard(keyboard),
	basePanel(basePanel)
{}

void InputManager::update()
{
	shortcuts->checkKey(keyboard.ReadChar());
	
	Mouse::Event e = mouse.Read();
	while (e.IsValid())
	{
		if (e.GetType() == Mouse::Event::Type::WheelUp
			|| e.GetType() == Mouse::Event::Type::WheelDown)
			shortcuts->handleMouseWheel(e);
		{
			//checking to see if panel removes focus before the event is proccessed
			handleFocus(e);
			if (focusedPanel != nullptr)
			{
				//checking to see if the panel removes focus after proccesing the event
				if (!focusedPanel->handleEvent(e, LRHeld(leftHeld, rightHeld), this))
				{
					focusedPanel->loseFocus();
					focusedPanel = nullptr;
				}
			}
			else
				basePanel.handleEvent(e, LRHeld(leftHeld, rightHeld), this);


			e = mouse.Read();
		}
	}
	leftHeld = mouse.LeftIsPressed();
	rightHeld = mouse.RightIsPressed();
}

void InputManager::addDebugText(DebugInfo info)
{
	debugInfo.push_back(info);
}

void InputManager::setFocus(ActionPanel* panel)
{
	focusedPanel = panel;
}

void InputManager::setShortcutManager(ShortcutManager* shortcuts)
{
	this->shortcuts = shortcuts;
}

void InputManager::handleFocus(const Mouse::Event e)
{
	if (focusedPanel == nullptr)
		return;

	//First check to see if the event is valid for the panel's current action
	bool stillFocused = focusedPanel->checkFocus(e, LRHeld(leftHeld, rightHeld));

	if (!stillFocused)
	{
		focusedPanel->loseFocus();
		focusedPanel = nullptr;
	}
}

void InputManager::handleMouseWheel(Mouse::Event e)
{
	//Old code for a debug panel that i plan to remove

	//if (e.GetType() == Mouse::Event::Type::WheelUp)
	//{
	//	if (basePanel.getVisualRect().contains(Tuple(e.GetPos())))
	//	{
	//		//if (focusedPanel == nullptr)
	//		//	basePanel.updateDebugPanel("Null", true);
	//		//else
	//		//	basePanel.updateDebugPanel(focusedPanel->getDebugInfo().first, true);
	//		debugInfo.clear();
	//		basePanel.handleEvent(e, LRHeld(leftHeld,rightHeld), this);

	//		assert(!debugInfo.empty());

	//		std::string text;
	//		int count = 0;

	//		for (auto e : debugInfo)
	//		{
	//			for (int x = 0; x < count; x++)
	//				text += "-";

	//			text += e.first;
	//			text += e.second + "\n";
	//			count++;
	//		}

	//		basePanel.updateDebugPanel(text, true);
	//	}
	//}
	//else if (e.GetType() == Mouse::Event::Type::WheelDown)
	//{
	//	debugInfo.clear();
	//	basePanel.updateDebugPanel("", false);
	//}
}
