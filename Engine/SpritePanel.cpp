#include "SpritePanel.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>
#include <algorithm>

SpritePanel::SpritePanel(const std::string& filename, const Tuple location)
{
	visualRect.position = location;

	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	const bool is32b = bmInfoHeader.biBitCount == 32;

	visualRect.size.x = bmInfoHeader.biWidth;

	// test for reverse row order and control
	// y loop accordingly
	int yStart;
	int yEnd;
	int dy;
	if (bmInfoHeader.biHeight < 0)
	{
		visualRect.size.y = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = visualRect.height();
		dy = 1;
	}
	else
	{
		visualRect.size.y = bmInfoHeader.biHeight;
		yStart = visualRect.height() - 1;
		yEnd = -1;
		dy = -1;
	}

	pixels.resize(visualRect.width() * visualRect.height());

	file.seekg(bmFileHeader.bfOffBits);
	// padding is for the case of of 24 bit depth only
	const int padding = (4 - (visualRect.width() * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < visualRect.width(); x++)
		{
			PutPixel(x, y, Color(file.get(), file.get(), file.get()));
			if (is32b)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

std::string SpritePanel::getDebugInfo() const
{
	return std::string();
}

void SpritePanel::draw(Graphics& gfx) const
{
	gfx.drawSprite(visualRect, pixels.data());
}

void SpritePanel::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < visualRect.width());
	assert(y >= 0);
	assert(y < visualRect.height());
	pixels.data()[y * visualRect.width() + x] = c;
}