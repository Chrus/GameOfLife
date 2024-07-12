#pragma once
#include "Container.h"
#include "TextPanel.h"

class Button : public ActionPanel
{
public:
	//Constructors
	Button();
	Button(Rect rect, Container& parent);
	Button(Rect rect, std::string fileName, Container& parent);
	Button(Rect rect, std::string fileName, std::string text, Container& parent);
	~Button();

	//Inherited via Panel
	void draw(Graphics& gfx) const override;

protected:
	SpritePanel* sprite = nullptr;
	Container* parent;
};