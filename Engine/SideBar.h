#pragma once
#include "Container.h"
#include "Board.h"
#include "EditExpander.h"

class ShortcutsExpander;
class BrushExpander;
class SpeedExpander;
class ShortcutManager;

class SideBar : public Container
{
public:
	//Constructors
	SideBar(Rect rect, Container* parent, Board& board);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Functions
	void init(ShortcutManager* shortcutManager, BrushManager* brushManager);
	PlayPanel* getPlayPanel() { return play; }
	EditExpander* getEditExpander() { return edit; }

protected:
	//Inherited via Container
	void setContents() override;

private:
	Board& board;

	PlayPanel* play;
	SpeedExpander* speed;
	BrushExpander* brush;
	EditExpander* edit;
	ShortcutsExpander* shortcuts;
};

