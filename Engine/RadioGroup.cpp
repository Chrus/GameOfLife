#include "RadioGroup.h"

RadioGroup::RadioGroup(Rect rect, Container* parent, int columnSize)
	:
	Container(rect, parent),
	columnSize(columnSize)
{}

void RadioGroup::select(CheckBox* button)
{
	if (selected == nullptr)
	{
		selected = button;
		button->checked = true;
	}
	else
	{
		selected->checked = false;
		selected = button;
		button->checked = true;
	}
}

void RadioGroup::addButton(CheckBox* newButton)
{
	int padding = 5;
	int size = (visualRect.width() / columnSize) - padding;

	Tuple pos = Tuple(
		visualRect.x() + (size * (buttonCount % columnSize)) + padding,
		visualRect.y() + (size * (buttonCount / columnSize)) + padding);

	newButton->setPosition(pos);
	newButton->setSize(Tuple(size, size));
	newButton->setIRect(Rect(pos.x, pos.y, size, size));

	contents.push_back(newButton);
	buttonCount++;
}
