#pragma once
#include "Container.h"
#include "Cell.h"
#include "PlayPanel.h"
#include "set"
#include "BrushManager.h"

class Board : public Container
{
public:
	//Constructors
	Board(Rect rect, Container* parent);
	~Board();

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	void update() override;
	void draw(Graphics& gfx) const override;

	//Inherited via Container
	void setContents() override;

	//Inherited via InputHandler
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;
	bool checkFocus(const Mouse::Event event, const LRHeld held) const override;
	void loseFocus() override;

	//Functions
	void init(PlayPanel* play, BrushManager* brushManager)
	{
		playPanel = play; 
		brushes = brushManager;
	}
	int getCellCount() const;
	Cell* getCell(const int xPos, const int yPos);
	Cell* getCell(const Tuple position);
	Cell* getCell(const int position);
	Cell* cellAtMouse(const Tuple mousePosition);
	void setAllCells(bool alive);
	int tupToIndex(const Tuple arrayPosition) const;

private:
	Tuple numCells;
	PlayPanel* playPanel;
	BrushManager* brushes;
	Cell* lastCellUpdated = nullptr;
	std::set<int> selectedCells;

	//Functions
	void initCellArray(const int xCount,const int yCount);
	Tuple correctBorderCells(int x, int y) const;
};

