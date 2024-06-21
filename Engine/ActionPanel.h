#pragma once
#include "Panel.h"
#include "InputHandler.h"

class ActionPanel:public Panel, InputHandler
{
public:
	//Constructors
	ActionPanel();
	ActionPanel(Rect rect);
	ActionPanel(Rect visualRect, Rect interactionRect);

	//Functions
	virtual bool interactsWith(const Tuple point) const;
	//std::string getDebugInfo() const override;

protected:
	//The space of the panel that the user can interact with/click on
	Rect iRect;
};