#include "BrushRadioGroup.h"
#include "BrushExpander.h"

BrushRadioGroup::BrushRadioGroup(Rect rect, Container* parent, int columnSize)
	:
	RadioGroup(rect, parent, columnSize)
{
	setContents();
}

void BrushRadioGroup::setContents()
{
	BrushButton* brush1 = new BrushButton(Rect(), *this, 0);
	BrushButton* brush2 = new BrushButton(Rect(), *this, 1);
	BrushButton* brush3 = new BrushButton(Rect(), *this, 2);
	BrushButton* brush4 = new BrushButton(Rect(), *this, 3);
	BrushButton* brush5 = new BrushButton(Rect(), *this, 4);

	addButton(brush1); //square
	addButton(brush2); //circle
	addButton(brush3); //triange
	addButton(brush4); //vert
	addButton(brush5); //hor

	selected = brush1;
	brush1->checked = true;
}

void BrushRadioGroup::select(CheckBox* button)
{
	RadioGroup::select(button);

	BrushButton* b = dynamic_cast<BrushButton*>(button);
	dynamic_cast<BrushExpander*>(parent)->setBrushSelection(b->index);
}

void BrushRadioGroup::select(int index)
{
	CheckBox* button = dynamic_cast<CheckBox*>(contents[index]);
	select(button);
}
