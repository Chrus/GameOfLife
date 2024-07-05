#pragma once
#include "Container.h"
#include "TextPanel.h"

//TODO remove?
#include "Cell.h"

class MasterUIPanel: public Container
{
public:
	MasterUIPanel();

	// Inherited via InputHandler
	ActionPanel* handleEvent(InputHandler::Event event) override;
	bool checkFocus(InputHandler::Event event) const override;
	void loseFocus() override;

	//inherited via Panel
	void getDebugInfo(std::vector<DebugInfo>* info) const override;

	//Inherited via Container
	void setContents() override;

private:
	Cell c1 = Cell(Tuple(50, 50));
	Cell c2 = Cell(Tuple(65, 50));
	Cell c3 = Cell(Tuple(80, 50));
	Cell c4 = Cell(Tuple(95, 50));
	Cell c5 = Cell(Tuple(110, 50));
	//SpritePanel sprite1 = SpritePanel("Images\\Fixedsys16x28.bmp", Rect(0,0,600,250));
	//SpritePanel sprite2 = SpritePanel("Images\\TestSprite.bmp", Tuple(212, 350));
	TextPanel text1 = TextPanel("Images\\Fixedsys16x28.bmp", Rect(10, 10, 600, 200), Tuple(16, 28), "t\ne\ns\nt");
};

