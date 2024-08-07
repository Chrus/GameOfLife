#pragma once
#include "Panel.h"
#include "Colors.h"
#include <string>
#include <vector>
#include "Rect.h"

class SpritePanel : public Panel
{
public:
	//Constructors
	SpritePanel(const std::string& filename, Rect& panelRect);
	SpritePanel(const SpritePanel&) = default;
	SpritePanel() = default;

	//Getters/Setters
	void setChroma(Color color) { chroma = color; }

	// Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void draw(Graphics& gfx) const override;

protected:
	std::vector<Color> pixels;
	Color chroma = Colors::Magenta;
	Rect spriteRect = Rect();

	//Functions
	void PutPixel(int x, int y, Color c);
};