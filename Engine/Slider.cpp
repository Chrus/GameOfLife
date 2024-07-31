#include "Slider.h"
#include "InputManager.h"

Slider::Slider(Rect rect, Container* parent)
	:
	ActionPanel(rect),
	parent(parent)
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

bool Slider::interactsWith(const Tuple point) const
{
	return visualRect.contains(point);
}

bool Slider::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	if (selecting && event.GetType() == Mouse::Event::Type::Move)
		setValue(event.GetPosX());
	else if (event.GetType() == Mouse::Event::Type::LPress)
	{
		selecting = true;
		setValue(event.GetPosX());
		manager->setFocus(this);
	}
	else if (selecting && !event.LeftIsPressed())
	{
		selecting = false;
		setValue(event.GetPosX());
		manager->setFocus(parent);
	}

	return true;
}

int Slider::getValue() const
{
	float currentValue = iRect.center().x + 0.0f;
	float right = track.right() + 0.0f;
	float left = track.left() + 0.0f;

	float ret = ((currentValue - left)
		/ (right - left)) * 100;

	return static_cast<int>(ret);
}

float Slider::getRatio() const
{
	float currentValue = iRect.center().x + 0.0f;
	float right = track.right() + 0.0f;
	float left = track.left() + 0.0f;

	return ((currentValue - left) / (right - left));
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