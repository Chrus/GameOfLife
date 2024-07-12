#pragma once
#include "Rect.h"
#include "Colors.h"
#include "Graphics.h"
#include "assert.h"
#include <vector>

using DebugInfo = std::pair<std::string, std::string>;

class Panel
{
public:
	//Default Values
	static constexpr int DEFAULT_BORDER_SIZE = 3;
	static constexpr Color DEFAULT_COLOR = Colors::BackgroundBlue;
	static constexpr Color DEFAULT_BORDER_COLOR = Colors::BorderBlue;
	static constexpr int DEFAULT_SIZE = 15;

	//Constructors
	Panel();
	Panel(Rect rect);
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
	int getBorderSize() const { return borderSize; }
	void setBorderSize(int newSize)
	{
		assert(newSize < visualRect.width());
		assert(newSize < visualRect.height());

		borderSize = newSize;
	}

	//Variables
	bool drawBorder = false;
	bool drawPanel = true;
	bool drawBackground = false;
	Color color = DEFAULT_COLOR;
	Color borderColor = DEFAULT_BORDER_COLOR;

	//Functions
	virtual void Panel::update() {};
	virtual void Panel::draw(Graphics& gfx) const;
	virtual DebugInfo Panel::getDebugInfo() const = 0;

protected:
	//Variables
	int borderSize = DEFAULT_BORDER_SIZE;
	//the entire space this panel takes up.
	Rect visualRect;
};

