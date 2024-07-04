#include "TextPanel.h"

TextPanel::TextPanel(const std::string& filename, Rect& panelRect,
	Tuple glyphSize, std::string text)
	:
	SpritePanel(filename, panelRect),
	glyphSize(glyphSize)
{
	setText(text);
}

void TextPanel::draw(Graphics& gfx) const
{
	if (!drawPanel)
		return;
	Panel::draw(gfx);

	Tuple curPos = textRect.position;
	for (char c : text)
	{
		if (c == '\n')
		{
			curPos.x = textRect.position.x;
			curPos.y += glyphSize.y;
			continue;
		}

		if (c >= firstChar + 1 && c <= lastChar)
		{
			gfx.drawChar(curPos, mapGlyphRect(c), spriteRect, pixels.data(), Colors::White);
		}
		curPos.x += glyphSize.x;
	}
}

void TextPanel::setText(const std::string newText)
{
	text = newText;
	textRect = calcTextRect();
}

//returns a rect to the position of c on the spritesheet
Rect TextPanel::mapGlyphRect(char c) const
{
	assert(c >= firstChar && c <= lastChar);

	const int glyphIndex = c - ' ';
	const int yGlyph = glyphIndex / numCol;
	const int xGlyph = glyphIndex % numCol;

	return Rect(xGlyph * glyphSize.x, yGlyph * glyphSize.y,
		glyphSize.x, glyphSize.y);
}

Rect TextPanel::calcTextRect() const
{
	assert(!text.empty());

	int maxWidth = 1;
	int maxHeight = 1;
	int currentWidth = 1;

	for (auto c : text)
	{
		if (c == '\n')
		{
			maxHeight++;
			currentWidth = 0;
		}
		else if (currentWidth > maxWidth)
			maxWidth++;

		currentWidth++;
	}

	Tuple drawRectSize = Tuple(maxWidth * glyphSize.x, maxHeight * glyphSize.y);

	assert(maxWidth * glyphSize.x < visualRect.width());
	assert(maxHeight * glyphSize.y < visualRect.height());

	return visualRect.centerInside(Rect({ 0,0 }, drawRectSize));
}
