#pragma once
#include "SpritePanel.h"
#include "Rect.h"

class TextPanel : public SpritePanel
{
public:
	//Statics
	static constexpr char TEXT_SPRITE[] = "Images\\Fixedsys16x28.bmp";
	static constexpr int GLYPH_WIDTH = 16;
	static constexpr int GLYPH_HEIGHT = 28;


	TextPanel(Rect& panelRect, std::string text);

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