#pragma once
#include "ActionPanel.h"

class Cell: public ActionPanel
{
public:
	static constexpr int DEFAULT_SIZE = 25;

	Cell(Tuple position, Tuple arrayPos);
	
	//Inherited via Panel
	void update() override;
	DebugInfo getDebugInfo() const override;
	void draw(Graphics& gfx) const override;

	//Inherited via ActionPanel
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;

	//Functions
	void setNeighbors(std::vector<Cell*> newNeighbors);
	void updateState();
	void setAlive(bool cellAlive);
	bool getState() const { return alive; }
	Tuple arrayPosition() const { return arrayPos; }

private:
	bool alive = false;
	bool switchState = false;
	Tuple arrayPos;
	std::vector<Cell*> neighbors;
};