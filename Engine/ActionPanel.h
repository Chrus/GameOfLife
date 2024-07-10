#pragma once
#include "Panel.h"
#include "InputHandler.h"

class ActionPanel:public Panel, public InputHandler
{
public:
	//Constructors
	ActionPanel();
	ActionPanel(Rect rect);
	ActionPanel(Rect visualRect, Rect interactionRect);

	// Inherited via InputHandler
	void handleEvent(const InputHandler::Event event, InputManager* manager) override = 0;

	//Functions
	virtual bool interactsWith(const Tuple point) const;

protected:
	//The space of the panel that the user can interact with/click on
	Rect iRect;
};