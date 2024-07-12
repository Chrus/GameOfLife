#pragma once
#include "Container.h"
#include "TextPanel.h"
#include "ExpandablePanel.h"
#include "Board.h"
#include "ControlsPanel.h"

//TODO remove?
#include "Cell.h"

class MasterUIPanel: public Container
{
public:
	MasterUIPanel();

	//inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Inherited via Container
	void setContents() override;
	void updateDebugPanel(std::string text, bool display);

	//Functions


private:
	ControlsPanel controls = ControlsPanel(Rect(450, 200, 100, 50), this);
	Board board = Board(Rect(75, 0, Graphics::ScreenWidth - 76, Graphics::ScreenHeight - 1), this, &controls);
	TextPanel debugPanel = TextPanel(std::string(TextPanel::TEXT_SPRITE16X28),
		Rect(0, 0, Graphics::ScreenWidth - 1, Graphics::ScreenHeight - 1),
		" ");

	//Debugg/Testing code
	//Cell c1 = Cell(Tuple(50, 50));
	//Cell c2 = Cell(Tuple(65, 50));
	//Cell c3 = Cell(Tuple(80, 50));
	//Cell c4 = Cell(Tuple(95, 50));
	//Cell c5 = Cell(Tuple(110, 50));
	ExpandablePanel eP = ExpandablePanel(Rect(0, 0, 75, 1299),
		Rect(200, 200, 25, 25), this, "T\ne\nm\np");

};