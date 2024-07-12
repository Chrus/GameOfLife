#include "CheckBox.h"

CheckBox::CheckBox()
	:
	Button()
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

	if (!checked)
		sprite->draw(gfx);
	else
		checkedSprite->draw(gfx);
}
