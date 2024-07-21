#pragma once
#include "Button.h"
class CheckBox : public Button
{
public:
	//Constructors
	CheckBox();
	CheckBox(Rect rect, Container& parent);
	CheckBox(Rect rect, std::string fileName, std::string checkedFileName, Container& parent);
	~CheckBox();

	//Inherited via Panel
	void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override
	{
		return DebugInfo("Checkbox", "");
	}

	//Inherited via ActionPanel
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;

	//Variables
	bool checked = false;

protected:
	//Variables
	SpritePanel* checkedSprite = nullptr;

	//Functions
	void drawCustom(Graphics& gfx) const override;
};