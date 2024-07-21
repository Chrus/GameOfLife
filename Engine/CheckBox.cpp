#include "CheckBox.h"

CheckBox::CheckBox()
	:
	Button()
{}

CheckBox::CheckBox(Rect rect, Container& parent)
	:
	Button(rect, parent)
{}

CheckBox::CheckBox(Rect rect, std::string fileName, std::string checkedFileName, Container& parent)
	:
	Button(rect,fileName,parent)
{
	checkedSprite = new SpritePanel(checkedFileName, rect);
}

CheckBox::~CheckBox()
{
	delete checkedSprite;
}

void CheckBox::draw(Graphics& gfx) const
{
	ActionPanel::draw(gfx);

	if (sprite != nullptr && checkedSprite != nullptr)
	{
		if (!checked)
			sprite->draw(gfx);
		else
			checkedSprite->draw(gfx);
	}
	else
		drawCustom(gfx);
}

bool CheckBox::handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager)
{
	if (event.GetType() == Mouse::Event::Type::LPress && !held.first)
		checked = !checked;

	return true;
}

void CheckBox::drawCustom(Graphics& gfx) const
{
	if (checked)
	{
		int padding = std::min(iRect.width(), iRect.height()) / 4;
		gfx.drawRect(iRect.getExpanded(padding * -1), Colors::Black);
	}
}
