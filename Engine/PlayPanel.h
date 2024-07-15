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
		void handleEvent(const InputHandler::Event event, InputManager* manager) override
		{
			if (event.type == InputHandler::Event::Type::LPress
				&& !event.keyHeld)
			{
				checked = !checked;
				dynamic_cast<PlayPanel*>(parent)->playClick();
			}
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
		void handleEvent(const InputHandler::Event event, InputManager* manager) override
		{
			if (event.type == InputHandler::Event::Type::LPress
				&& !event.keyHeld)
				dynamic_cast<PlayPanel*>(parent)->stepClick();
		}
	};
	
	//Variables
	PlayButton playButton;
	StepButton stepButton;

	bool step = false;
	bool play = false;
	int updateTime = 5;
	int currentTime = 0;
};