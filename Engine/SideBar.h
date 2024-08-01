#pragma once
#include "Container.h"
#include "Board.h"
#include "EditExpander.h"

class ShortcutsExpander;
class BrushExpander;

class SideBar : public Container
{
public:
	//Constructors
	SideBar(Rect rect, Container* parent, Board& board);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Functions
	void init(std::vector<std::string> shortcutsText, BrushManager* manager);
	PlayPanel* getPlayPanel() { return play; }
	EditExpander* getEditExpander() { return edit; }

protected:
	//Inherited via Container
	void setContents() override;

private:
	Board& board;

	PlayPanel* play;
	BrushExpander* brush;
	EditExpander* edit;
	ShortcutsExpander* shortcuts;
};

