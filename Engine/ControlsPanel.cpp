#include "ControlsPanel.h"
ControlsPanel::ControlsPanel(Rect rect, Container* parent)
	:
	Container(rect, parent),
	playButton(Rect(rect.x(), rect.y(), 50, 50), "Images\\Play50x50new.bmp", "Images\\Stop50x50new.bmp", *this),
	stepButton(Rect(rect.x() + 51, rect.y(), 50, 50), "Images\\Step50x50new.bmp",*this)
{
	setContents();
	drawBackground = true;
	playButton.drawBorder = true;
	stepButton.drawBorder = true;
}

void ControlsPanel::setContents()
{
	contents.push_back(&playButton);
	contents.push_back(&stepButton);
}

bool ControlsPanel::checkForIteration()
{
	if (step)
	{
		step = false;
		return true;
	}

	if (play)
	{
		if (--currentTime < 0)
		{
			currentTime = updateTime;
			return false;
		}
	}
}

void ControlsPanel::playClick()
{
	play = !play;
}

void ControlsPanel::stepClick()
{
	step = true;
}
