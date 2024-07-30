#pragma once

#include "Tuple.h"

class Rect
{
public:

	//Constructors
	Rect();
	Rect(int x, int y, int width, int height);
	Rect(Tuple position, Tuple size);

	//Operators
	bool Rect::operator==(const Rect& other) const
	{
		return other.position == position &&
			other.size == size;
	}

	//Qol Getters
	int Rect::x() const { return position.x; }
	int Rect::y() const { return position.y; }
	int Rect::width() const { return size.x; }
	int Rect::height() const { return size.y; }
	int Rect::left() const { return position.x; }
	int Rect::right() const { return position.x + size.x; }
	int Rect::top() const { return position.y; }
	int Rect::bottom() const { return position.y + size.y; }
	Tuple Rect::center() const
	{
		return Tuple(position.x + (width() / 2),
			position.y + (height() / 2));
	}

	//Functions
	void Rect::moveBy(const Tuple& amount);
	void Rect::moveBy(const int xAmount, const int yAmount);
	void Rect::reSize(const Tuple& amount);
	void Rect::reSize(const int widthAmount, const int heightAmount);
	Rect getExpanded(const int offset) const;
	Rect centerInside(const Rect& smallerRect) const;
	bool Rect::overlaps(const Rect& other) const;
	bool Rect::contains(const Rect& other) const;
	bool Rect::contains(const Tuple& point) const;
	std::string toString() const;

	//Variables
	Tuple position;
	Tuple size;
};

