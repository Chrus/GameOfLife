#pragma once
#include "SpritePanel.h"
#include "Rect.h"

class TextPanel : public SpritePanel
{
public:
	TextPanel(const std::string& filename, Rect& panelRect,
		Tuple glyphSize, std::string text);

	//Inherited from Panel
	void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override;

	//Variables

	//Functions
	Rect mapGlyphRect(char c) const;
	void setText(const std::string newText);

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