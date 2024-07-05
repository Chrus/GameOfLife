#include "SpritePanel.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>
#include <algorithm>

SpritePanel::SpritePanel(const std::string& filename, Rect& panelRect)
	:
	Panel(panelRect)
{
	spriteRect.position = { 0,0 };

	//just draw the sprite by default
	drawBorder = false;
	drawBackground = false;

	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHeader;
	file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

	BITMAPINFOHEADER bmInfoHeader;
	file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

	assert(bmInfoHeader.biBitCount == 24 || bmInfoHeader.biBitCount == 32);
	assert(bmInfoHeader.biCompression == BI_RGB);

	const bool is32b = bmInfoHeader.biBitCount == 32;

	spriteRect.size.x = bmInfoHeader.biWidth;

	// test for reverse row order and control
	// y loop accordingly
	int yStart;
	int yEnd;
	int dy;
	if (bmInfoHeader.biHeight < 0)
	{
		spriteRect.size.y = -bmInfoHeader.biHeight;
		yStart = 0;
		yEnd = spriteRect.height();
		dy = 1;
	}
	else
	{
		spriteRect.size.y = bmInfoHeader.biHeight;
		yStart = spriteRect.height() - 1;
		yEnd = -1;
		dy = -1;
	}

	pixels.resize(spriteRect.width() * spriteRect.height());

	file.seekg(bmFileHeader.bfOffBits);
	// padding is for the case of of 24 bit depth only
	const int padding = (4 - (spriteRect.width() * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dy)
	{
		for (int x = 0; x < spriteRect.width(); x++)
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

void SpritePanel::getDebugInfo(std::vector<DebugInfo>* info) const
{
	info->push_back(std::make_pair("SpritePanel", ""));
}

void SpritePanel::draw(Graphics& gfx) const
{
	if (!drawPanel)
		return;
	Panel::draw(gfx);

	gfx.drawSprite(visualRect.centerInside(spriteRect), pixels.data(), chroma);
}

void SpritePanel::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < spriteRect.width());
	assert(y >= 0);
	assert(y < spriteRect.height());
	pixels.data()[y * spriteRect.width() + x] = c;
}