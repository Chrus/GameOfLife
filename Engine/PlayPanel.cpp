#include "PlayPanel.h"
PlayPanel::PlayPanel(Rect rect, Container* parent)
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

void PlayPanel::setContents()
{
	contents.push_back(&playButton);
	contents.push_back(&stepButton);
}

bool PlayPanel::checkForIteration()
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
			return true;
		}
	}

	return false;
}

void PlayPanel::playClick()
{
	play = !play;
}

void PlayPanel::stepClick()
{
	step = true;
}
