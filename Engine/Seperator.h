#pragma once
#include "Panel.h"
class Seperator : public Panel
{
public:
	//Constructors
	Seperator() : Panel(0, 0, 10, 5) {}
	Seperator(const Tuple position, const int width, const int padding)
		:
		Panel(position.x, position.y, width, 2 + (padding*2))
	{
		drawBackground = true;
		borderSize = padding;
		color = Colors::BorderBlu;
	}

	// Inherited via Panel
	DebugInfo getDebugInfo() const override
	{
		return DebugInfo("Seperator", "");
	}

private:

};

