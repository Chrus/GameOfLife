#pragma once
#include <functional>
#include "Board.h"
#include "ControlsExpander.h"

class ShortcutManager
{
public:
	//Constructors
	ShortcutManager(Board* board, ControlsExpander* controls, PlayPanel* playPanel);

	bool checkKey(const char key);

private:
	//Variables
	Board* board;
	ControlsExpander* controls;
	PlayPanel* playPanel;
	std::vector<char> keys;

	//Functions
	void fill() const;
	void clear() const;
	void play() const;
	void step() const;
};

