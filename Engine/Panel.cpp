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

void Panel::draw(Graphics& gfx) const
{
	if (!drawPanel)
		return;

	if (drawBackground)
		gfx.drawRect(visualRect, color);
	if (drawBorder)
		gfx.drawBorder(visualRect, color, borderColor, borderSize);
}
