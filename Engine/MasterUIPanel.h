#pragma once
#include "Container.h"
#include "TextPanel.h"
#include "ExpandablePanel.h"
#include "Board.h"
#include "SideBar.h"
#include "BrushRadioGroup.h"

//TODO remove?
#include "Cell.h"

class MasterUIPanel: public Container
{
public:
	MasterUIPanel();

	//inherited via Panel
	DebugInfo getDebugInfo() const override;

	//Inherited via Container
	void setContents() override;
	void updateDebugPanel(std::string text, bool display);

	//Functions
	void initShortcutManager(InputManager* input);

private:
	Board board = Board(Rect(75, 0, Graphics::ScreenWidth - 76, Graphics::ScreenHeight - 1), this);
	TextPanel debugPanel = TextPanel(std::string(TextPanel::TEXT_SPRITE16X28),
		Rect(0, 0, Graphics::ScreenWidth - 1, Graphics::ScreenHeight - 1),
		" ");
	SideBar sideBar = SideBar(Rect(0, 0, 75, 1299), this, board);
};