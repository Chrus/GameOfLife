#include "SpeedExpander.h"

SpeedExpander::SpeedExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text)
{
	setContents();
}

void SpeedExpander::setContents()
{
	sliderText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x() + 5, iRect.y() + 10, iRect.width() - 5, 15),
		"Simulation Speed");

	speedSlider = new Slider(
		Rect(iRect.x() + 5, sliderText->getVisualRect().bottom(), iRect.width() - 10, 20),
		this);
	speedSlider->setValueByCord(1000);

	contents.push_back(sliderText);
	contents.push_back(speedSlider);
}

int SpeedExpander::getGameSpeed() const
{
	return (100 - speedSlider->getValue()) / 8;
}