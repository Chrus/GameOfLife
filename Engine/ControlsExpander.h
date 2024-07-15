#pragma once
#include "ExpandablePanel.h"
#include "Board.h"

class ControlsExpander : public ExpandablePanel
{
public:
	//Constructors
	ControlsExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Inherited via Container
	void setContents();

	//Functions
	void clearButtonClick() const;
	void fillButtonClick() const;

private:
	class ClearButton : public Button
	{
	public:
		ClearButton(Rect rect, std::string text, ExpandablePanel& parent)
			:
			Button(rect, std::string(TextPanel::TEXT_SPRITE8X14), text, parent) {	}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("ClearButton", "");
		}
		// Inherited via ActionPanel
		void handleEvent(const InputHandler::Event event, InputManager* manager) override
		{
			if (event.type == InputHandler::Event::Type::LPress && !event.keyHeld)
				dynamic_cast<ControlsExpander*>(parent)->clearButtonClick();
		}
	};
	class FillButton : public Button
	{
	public:
		FillButton(Rect rect, std::string text, ExpandablePanel& parent)
			:
			Button(rect, std::string(TextPanel::TEXT_SPRITE8X14), text, parent) {	}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("FillButton", "");
		}
		// Inherited via ActionPanel
		void handleEvent(const InputHandler::Event event, InputManager* manager) override
		{
			if (event.type == InputHandler::Event::Type::LPress && !event.keyHeld)
				dynamic_cast<ControlsExpander*>(parent)->fillButtonClick();
		}
	};

	//Variables
	Board& board;
};

