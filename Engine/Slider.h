#pragma once
#include "ActionPanel.h"
class Slider : public ActionPanel
{
public:
	//Constructors
	Slider(Rect rect);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void draw(Graphics& gfx) const override;

	//Inherited via InputHandler
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;
	bool checkFocus(const Mouse::Event event, const LRHeld held) const override;
	void loseFocus() override;

	//Functions
	int getValue() const;
	void setValue(const int xPosition);

private:
	static constexpr int SLIDER_SIZE = 7;
	static constexpr int TRACK_THICKNESS = 2;
	Rect track;
	bool selecting = false;
};

