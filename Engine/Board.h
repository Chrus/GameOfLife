#pragma once
#include "Container.h"
#include "Cell.h"
#include "ControlsPanel.h"

class Board : public Container
{
public:
	//Constructors
	Board(Rect rect, Container* parent, ControlsPanel* controls);
	~Board();

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void update() override;

	//Inherited via Container
	void setContents() override;

	//Functions
	int getCellCount() const;
	Cell* getCell(const int xPos, const int yPos);
	Cell* getCell(const Tuple position);

private:
	Tuple numCells;
	ControlsPanel* controls;		

	//Functions
	void initCellArray(const int xCount,const int yCount);
	Tuple correctBorderCells(int x, int y) const;
};

