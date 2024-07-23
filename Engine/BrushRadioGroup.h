#pragma once
#include "RadioGroup.h"

class BrushRadioGroup : public RadioGroup
{
public:
	//Constructors
	BrushRadioGroup(Rect rect, Container* parent, int columnSize);

	//Inherited via Container
	virtual void setContents();

private:
	class BrushButton : public CheckBox
	{
	public:
		BrushButton(Rect rect, Container& parent)
			:
			CheckBox(rect, parent)
		{}
		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("BrushButton", "");
		}
		//Inherited via ActinPanel
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			CheckBox::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
			{
				dynamic_cast<BrushRadioGroup*>(parent)->select(this);
			}
			return true;
		}
	};
};

