#pragma once
#include "Button.h"
class CheckBox : public Button
{
public:
	//Constructors
	CheckBox();
	CheckBox(Rect rect, std::string fileName, std::string checkedFileName, Container& parent);
	~CheckBox();

	//Inherited via Panel
	void draw(Graphics& gfx) const override;

protected:
	SpritePanel* checkedSprite = nullptr;
	bool checked = false;
};

