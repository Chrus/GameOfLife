#pragma once
#include "ExpandablePanel.h"
#include "Board.h"

class EditExpander : public ExpandablePanel
{
public:
	//Constructors
	EditExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board);
	~EditExpander();

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Inherited via Container
	void setContents() override;

	//Functions
	void clearButtonClick() const;
	void fillButtonClick() const;
	void saveButtonClick();
	void loadButtonClick() const;

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
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
				dynamic_cast<EditExpander*>(parent)->clearButtonClick();
			return true;
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
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
				dynamic_cast<EditExpander*>(parent)->fillButtonClick();
			return true;
		}
	};
	class SaveButton : public Button
	{
	public:
		SaveButton(Rect rect, std::string text, ExpandablePanel& parent)
			:
			Button(rect, std::string(TextPanel::TEXT_SPRITE8X14), text, parent) {	}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("SaveButton", "");
		}
		// Inherited via ActionPanel
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
				dynamic_cast<EditExpander*>(parent)->saveButtonClick();
			return true;
		}
	};
	class LoadButton : public Button
	{
	public:
		LoadButton(Rect rect, std::string text, ExpandablePanel& parent)
			:
			Button(rect, std::string(TextPanel::TEXT_SPRITE8X14), text, parent) {	}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("LoadButton", "");
		}
		// Inherited via ActionPanel
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
				dynamic_cast<EditExpander*>(parent)->loadButtonClick();
			return true;
		}
	};

	//Variables
	Board& board;
	bool* savedCells;
};

