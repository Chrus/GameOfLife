#pragma once
#include "Tuple.h"
#include "Mouse.h"
class InputManager;

using LRHeld = std::pair<bool, bool>;

class InputHandler
{
public:
	//return false ONLY if focus is lost AFTER the event has been performed (eg clicking an ExpandablePanel to close it)
	//Otherwise default to true.  
	virtual bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) = 0;
	//checkFocus() will only be called if it is currently focused.  
	//return false ONLY if you want focus to be removed before the event is proccessed.
	//otherwise default to true
	virtual bool checkFocus(const Mouse::Event event, const LRHeld held) const { return false; }
	virtual void loseFocus() {}
};