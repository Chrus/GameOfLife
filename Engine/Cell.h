#pragma once
#include "ActionPanel.h"

class Cell: public ActionPanel
{
public:
	static constexpr int DEFAULT_SIZE = 25;

	Cell(Tuple position, Tuple arrayPos);
	
	//Inherited via Panel
	void update() override;

	//Inherited via ActionPanel
	void handleEvent(const InputHandler::Event event, InputManager* manager) override;

	//Functions
	void setNeighbors(std::vector<Cell*> newNeighbors);
	void updateState();

private:
	bool alive = false;
	bool switchState = false;
	Tuple arrayPos;
	std::vector<Cell*> neighbors;

	// Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void draw(Graphics& gfx) const override;
};