#include "Brush.h"
#include "vector"
#include <random>
#include "Graphics.h"

#pragma once
class BrushManager
{
public:
	//Constructors
	BrushManager();
	~BrushManager();

	//Functions
	std::set<int> applyBrush(const Tuple start, const Tuple canvasSize);
	bool applyRandomness() const;
	void endSelection() { currentBrush->endSelection(); }

	//Getters/Setters
	void setBrush(int selection)
	{
		assert(selection >= 0 && selection < brushes.size());
		currentBrush = dynamic_cast<Brush*>(brushes[selection]);
	}
	Brush* getBrush(int selection) 
	{
		assert(selection >= 0 && selection < brushes.size());
		return brushes[selection]; 
	}
	void setSize(const float ratio) { sizeRatio = ratio; }
	int getSize(const int maxSize) const
	{
		return static_cast<int>(sizeRatio * maxSize);
	}
	void setRandomness(const float ratio) { randomRatio = ratio; }
	int getRandomness(const int maxValue) const
	{
		return static_cast<int>(randomRatio * maxValue);
	}
	void setFill(const bool fill) { this->fill = fill; }
	bool getFill() const { return fill; }

private:
	Brush* currentBrush = nullptr;
	std::vector<Brush*> brushes;

	float sizeRatio = 0.0f;
	float randomRatio = 0.0f;
	bool fill = true;

	class SquareBrush : public Brush
	{
	public:
		// Inherited via Brush
		std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);

			std::set<int> ret;

			for (int x = 0 - (size / 2); x < std::max(1,size / 2); x++)
			{
				for (int y = 0 - (size / 2); y < std::max(1, size / 2); y++)
				{
					Tuple pos = { start.x + x, start.y + y };
					pos = fixWrapping(pos, canvasSize);
					int index = tupToIndex(pos, canvasSize);

					if (selected.insert(index).second == true)
						ret.insert(index);
				}
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			gfx.drawRect(area.getExpanded(area.width() / 4 * -1), Colors::Black);
		}
	};
	class CircleBrush : public Brush
	{
		// Inherited via Brush
		std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int radius = manager->getSize(maxSize) / 2;
			std::set<int> ret;

			for (int x = start.x - radius; x < start.x + radius; x++)
			{
				for (int y = start.y - radius; y < start.y + radius; y++)
				{
					if (std::pow(x - start.x, 2) + std::pow(y - start.y, 2)
						< std::pow(radius, 2))
					{
						Tuple pos = { x, y };
						pos = fixWrapping(pos, canvasSize);
						int index = tupToIndex(pos, canvasSize);

						if (selected.insert(index).second == true)
							ret.insert(index);
					}
				}
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			Tuple center = area.center();
			int radius = area.width() / 5;

			for (int x = area.left(); x < area.right(); x++)
			{
				for (int y = area.top(); y < area.bottom(); y++)
				{
					if (std::pow(x - center.x, 2) + std::pow(y - center.y, 2)
						< std::pow(radius, 2))
						gfx.PutPixel(x, y, Colors::Black);
				}
			}
		}
	};
	class TriangleBrush : public Brush
	{
		// Inherited via Brush
		std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;

			//testing
			ret.insert(tupToIndex(Tuple(start.x, start.y - 1), canvasSize));

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			Tuple start = { area.center().x,area.top() + area.height() / 3 };

			int x = 1;
			for (int y = start.y; y < start.y + 10; y++)
			{
				gfx.drawRect(Rect(start.x - x, y, x * 2, 1), Colors::Black);
				x++;
			}
		}
	};
	class VerticalBrush : public Brush
	{
		// Inherited via Brush
		std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;

			for (int y = start.y - size / 2; y <= start.y + size / 2; y++)
			{
				Tuple pos = { start.x, y };
				pos = fixWrapping(pos, canvasSize);
				int index = tupToIndex(pos, canvasSize);

				if (selected.insert(index).second == true)
					ret.insert(index);
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			int width = area.width() / 6;
			int height = width * 4;
			Rect line = Rect(area.center().x - width / 2,
				area.center().y - height / 2,
				width, height);

			gfx.drawRect(line, Colors::Black);

			int boxHeight = height / 4;
			for (int y = 0; y <= 3; y++)
			{
				gfx.drawBorder(
					Rect(line.x(), line.y() + (boxHeight * y), width, boxHeight),
					Colors::BorderBlu, 1);
			}
		}
	};
	class HorizontalBrush : public Brush
	{
		// Inherited via Brush
		std::set<int> applyBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;

			for (int x = start.x - size / 2; x <= start.x + size / 2; x++)
			{
				Tuple pos = { x, start.y };
				pos = fixWrapping(pos, canvasSize);
				int index = tupToIndex(pos, canvasSize);

				if (selected.insert(index).second == true)
					ret.insert(index);
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			int height = area.width() / 6;
			int width = height * 4;
			Rect line = Rect(area.center().x - width / 2,
				area.center().y - height / 2,
				width, height);

			gfx.drawRect(line, Colors::Black);

			int boxWidth = width / 4;
			for (int x = 0; x <= 3; x++)
			{
				gfx.drawBorder(
					Rect(line.x() + (boxWidth * x), line.y(), boxWidth, height),
					Colors::BorderBlu, 1);
			}

		}
	};
};