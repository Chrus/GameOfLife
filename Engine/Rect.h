#pragma once

#include "Tuple.h"

class Rect
{
public:

	//Constructors
	Rect();
	Rect(int x, int y, int width, int height);
	Rect(Tuple position, Tuple size);

	//Getters
	int Rect::X() const { return position.x; }
	int Rect::Y() const { return position.y; }
	int Rect::Width() const { return size.x; }
	int Rect::Height() const { return size.y; }
	int Rect::Left() const { return X(); }
	int Rect::Right() const { return X() + Width(); }
	int Rect::Top() const { return Y(); }
	int Rect::Bottom() const { return Y() + Height(); }
	Tuple Rect::Position() const { return position; }
	Tuple Rect::Size() const { return size; }

	//Setters (position)
	void Rect::setPosition(const Tuple& newPosition);
	void Rect::setPosition(const int x, const int y);
	void Rect::moveBy(const Tuple& amount);
	void Rect::moveBy(const int xAmount, const int yAmount);
	//Setters (size)
	void Rect::setSize(const Tuple& newSize);
	void Rect::setSize(const int width, const int height);
	void Rect::reSize(const Tuple& amount);
	void Rect::reSize(const int widthAmount, const int heightAmount);

	//Comparisions
	bool Rect::overlaps(const Rect& other) const;
	bool Rect::contains(const Rect& other) const;
	bool Rect::contains(const Tuple& point) const;

private:
	//Variables
	Tuple position;
	Tuple size;
};

