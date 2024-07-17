#pragma once
#include "Board.h"
#include "EditExpander.h"


class ShortcutManager
{
public:
	//Constructors
	ShortcutManager(Board* board, EditExpander* editPanel, PlayPanel* playPanel);
	ShortcutManager() {};

	bool checkKey(const char key);
	std::vector<std::string> getKeys() const;

private:
	//Variables
	Board* board;
	EditExpander* editPanel;
	PlayPanel* playPanel;
	std::vector<std::string> keys;

	//Functions
	void fill() const;
	void clear() const;
	void play() const;
	void step() const;
};

