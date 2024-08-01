#include "ShortcutManager.h"
#include "PlayPanel.h"

ShortcutManager::ShortcutManager(Board* board, EditExpander* editPanel, PlayPanel* playPanel)
	:
	board(board),
	editPanel(editPanel),
	playPanel(playPanel)
{
	keys.push_back(std::string("C: Clear"));//clear
	keys.push_back(std::string("F: Fill"));//fill
	keys.push_back(std::string("Enter: Step"));//step
	keys.push_back(std::string("Space: Play/Stop"));//play/stop
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

std::vector<std::string> ShortcutManager::getKeys() const
{
	return keys;
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
