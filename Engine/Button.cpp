#include "Button.h"

Button::Button()
	:
	ActionPanel(Rect()),
	parent(nullptr)
{
	color = Colors::LightGray;
	borderColor = Colors::Black;
	drawBorder = true;
	drawBackground = true;
}

//Button with no sprite or text
Button::Button(Rect rect, Container& parent)
	:
	ActionPanel(rect),
	parent(&parent)
{
	color = Colors::LightGray;
	borderColor = Colors::Black;
	drawBorder = true;
	drawBackground = true;
}

//Button with a sprite
Button::Button(Rect rect, std::string fileName, Container& parent)
	:
	Button(rect, parent)
{
	sprite = new SpritePanel(fileName, rect);
}

//Button with text
Button::Button(Rect rect, std::string fileName, std::string text, Container& parent)
	:
	Button(rect, parent)
{
	sprite = new TextPanel(fileName, rect, text);
}

Button::~Button()
{
	if (sprite != nullptr)
		delete sprite;
}

void Button::draw(Graphics & gfx) const
{
	ActionPanel::draw(gfx);

	if (sprite != nullptr)
		sprite->draw(gfx);
	else
		drawCustom(gfx);
}
