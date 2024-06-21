#pragma once
#include "ActionPanel.h"

class Cell: public ActionPanel
{
public:
	static constexpr int DEFAULT_SIZE = 15;

	Cell(Tuple position);
	
	//Inherited via ActionPanel
	ActionPanel* handleEvent(InputHandler::Event event) override;
	bool checkFocus(InputHandler::Event event) const override;
	void loseFocus() override;

private:
	bool alive = false;

	// Inherited via Panel
	std::string getDebugInfo() const override;
	void draw(Graphics& gfx) const override;
};