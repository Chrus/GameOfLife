#pragma once
#include "Container.h"
#include "CheckBox.h"

class ControlsPanel : public Container
{
public:
	//Constructor
	ControlsPanel(Rect rect, Container* parent);

	//Inherited via Container
	void setContents() override;

	//Functions
	bool checkForIteration();

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
			checked = !checked;
			dynamic_cast<ControlsPanel*>(parent)->playClick();
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
			dynamic_cast<ControlsPanel*>(parent)->stepClick();
		}
	};
	
	//Variables
	PlayButton playButton;
	void playClick();
	StepButton stepButton;
	void stepClick();

	bool step = false;
	bool play = false;
	int updateTime = 5;
	int currentTime = 0;
};