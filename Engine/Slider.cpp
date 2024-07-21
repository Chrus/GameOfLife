#include "Slider.h"
#include "InputManager.h"

Slider::Slider(Rect rect)
	:
	ActionPanel(rect)
{
	iRect = Rect(visualRect.x() + (visualRect.width() / 2) - SLIDER_SIZE / 2,
		visualRect.y() + (visualRect.height() / 2) - SLIDER_SIZE / 2,
		SLIDER_SIZE,
		SLIDER_SIZE);

	track = Rect(visualRect.x() + SLIDER_SIZE,
		visualRect.y() + (visualRect.height() / 2) - (TRACK_THICKNESS / 2),
		visualRect.width() - (SLIDER_SIZE * 2), TRACK_THICKNESS);

	borderSize = 0;
}

DebugInfo Slider::getDebugInfo() const
{
	return DebugInfo("Slider","");
}

void Slider::draw(Graphics& gfx) const
{
	ActionPanel::draw(gfx);

	gfx.drawRect(track, Colors::Gray);
	gfx.drawRect(iRect, Colors::Black);
}

bool Slider::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	if (selecting && event.GetType() == Mouse::Event::Type::Move)
		setValue(event.GetPosX());
	else if (event.GetType() == Mouse::Event::Type::LPress)
	{
		selecting = true;
		manager->setFocus(this);
	}

	return true;
}

bool Slider::checkFocus(const Mouse::Event event, const LRHeld held) const
{
	return selecting && event.GetType() != Mouse::Event::Type::LRelease;
}

void Slider::loseFocus()
{
	selecting = false;
}

int Slider::getValue() const
{
	int currentValue = iRect.center().x;

	return ((currentValue - track.left())
		/ (track.right() - track.left())) * 100;
}

void Slider::setValue(const int xPosition)
{
	//This will be the center of iRect after bounds checking
	int newPosition = xPosition;

	if (xPosition < track.x())
		newPosition = track.x();
	else if (xPosition > track.right())
		newPosition = track.right();

	iRect.position.x = newPosition - SLIDER_SIZE / 2;
}