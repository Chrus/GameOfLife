#pragma once
#include "Container.h"
#include "Cell.h"
#include "PlayPanel.h"

class Board : public Container
{
public:
	//Constructors
	Board(Rect rect, Container* parent, PlayPanel* controls);
	~Board();

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void update() override;

	//Inherited via Container
	void setContents() override;

	//Inherited via InputHandler
	void handleEvent(const InputHandler::Event event, InputManager* manager) override;
	bool checkFocus(InputHandler::Event event) const override;
	void loseFocus() override;

	//Functions
	int getCellCount() const;
	Cell* getCell(const int xPos, const int yPos);
	Cell* getCell(const Tuple position);
	Cell* cellAtMouse(const Tuple mousePosition);
	void setAllCells(bool alive);

private:
	Tuple numCells;
	PlayPanel* playPanel;
	Cell* lastCellUpdated;

	//Functions
	void initCellArray(const int xCount,const int yCount);
	Tuple correctBorderCells(int x, int y) const;
};

