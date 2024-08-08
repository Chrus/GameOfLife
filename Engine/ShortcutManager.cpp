#include "ShortcutManager.h"
#include "PlayPanel.h"

ShortcutManager::ShortcutManager()
{
	keys.push_back(std::string("L Click: Set Cell to Alive"));
	keys.push_back(std::string("R Click: Set Cell to Dead"));
	keys.push_back(std::string("Space: Play/Stop"));
	keys.push_back(std::string("Enter: Step"));
	keys.push_back(std::string("1-5: Select Brush")); 
	keys.push_back(std::string("MouseWheel: Change Brush Size"));
	keys.push_back(std::string("Tab: Toggle Brush Preview"));
	keys.push_back(std::string("C: Clear"));
	keys.push_back(std::string("R: Reset Board"));
	keys.push_back(std::string("F: Fill"));
	keys.push_back(std::string("S: Save Board State"));
	keys.push_back(std::string("L: Load Saved State"));
	keys.push_back(std::string("Z: Undo"));
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
	case 'r':
		reset();
		return true;
	case '\r':
		step();
		return true;
	case ' ':
		play();
		return true;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
		selectBrush(key);
		return true;
	case '\t':
		togglePreview();
		return true;
	case 's':
		save();
		return true;
	case 'l':
		load();
		return true;
	case 'z':
		undo();
		return true;
	}

	return false;
}

std::vector<std::string> ShortcutManager::getKeys() const
{
	return keys;
}

void ShortcutManager::handleMouseWheel(Mouse::Event e)
{
	if (e.GetType() == Mouse::Event::Type::WheelUp)
	{
		brushExpander->incBrushSize();
	}
	else if (e.GetType() == Mouse::Event::Type::WheelDown)
	{
		brushExpander->decBrushSize();
	}
}


void ShortcutManager::fill() const
{
	editPanel->fillButtonClick();
}

void ShortcutManager::clear() const
{
	editPanel->clearButtonClick();
}

void ShortcutManager::reset() const
{
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

void ShortcutManager::selectBrush(const char key) const
{
	int selection = key - '0' - 1;
	brushExpander->setBrushButton(selection);
}

void ShortcutManager::togglePreview() const
{
	brushExpander->togglePreview();
}

void ShortcutManager::save() const
{
	editPanel->saveButtonClick();
}

void ShortcutManager::load() const
{
	editPanel->loadButtonClick();
}

void ShortcutManager::undo() const
{
	editPanel->undoButtonClick();
}
