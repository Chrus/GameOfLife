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
	SpritePanel(const std::string& filename, const Tuple location);
	SpritePanel(const SpritePanel&) = default;
	SpritePanel() = default;

	// Inherited via Panel
	std::string getDebugInfo() const override;
	void draw(Graphics& gfx) const override;

protected:
	std::vector<Color> pixels;
	void PutPixel(int x, int y, Color c);
};