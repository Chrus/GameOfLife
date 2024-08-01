#pragma once
#include "Container.h"
#include "CheckBox.h"

class PlayPanel : public Container
{
public:
	//Constructor
	PlayPanel(Rect rect, Container* parent);

	//Inherited via Container
	void setContents() override;

	//Functions
	bool checkForIteration();
	void playClick();
	void stepClick();

private:
	class PlayButton : public CheckBox
	{
	public:
		PlayButton(Rect rect, std::string fileName, std::string checkedFileName, Container& parent)
			:
			CheckBox(rect, fileName, checkedFileName, parent) {}
		// Inherited via Button
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("PlayButton", "");
		}
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			CheckBox::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
			{
				dynamic_cast<PlayPanel*>(parent)->playClick();
			}
			return true;
		}
	};
	class StepButton : public Button
	{
	public:
		StepButton(Rect rect, std::string fileName, Container& parent)
			:
			Button(rect, fileName, parent) {}
		// Inherited via Button
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("StepButton", "");
		}
		bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
				dynamic_cast<PlayPanel*>(parent)->stepClick();
			return true;
		}
	};
	
	//Variables
	PlayButton playButton;
	StepButton stepButton;

	bool step = false;
	bool play = false;
	int updateTime = 0;
	int currentTime = 0;
};