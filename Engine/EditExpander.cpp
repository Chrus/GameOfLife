#include "EditExpander.h"
#include "Seperator.h"
#include <random>

EditExpander::EditExpander(Rect expanderRect, Rect contentsRect, Container* parent, std::string text, Board& board)
	:
	ExpandablePanel(expanderRect, contentsRect, parent, text),
	board(board)
{
	setContents();
	savedCells = new bool[1];
	undoCells = new bool[1];
}

EditExpander::~EditExpander()
{
	delete[] savedCells;
}

DebugInfo EditExpander::getDebugInfo() const
{
	return DebugInfo("EditExpander", "");
}

void EditExpander::update()
{
	int randomness = randomSlider->getValue();
	if (lastSliderValue != randomness)
	{
		randomText->setText(std::string("Randomness: " + std::to_string(randomness) + "%"));
		lastSliderValue = randomness;
		updateButtonText();
	}
}

void EditExpander::updateButtonText()
{
	if (randomSlider->getValue() == 0)
	{
		clear->setText("Clear");
		fill->setText("Fill");
	}
	else
	{
		std::string clearText = "  Clear ";
		clearText.append(std::to_string(100 - randomSlider->getValue()) + "%\n");
		if (override->checked)
			clearText.append("of the Board ");
		else
			clearText.append("of Live Cells");

		std::string fillText = "  Fill ";
		fillText.append(std::to_string(100 - randomSlider->getValue()) + "%\n");
		if (override->checked)
			fillText.append("of the Board ");
		else
			fillText.append("of Dead Cells");
		
		fill->setText(fillText);
		clear->setText(clearText);
	}
}


void EditExpander::setContents()
{
	clear = new ClearButton(
		Rect(iRect.x() + 5, iRect.y() + 5, iRect.width() - 10, 45),
		std::string("Clear"), *this);

	fill = new FillButton(
		Rect(iRect.x() + 5, clear->getVisualRect().bottom() + 5, iRect.width() - 10, 45),
		std::string("Fill"), *this);

	randomText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(iRect.x(), fill->getVisualRect().bottom() + 5, iRect.width(), 20),
		"Randomness: 0%");

	randomSlider = new Slider(
		Rect(iRect.x() + 5, randomText->getVisualRect().bottom(), iRect.width() - 10, 10),
		this);
	randomSlider->setValue(0);

	override = new OverrideButton(
		Rect(iRect.x() + 5, randomSlider->getVisualRect().bottom() + 10, 20, 20),
		*this);
	override->checked = true;

	TextPanel* overrideText = new TextPanel(
		TextPanel::TEXT_SPRITE8X14,
		Rect(override->getVisualRect().right(), 
			override->getVisualRect().top(), 
			iRect.width() - override->getVisualRect().width() - 10, 
			override->getVisualRect().height()),
		std::string("Override Cells"));

	Seperator* seperator = new Seperator(Tuple(iRect.x(), override->getVisualRect().bottom() + 5), iRect.width(), 5);

	SaveButton* save = new SaveButton(
		Rect(iRect.x() + 5, seperator->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Save"), *this);

	load = new LoadButton(
		Rect(iRect.x() + 5, save->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Load"), *this);
	load->setState(false);

	undo = new UndoButton(
		Rect(iRect.x() + 5, load->getVisualRect().bottom() + 5, iRect.width() - 10, 30),
		std::string("Undo"), *this);
	undo->setState(false);

	contents.push_back(clear);
	contents.push_back(fill);
	contents.push_back(randomText);
	contents.push_back(randomSlider);
	contents.push_back(override);
	contents.push_back(overrideText);
	contents.push_back(seperator);
	contents.push_back(save);
	contents.push_back(load);
	contents.push_back(undo);
}

void EditExpander::clearButtonClick()
{
	//Dont need to do anything
	if (randomSlider->getValue() == 100)
		return;

	setUndoCells();

	if (randomSlider->getValue() == 0)
		board.setAllCells(false);
	else
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> xDist(0, 100);
		int random;
		int value = randomSlider->getValue();

		for (int x = 0; x < board.getCellCount(); x++)
		{
			random = xDist(rng);
			if (random > value)
				board.getCell(x)->setAlive(false);
			else if(override->checked)
				board.getCell(x)->setAlive(true);
		}
	}
}
void EditExpander::fillButtonClick()
{
	//Dont need to do anything
	if (randomSlider->getValue() == 100)
		return;

	setUndoCells();

	if (randomSlider->getValue() == 0)
		board.setAllCells(true);
	else
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution<int> xDist(0, 100);
		int random = xDist(rng);
		int value = randomSlider->getValue();

		for (int x = 0; x < board.getCellCount(); x++)
		{
			random = xDist(rng);
			if (random > value)
				board.getCell(x)->setAlive(true);
			else if(override->checked)
				board.getCell(x)->setAlive(false);
		}
	}
}
void EditExpander::overrideButtonClick()
{
	updateButtonText();
}
void EditExpander::saveButtonClick() 
{
	delete[] savedCells;
	savedCells = new bool[board.getCellCount()]();
	load->setState(true);

	for (int x = 0; x < board.getCellCount(); x++)
		savedCells[x] = board.getCell(x)->getState();
}
void EditExpander::loadButtonClick() 
{
	delete[] undoCells;
	undoCells = new bool[board.getCellCount()]();
	for (int x = 0; x < board.getCellCount(); x++)
	{
		//First save the previous state for undo
		undoCells[x] = board.getCell(x)->getState();
		//Then update the cell from the saved state
		board.getCell(x)->setAlive(savedCells[x]);
	}
	undo->setState(true);		
}

void EditExpander::undoButtonClick()
{
	for (int x = 0; x < board.getCellCount(); x++)
		board.getCell(x)->setAlive(undoCells[x]);

	undo->setState(false);
}

void EditExpander::setUndoButton(bool state)
{
	undo->setState(state);
}

void EditExpander::setUndoCells()
{
	delete[] undoCells;
	undoCells = new bool[board.getCellCount()]();
	for (int x = 0; x < board.getCellCount(); x++)
		undoCells[x] = board.getCell(x)->getState();
	undo->setState(true);
}