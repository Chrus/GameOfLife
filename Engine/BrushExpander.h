#pragma once
#include "ExpandablePanel.h"
#include "RadioGroup.h"
#include "BrushRadioGroup.h"

class BrushExpander : public ExpandablePanel
{
public:
	//Constructors
	BrushExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Inherited via Container
	void setContents() override;


};

