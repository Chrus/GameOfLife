#pragma once
#include "Board.h"
#include "EditExpander.h"
#include "BrushExpander.h"
#include "SpeedExpander.h"


class ShortcutManager
{
public:
	//Constructors
	ShortcutManager();

	//Getters/Setters
	void setBoard(Board& board) { this->board = &board; }
	void setEditExpander(EditExpander* edit) { editPanel = edit; }
	void setPlayPanel(PlayPanel* playPanel) { this->playPanel = playPanel; }
	void setBrushExpander(BrushExpander* brushExpander) { this->brushExpander = brushExpander; }
	void setSpeedExpander(SpeedExpander* speedExpander) { this->speedExpander = speedExpander; }

	//Functions
	bool checkKey(const char key);
	std::vector<std::string> getKeys() const;
	void handleMouseWheel(Mouse::Event e);

private:
	//Variables
	Board* board;
	EditExpander* editPanel;
	PlayPanel* playPanel;
	BrushExpander* brushExpander;
	SpeedExpander* speedExpander;
	std::vector<std::string> keys;

	//Functions
	void fill() const;
	void clear() const;
	void reset() const;
	void play() const;
	void step() const;
	void selectBrush(const char key) const;
	void togglePreview() const;
	void save() const;
	void load() const;
	void undo() const;
};

