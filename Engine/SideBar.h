#pragma once
#include "Container.h"
#include "Board.h"
#include "EditExpander.h"

class SideBar : public Container
{
public:
	//Constructors
	SideBar(Rect rect, Container* parent, Board& board);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;
	EditExpander* getEditExpander()
	{
		return dynamic_cast<EditExpander*>(contents[0]);
	}

	//Functions
	void setShortcutsText(std::vector<std::string> shortcuts);
	PlayPanel* getPlayPanel() const;

protected:
	//Inherited via Container
	void setContents() override;

private:
	Board& board;
};

