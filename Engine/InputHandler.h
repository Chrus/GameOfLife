#pragma once
#include "Tuple.h"
class InputManager;

class InputHandler
{
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			RPress,
			LoseFocus,
			MWheel,
			Invalid
		};

		Event(Tuple mousePos, char key, Type type)
			:
			mousePos(mousePos),
			key(key),
			type(type)
		{}

		const Tuple mousePos;
		const char key;
		const Type type;
	};

	virtual void handleEvent(const InputHandler::Event event, InputManager* manager) = 0;
	virtual bool checkFocus(InputHandler::Event event) const = 0;
	virtual void loseFocus() = 0;
};