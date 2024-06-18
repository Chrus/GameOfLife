#include "Tuple.h"

//Constructors
Tuple::Tuple()
	:
	x(0),
	y(0)
{}
Tuple::Tuple(int x, int y)
	:
	x(x),
	y(y)
{
}

std::string Tuple::toString() const
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}