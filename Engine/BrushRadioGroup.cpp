#include "BrushRadioGroup.h"

BrushRadioGroup::BrushRadioGroup(Rect rect, Container* parent, int columnSize)
	:
	RadioGroup(rect, parent, columnSize)
{
	setContents();
}

void BrushRadioGroup::setContents()
{
	BrushButton* brush1 = new BrushButton(Rect(), *this);
	BrushButton* brush2 = new BrushButton(Rect(), *this);
	BrushButton* brush3 = new BrushButton(Rect(), *this);
	BrushButton* brush4 = new BrushButton(Rect(), *this);
	BrushButton* brush5 = new BrushButton(Rect(), *this);

	addButton(brush1);
	addButton(brush2);
	addButton(brush3);
	addButton(brush4);
	addButton(brush5);

	select(brush1);
}
