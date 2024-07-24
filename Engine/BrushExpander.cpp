#include "BrushExpander.h"
#include "Seperator.h"
#include "Slider.h"

BrushExpander::BrushExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text)
{
	setContents();
}

DebugInfo BrushExpander::getDebugInfo() const
{
	return DebugInfo("BrushExpander","");
}

void BrushExpander::setContents()
{
	BrushRadioGroup* brush = new BrushRadioGroup(
		Rect(iRect.x(), iRect.y(), iRect.width(), 150),
		this, 2);
	brush->drawBorder = false;
	brush->color = Colors::Cyan;

	Seperator* sep1 = new Seperator(
		Tuple(iRect.x(), brush->getVisualRect().bottom()),
		iRect.width(), 5);

	TextPanel* sizeText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x(), sep1->getVisualRect().bottom(), iRect.width(), 25),
		std::string("Size"));

	Slider* sizeSlider = new Slider(
		Rect(iRect.x() + 2, sizeText->getVisualRect().bottom(), iRect.width() - 4, 10));

	TextPanel* randomText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x(), sizeSlider->getVisualRect().bottom(), iRect.width(), 25),
		std::string("Randomness"));

	Slider* randomSlider = new Slider(
		Rect(iRect.x() + 2, randomText->getVisualRect().bottom(), iRect.width() - 4, 10));

	CheckBox* fillCheckbox = new CheckBox(
		Rect(iRect.x() + 10, randomSlider->getVisualRect().bottom() + 15, 20, 20),
		*this);

	TextPanel* fillText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(fillCheckbox->getVisualRect().right(), fillCheckbox->getVisualRect().top(), 50, 25),
		std::string("Fill"));
	
	contents.push_back(brush);
	contents.push_back(sep1);
	contents.push_back(sizeText);
	contents.push_back(sizeSlider);
	contents.push_back(randomText);
	contents.push_back(randomSlider);
	contents.push_back(fillCheckbox);
	contents.push_back(fillText);
}
