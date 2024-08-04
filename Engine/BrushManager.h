#include "Brush.h"
#include "vector"
#include <random>
#include "Graphics.h"
#include "Cell.h"

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

	//Variables
	bool preview = true;
	Brush* currentBrush = nullptr;

private:
	std::vector<Brush*> brushes;

	float sizeRatio = 0.0f;
	float randomRatio = 0.0f;
	bool fill = true;

	class SquareBrush : public Brush
	{
	public:
		SquareBrush()
		{
			maxSize = std::min(Graphics::ScreenHeight / Cell::DEFAULT_SIZE, Graphics::ScreenWidth / Cell::DEFAULT_SIZE) - 1;
		}
		// Inherited via Brush
		std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;
			
			int max = std::max(1, size / 2);
			if (size % 2 != 0 && size != 1) 
				max++;

			for (int x = 0 - (size / 2); x < max; x++)
			{
				for (int y = 0 - (size / 2); y < max; y++)
				{
					Tuple pos = { start.x + x, start.y + y };
					pos = fixWrapping(pos, canvasSize);
					int index = tupToIndex(pos, canvasSize);

					ret.insert(index);
				}
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			gfx.drawRect(area.getExpanded(area.width() / 4 * -1), Colors::Black);
		};
	};
	class CircleBrush : public Brush
	{
	public:
		CircleBrush()
		{
			maxSize = std::min(Graphics::ScreenHeight / Cell::DEFAULT_SIZE, Graphics::ScreenWidth / Cell::DEFAULT_SIZE) - 1;
		}
		// Inherited via Brush
		std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			std::set<int> ret;
			float size = std::max(1, manager->getSize(maxSize));

			if (size == 1)
			{
				ret.insert(tupToIndex({ start.x, start.y }, canvasSize));
				return ret;
			}

			float center = size / 2;

			for (int x = 0; x < size; x++)
			{
				for (int y = 0; y < size; y++)
				{
					float centerX = x + 0.5f;
					float centerY = y + 0.5f;

					float t1 = std::pow(std::abs(center - centerX), 2);
					float t2 = std::pow(std::abs(center - centerY), 2);
					float distance = std::sqrt(t1 + t2);

					if (distance <= size / 2)
					{
						int adjust = size / 2;
						Tuple pos = { start.x + x - adjust, start.y + y - adjust };
						pos = fixWrapping(pos, canvasSize);
						int index = tupToIndex(pos, canvasSize);

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
	public:
		TriangleBrush()
		{
			maxSize = std::min(Graphics::ScreenHeight / Cell::DEFAULT_SIZE, Graphics::ScreenWidth / Cell::DEFAULT_SIZE) - 1;
		}
		// Inherited via Brush
		std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = std::max(1, manager->getSize(maxSize));
			std::set<int> ret;
			float pi = 3.14159265358979323846;
			float angle = 180;
			angle *= (pi / 180.0f);

			Tuple v0 = { start.x,start.y };
			Tuple v1 = { static_cast<int>(start.x + size * std::cos(angle)),
				static_cast<int>(start.y + size * std::sin(angle)) };
			Tuple v2 = { static_cast<int>(start.x + size * std::cos(angle + pi / 3)),
				static_cast<int>(start.y + size * std::sin(angle + pi / 3)) };

			int minX = std::min({ v0.x, v1.x, v2.x });
			int maxX = std::max({ v0.x, v1.x, v2.x });
			int minY = std::min({ v0.y, v1.y, v2.y });
			int maxY = std::max({ v0.y, v1.y, v2.y });

			for (int x = minX; x < maxX; x++)
			{
				for (int y = minY; y < maxY; y++)
				{
					Tuple pos = { x,y };
					if (isPointInTriangle(pos, v0, v1, v2))
					{
						pos = pos + Tuple{ size / 2,size / 2 };
						pos = fixWrapping(pos, canvasSize);
						int index = tupToIndex(pos, canvasSize);
						ret.insert(index);
					}
				}
			}

			return ret;
		}
		void drawThumbnail(Graphics& gfx, const Rect area) const override
		{
			Tuple start = { area.center().x,area.top() + 20 };

			int x = 1;
			for (int y = start.y; y < start.y + 30; y +=2)
			{
				gfx.drawRect(Rect(start.x - x, y, x * 2, 1), Colors::Black);
				x++;
			}
		}

		bool isPointInTriangle(const Tuple& pt, const Tuple& v0, const Tuple& v1, const Tuple& v2) 
		{
			// Barycentric coordinates method
			float denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
			float a = ((v1.y - v2.y) * (pt.x - v2.x) + (v2.x - v1.x) * (pt.y - v2.y)) / denom;
			float b = ((v2.y - v0.y) * (pt.x - v2.x) + (v0.x - v2.x) * (pt.y - v2.y)) / denom;
			float c = 1.0f - a - b;
			return a >= 0 && b >= 0 && c >= 0;
		}
	};
	class VerticalBrush : public Brush
	{
	public:
		VerticalBrush()
		{
			maxSize = Graphics::ScreenHeight / Cell::DEFAULT_SIZE - 1;
		}
		// Inherited via Brush
		std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;

			int max = std::max(1, size / 2);
			if (size % 2 != 0 && size != 1)
				max++;

			for (int y = 0 - (size / 2); y < max; y++)
			{
				Tuple pos = { start.x, start.y + y};
				pos = fixWrapping(pos, canvasSize);
				int index = tupToIndex(pos, canvasSize);

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
	public:
		HorizontalBrush()
		{
			maxSize = Graphics::ScreenWidth / Cell::DEFAULT_SIZE - 1;
		}
		// Inherited via Brush
		std::set<int> previewBrush(const Tuple start, const Tuple canvasSize, const BrushManager* manager) override
		{
			int size = manager->getSize(maxSize);
			std::set<int> ret;

			int max = std::max(1, size / 2);
			if (size % 2 != 0 && size != 1)
				max++;

			for (int x = 0 - (size / 2); x < max; x++)
			{
				Tuple pos = { start.x + x, start.y };
				pos = fixWrapping(pos, canvasSize);
				int index = tupToIndex(pos, canvasSize);

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