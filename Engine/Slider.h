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
	void setValue(const int xPosition);

private:
	static constexpr int SLIDER_SIZE = 7;
	static constexpr int TRACK_THICKNESS = 2;
	Rect track;
	bool selecting = false;
	Container* parent;
};