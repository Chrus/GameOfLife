#include "BrushManager.h"

BrushManager::BrushManager()
{
	Brush* square = new SquareBrush();
	Brush* circle = new CircleBrush();
	Brush* triangle = new TriangleBrush();
	Brush* vert = new VerticalBrush();
	Brush* hor = new HorizontalBrush();

	brushes.push_back(square);
	brushes.push_back(circle);
	brushes.push_back(triangle);
	brushes.push_back(vert);
	brushes.push_back(hor);

	setBrush(0);
}

BrushManager::~BrushManager()
{
	for (Brush* brush : brushes)
		delete brush;
}

std::set<int> BrushManager::applyBrush(const Tuple start, const Tuple canvasSize)
{
	return currentBrush->applyBrush(start, canvasSize, this);
}

bool BrushManager::applyRandomness() const
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, 100);
	int random = xDist(rng);

	return random >= getRandomness(100);
}
