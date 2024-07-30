#pragma once
#include "RadioGroup.h"
#include "BrushExpander.h"

class BrushRadioGroup : public RadioGroup
{
public:
	//Constructors
	BrushRadioGroup(Rect rect, Container* parent, int columnSize);

	//Inherited via Container
	virtual void setContents();

	//Inherited via RadioGroup
	void select(CheckBox* button) override;

	//Functions
	BrushExpander* getExpander() const { return dynamic_cast<BrushExpander*>(parent); }

private:
	class BrushButton : public CheckBox
	{
	public:
		BrushButton(Rect rect, Container& parent, int index)
			:
			CheckBox(rect, parent),
			index(index)
		{}
		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("BrushButton", "");
		}
		//Inherited via ActionPanel
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
		//Inherited via Button
		void drawCustom(Graphics& gfx) const override
		{
			if (checked)
				gfx.drawRect(iRect.getExpanded(borderSize * -1), Colors::White);

			dynamic_cast<BrushRadioGroup*>(parent)->getExpander()->manager->getBrush(index)->drawThumbnail(gfx, iRect);
		}

		int index;
	};
};

