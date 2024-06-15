#pragma once
struct Tuple
{
public:
	Tuple();
	Tuple(int x, int y);

	bool Tuple::operator==(const Tuple& other)
	{
		return other.x == x && other.y == y;
	}
	bool Tuple::operator!=(const Tuple& other)
	{
		return other.x != x || other.y != y;
	}
	void Tuple::operator+=(const Tuple& other)
	{
		x += other.x;
		y += other.y;
	}
	Tuple Tuple::operator+(const Tuple& right) const
	{
		return Tuple(x + right.x, y + right.y);
	}
	Tuple Tuple::operator*(int right) const
	{
		return Tuple(x * right, y * right);
	}

	int x;
	int y;
};

