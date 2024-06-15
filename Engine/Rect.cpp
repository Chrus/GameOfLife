#include "Rect.h"

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

bool Rect::overlaps(const Rect& other) const
{
	return  
		Right() > other.Left() &&
		Left() < other.Right() &&
		Bottom() > other.Top() &&
		Top() < other.Bottom();
}
bool Rect::contains(const Rect&  constother) const
{
	return
		Left() <= other.Left() &&
		Right() >= other.Right() &&
		Top() <= other.Top() &&
		Bottom() >= other.Bottom();
}
bool Rect::contains(const Tuple& point) const
{
	return
		point.x >= Left() &&
		point.x <= Right() &&
		point.y >= Top() &&
		point.y <= Bottom();
}

void Rect::setPosition(const Tuple& newPosition)
{
	position = newPosition;
}
void Rect::setPosition(const int x, const int y)
{
	position.x = x;
	position.y = y;
}
void Rect::moveBy(const Tuple& amount)
{
	position += amount;
}
void Rect::moveBy(const int xAmount, const int yAmount)
{
	position.x += xAmount;
	position.y += yAmount;
}

void Rect::setSize(const Tuple& newSize)
{
	size = newSize;
}
void Rect::setSize(const int width, const int height)
{
	size.x = width;
	size.y = height;
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
