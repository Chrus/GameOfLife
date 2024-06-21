#pragma once
#include "Container.h"

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

	//Inherited via Container
	void setContents() override;

private:
	Cell c1 = Cell(Tuple(50, 50));
	Cell c2 = Cell(Tuple(65, 50));
	Cell c3 = Cell(Tuple(80, 50));
	Cell c4 = Cell(Tuple(95, 50));
	Cell c5 = Cell(Tuple(110, 50));
};

