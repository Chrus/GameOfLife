#include "ShortcutManager.h"

ShortcutManager::ShortcutManager(Board* board, EditExpander* editPanel, PlayPanel* playPanel)
	:
	board(board),
	editPanel(editPanel),
	playPanel(playPanel)
{
	//keys.push_back('c');//clear
	//keys.push_back('f');//fill
	//keys.push_back('\r');//step
	//keys.push_back(' ');//play/stop
}

bool ShortcutManager::checkKey(const char key)
{
	switch (key)
	{
	case 'c':
		clear();
		return true;
	case 'f':
		fill();
		return true;
	case '\r':
		step();
		return true;
	case ' ':
		play();
		return true;
	}

	return false;
}

void ShortcutManager::fill() const
{
	assert(board != nullptr);
	board->setAllCells(true);
}

void ShortcutManager::clear() const
{
	assert(board != nullptr);
	board->setAllCells(false);
}

void ShortcutManager::play() const
{
	assert(playPanel != nullptr);
	playPanel->playClick();
}

void ShortcutManager::step() const
{
	assert(playPanel != nullptr);
	playPanel->stepClick();
}
