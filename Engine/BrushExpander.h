#pragma once
#include "ExpandablePanel.h"
#include "BrushManager.h"

class BrushRadioGroup;
class Slider;
class CheckBox;

class BrushExpander : public ExpandablePanel
{
public:
	//Constructors
	BrushExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void update() override;

	//Inherited via Container
	void setContents() override;

	//Functions
	void init(BrushManager* brushManager) { manager = brushManager; }
	void setBrushSelection(int selection) { manager->setBrush(selection); }
	void setBrushButton(int index);
	void togglePreview();
	void incBrushSize();
	void decBrushSize();

	//Variables
	BrushManager* manager;

private:
	BrushRadioGroup* brushButtons;
	TextPanel* sizeText;
	Slider* sizeSlider;
	TextPanel* randomText;
	Slider* randomSlider;
	CheckBox* fillCheckbox;
	CheckBox* previewCheckbox;
};

