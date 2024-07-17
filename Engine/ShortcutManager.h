#pragma once
#include <functional>
#include "Board.h"
#include "ControlsExpander.h"

class ShortcutManager
{
public:
	//Constructors
	ShortcutManager(Board* board, EditExpander* controls, PlayPanel* playPanel);
	ShortcutManager() {};

	bool checkKey(const char key);

private:
	//Variables
	Board* board;
	EditExpander* controls;
	PlayPanel* playPanel;
	std::vector<char> keys;

	//Functions
	void fill() const;
	void clear() const;
	void play() const;
	void step() const;
};

