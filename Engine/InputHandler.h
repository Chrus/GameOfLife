#pragma once
class ActionPanel;
#include "Tuple.h"

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

	virtual ActionPanel* handleEvent() = 0;
	virtual bool checkFocus() const = 0;
	virtual void loseFocus() = 0;
};

