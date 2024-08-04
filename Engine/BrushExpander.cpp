#include "BrushExpander.h"
#include "Seperator.h"
#include "BrushRadioGroup.h"
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

void BrushExpander::update()
{
	manager->setRandomness(randomSlider->getRatio());
	int rand = randomSlider->getRatio() * 100;
	randomText->setText("Randomness: " + std::string(std::to_string(rand)) + "%");

	manager->setSize(sizeSlider->getRatio());
	int temp = std::max(1, manager->getSize(manager->currentBrush->maxSize));
	sizeText->setText(std::string("Size: " + std::to_string(temp)));

	manager->setFill(fillCheckbox->checked);

	manager->preview = previewCheckbox->checked;
}

void BrushExpander::setContents()
{
	brushButtons = new BrushRadioGroup(
		Rect(iRect.x(), iRect.y(), iRect.width(), 215),
		this, 2);
	brushButtons->drawBorder = false;
	brushButtons->color = Colors::Cyan;

	Seperator* sep1 = new Seperator(
		Tuple(iRect.x(), brushButtons->getVisualRect().bottom()),
		iRect.width(), 5);

	previewCheckbox = new CheckBox(
		Rect(iRect.x() + 10, sep1->getVisualRect().bottom() + 5, 20, 20),
		*this);
	previewCheckbox->checked = true;

	TextPanel* previewText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(previewCheckbox->getVisualRect().right() + 5, previewCheckbox->getVisualRect().top(), 100, 25),
		std::string("Show Preview"));

	Seperator* sep2 = new Seperator(
		Tuple(iRect.x(), previewCheckbox->getVisualRect().bottom() + 5),
		iRect.width(), 5);

	sizeText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x(), sep2->getVisualRect().bottom(), iRect.width(), 25),
		std::string("Size"));

	sizeSlider = new Slider(
		Rect(iRect.x() + 2, sizeText->getVisualRect().bottom(), iRect.width() - 4, 10), this);
	sizeSlider->setValue(0);

	randomText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x(), sizeSlider->getVisualRect().bottom(), iRect.width(), 25),
		std::string("Randomness"));

	randomSlider = new Slider(
		Rect(iRect.x() + 2, randomText->getVisualRect().bottom(), iRect.width() - 4, 10), this);
	randomSlider->setValue(0);

	fillCheckbox = new CheckBox(
		Rect(iRect.x() + 10, randomSlider->getVisualRect().bottom() + 15, 20, 20),
		*this);

	TextPanel* fillText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(fillCheckbox->getVisualRect().right(), fillCheckbox->getVisualRect().top(), 50, 25),
		std::string("Fill"));
	
	contents.push_back(brushButtons);
	contents.push_back(sep1);
	contents.push_back(previewCheckbox);
	contents.push_back(previewText);
	contents.push_back(sep2);
	contents.push_back(sizeText);
	contents.push_back(sizeSlider);
	contents.push_back(randomText);
	contents.push_back(randomSlider);
	//contents.push_back(fillCheckbox);
	//contents.push_back(fillText);
}
