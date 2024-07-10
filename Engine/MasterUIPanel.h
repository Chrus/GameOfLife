#pragma once
#include "Container.h"
#include "TextPanel.h"
#include "ExpandablePanel.h"

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
	TextPanel debugPanel = TextPanel(Rect(0, 0, Graphics::ScreenWidth - 1, Graphics::ScreenHeight - 1), "");

	//Debugg/Testing code
	//Cell c1 = Cell(Tuple(50, 50));
	//Cell c2 = Cell(Tuple(65, 50));
	//Cell c3 = Cell(Tuple(80, 50));
	//Cell c4 = Cell(Tuple(95, 50));
	//Cell c5 = Cell(Tuple(110, 50));
	ExpandablePanel eP = ExpandablePanel(Rect(10, 10, 35, 100),
		Rect(200, 200, 50, 50), this, "T");

};