#include "Panel.h"

Panel::Panel()
	:
	visualRect(Rect(0,0, DEFAULT_SIZE, DEFAULT_SIZE))
{}
Panel::Panel(Rect& rect)
{
	assert(rect.x() >= 0 && rect.x() < Graphics::ScreenWidth);
	assert(rect.y() >= 0 && rect.y() < Graphics::ScreenHeight);
	assert(rect.width() >= 0);
	assert(rect.height() >= 0);

	visualRect = rect;
}
Panel::Panel(int x, int y, int width, int height)
	:
	visualRect(Rect(x, y, width, height))
{}

void Panel::update()
{
	
}

void Panel::draw(Graphics& gfx) const
{
	if (!drawPanel)
		return;

	if (drawBorder)
		gfx.drawRect(visualRect, color, borderColor, borderSize);
	else
		gfx.drawRect(visualRect, color);
}

std::string Panel::getDebugInfo() const
{
	std::string s = "Panel: \n -";
	s.append(visualRect.toString());

	return s;
}
