#pragma once
#include "Container.h"
#include "CheckBox.h"
#include "Rect.h"

class RadioGroup : public Container
{
public:
	//Constructors
	RadioGroup(Rect rect, Container* parent, int columnSize);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override
	{
		return DebugInfo("Radio Button Group", "");
	}

protected:
	//Variables
	int columnSize = 1;
	int buttonCount = 0;
	CheckBox* selected = nullptr;

	virtual void select(CheckBox* button);
	void addButton(CheckBox* newButton) ;
};

