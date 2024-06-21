#include "InputManager.h"

InputManager::InputManager(Mouse& mouse, Keyboard& keyboard, Container& basePanel)
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

		if (e.GetType() == Mouse::Event::Type::LPress)
		{
			if (basePanel.interactsWith(mousePos))
				basePanel.handleEvent(InputHandler::Event(mousePos, ' ', InputHandler::Event::Type::LPress));
		}
		else if (e.GetType() == Mouse::Event::Type::RPress)
		{
			if (basePanel.interactsWith(mousePos))
				basePanel.handleEvent(InputHandler::Event(mousePos, ' ', InputHandler::Event::Type::RPress));
		}
	}
}