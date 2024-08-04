#pragma once
#include "Container.h"

class Slider : public ActionPanel
{
public:
	//Constructors
	Slider(Rect rect, Container* parent);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void draw(Graphics& gfx) const override;

	//Inherited via ActionPanel
	bool interactsWith(const Tuple point) const override;

	//Inherited via InputHandler
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;

	//Functions
	int getValue() const;
	float getRatio() const;
	void setValueByCord(const int xPosition);
	void setValue(float value, float maxValue);

private:
	//There will be a bug in setValue() if SLIDER_SIZE is changed
	//see setValue() for more info
	static constexpr int SLIDER_SIZE = 7; 
	static constexpr int TRACK_THICKNESS = 2;
	Rect track;
	bool selecting = false;
	Container* parent;
};