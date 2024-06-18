#pragma once

#include "Rect.h"
#include "Colors.h"
#include "Graphics.h"
#include "assert.h"
#include <string>

class Panel
{
public:
	//Default Values
	static constexpr int DEFAULT_BORDER_SIZE = 5;
	static constexpr Color DEFAULT_COLOR = Colors::LightGray;
	static constexpr Color DEFAULT_BORDER_COLOR = Colors::Gray;
	static constexpr int DEFAULT_SIZE = 15;

	//Constructors
	Panel();
	Panel(Rect& rect);
	Panel(int x, int y, int width, int height);

	//Getter/Setters
	const Rect& getVisualRect() { return visualRect; }
	void setPosition(Tuple newPosition) { visualRect.position = newPosition; }
	void setSize(Tuple newSize)
	{
		assert(newSize.x > 0);
		assert(newSize.y > 0);

		visualRect.size = newSize;
	}
	const int getBorderSize() { return borderSize; }
	void setBorderSize(int newSize)
	{
		assert(newSize < visualRect.width());
		assert(newSize < visualRect.height());

		borderSize = newSize;
	}

	//Variables
	bool drawBorder = true;
	bool drawPanel = true;
	Color color = DEFAULT_COLOR;
	Color borderColor = DEFAULT_BORDER_COLOR;

	//Functions
	void Panel::update();
	void Panel::draw(Graphics& gfx) const;
	virtual std::string Panel::getDebugInfo() const;

protected:
	//Variables
	int borderSize = DEFAULT_BORDER_SIZE;
	//the entire space this panel takes up.
	Rect visualRect;
};

