#include "set"
#include "Tuple.h"
#include "Rect.h"
#include <assert.h>

class BrushManager;
class Graphics;

#pragma once
class Brush
{
public:
	//Constructors
	Brush() = default;

	//Functions
	virtual std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) = 0;
	virtual std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager)
	{
		std::set<int> ret;
		std::set<int> newCells = previewBrush(start, canvasSize, manager);

		for (int x : newCells)
		{
			if (selected.insert(x).second == true)
				ret.insert(x);
		}

		return ret;
	}
	virtual void drawThumbnail(Graphics& gfx, const Rect area) const = 0;
	void endSelection() { selected.clear(); }

	//Variables
	int maxSize = 20;

protected:
	//Variables
	std::set<int> selected;
	
	//Functions
	int tupToIndex(const Tuple pos, const Tuple canvas) const
	{
		int cellIndex = pos.y * canvas.x + pos.x;
		assert(cellIndex < canvas.x * canvas.y);

		return cellIndex;
	}
	Tuple fixWrapping(const Tuple pos, const Tuple canvas) const
	{
		Tuple ret = pos;
		if (pos.x < 0)
			ret.x += canvas.x;
		else if (pos.x >= canvas.x)
			ret.x -= canvas.x;

		if (pos.y < 0)
			ret.y += canvas.y;
		else if (pos.y >= canvas.y)
			ret.y -= canvas.y;

		return ret;
	}
};