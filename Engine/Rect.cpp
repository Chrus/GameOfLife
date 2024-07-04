#include "Rect.h"
#include <assert.h>

//Constructors
Rect::Rect()
	:
	position(Tuple()),
	size(Tuple())
{}
Rect::Rect(int x, int y, int width, int height)
	:
	position(Tuple(x,y)),
	size(Tuple(width,height))
{}
Rect::Rect(Tuple position, Tuple size)
	:
	position(position),
	size(size)
{}

void Rect::moveBy(const Tuple& amount)
{
	position += amount;
}
void Rect::moveBy(const int xAmount, const int yAmount)
{
	position.x += xAmount;
	position.y += yAmount;
}
void Rect::reSize(const Tuple& amount)
{
	size += amount;
}
void Rect::reSize(const int widthAmount, const int heightAmount)
{
	size.x += widthAmount;
	size.y += heightAmount;
}

Rect Rect::getExpanded(const int offset) const
{
	return Rect(left() - offset, top() - offset, width() + (offset * 2), height() + (offset * 2));
}

Rect Rect::centerInside(const Rect& smallerRect) const
{
	Rect drawRect = Rect(position.x,position.y,width(),height());

	//currnetly not handling clipping, throw an error if we are
	assert(smallerRect.width() < width());
	assert(smallerRect.height() < height());

	//Center the spritesheet if it is smaller than the Panel rect
	if (smallerRect.width() < width())
	{
		drawRect.size.x = smallerRect.width();
		drawRect.position.x += (width() / 2) - (smallerRect.width() / 2);
	}
	if (smallerRect.height() < height())
	{
		drawRect.size.y = smallerRect.height();
		drawRect.position.y += (height() / 2) - (smallerRect.height() / 2);
	}

	return drawRect;
}

bool Rect::overlaps(const Rect& other) const
{
	return
		right() > other.left() &&
		left() < other.right() &&
		bottom() > other.top() &&
		top() < other.bottom();
}
bool Rect::contains(const Rect& other) const
{
	return
		left() <= other.left() &&
		right() >= other.right() &&
		top() <= other.top() &&
		bottom() >= other.bottom();
}
bool Rect::contains(const Tuple& point) const
{
	return
		point.x >= left() &&
		point.x <= right() &&
		point.y >= top() &&
		point.y <= bottom();
}

std::string Rect::toString() const
{
	return "Position:" + position.toString()
		+ " | Size:" + size.toString();
}
