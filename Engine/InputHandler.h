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
			MWheel,
			Invalid
		};

		Event(Tuple mousePos, char key, Type type, bool keyHeld)
			:
			mousePos(mousePos),
			key(key),
			type(type),
			keyHeld(keyHeld)
		{}

		const Tuple mousePos;
		const char key;
		const Type type;
		const bool keyHeld;
	};

	virtual void handleEvent(const InputHandler::Event event, InputManager* manager) = 0;
	//return true if the event is part of a multistep action.  The event can be passed directly to this focused panel to proccess
	//return false if the event causes the currently focused panel to lose it's focus
	virtual bool checkFocus(InputHandler::Event event) const { return false; }
	virtual void loseFocus() {}
};