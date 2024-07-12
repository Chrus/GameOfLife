#pragma once
#include "SpritePanel.h"
#include "Rect.h"

class TextPanel : public SpritePanel
{
public:
	//Statics
	static constexpr char TEXT_SPRITE16X28[] = "Images\\Fixedsys16x28.bmp";
	static constexpr char TEXT_SPRITE8X14[] = "Images\\Fixedsys8x14.bmp";

	TextPanel(std::string fileName, Rect& panelRect, std::string text);

	//Inherited from Panel
	void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override;

	//Variables

	//Functions
	Rect mapGlyphRect(char c) const;
	void setText(const std::string newText);
	std::string getText() const { return text; }

private:
	//Statics
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
	static constexpr int numCol = 32;
	static constexpr int numRow = 3;

	//Functions
	Rect calcTextRect() const;

	//Variables
	Tuple glyphSize;
	std::string text;
	Rect textRect;
};