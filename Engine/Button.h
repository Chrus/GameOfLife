#pragma once
#include "ActionPanel.h"
#include "TextPanel.h"

class Button : public ActionPanel
{
public:
	//Constructors
	Button(Rect rect, std::string buttonText);

	//Inherited via Panel
	void draw(Graphics& gfx) const override;

protected:
	TextPanel text;
};