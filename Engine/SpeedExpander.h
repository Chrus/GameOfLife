#pragma once
#include "ExpandablePanel.h"
#include "Slider.h"
#include "TextPanel.h"

class SpeedExpander : public ExpandablePanel
{
public:
	//Constructors
	SpeedExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text);

	//Inherited via Container
	void setContents() override;

	//Functions
	int getGameSpeed() const;

private:
	Slider* speedSlider;
	TextPanel* sliderText;
	float prevSpeed = -1.0f;
};

