#include "PlayPanel.h"
PlayPanel::PlayPanel(Rect rect, Container* parent)
	:
	Container(rect, parent),
	playButton(Rect(rect.x(), rect.y(), 50, 50), "Images\\Play50x50new.bmp", "Images\\Stop50x50new.bmp", *this),
	stepButton(Rect(rect.x(), rect.y() + 50, 50, 50), "Images\\Step50x50new.bmp",*this)
{
	setContents();
	drawBackground = true;
	playButton.borderColor = Colors::BorderBlu;
	playButton.drawBackground = false;
	stepButton.borderColor = Colors::BorderBlu;
	stepButton.drawBackground = false;
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
	//checkbox sets checked.  But we also do it
	//because shortcuts calls this function too.
	playButton.checked = play;
}

void PlayPanel::stepClick()
{
	step = true;
}
