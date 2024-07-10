#include "Button.h"

Button::Button(Rect rect, std::string buttonText)
	:
	ActionPanel(rect),
	text(rect, buttonText)
{}

void Button::draw(Graphics & gfx) const
{
	ActionPanel::draw(gfx);

	text.draw(gfx);
}
