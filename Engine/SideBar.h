#pragma once
#include "Container.h"
#include "Board.h"
#include "ControlsExpander.h"

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

protected:
	//Inherited via Container
	void setContents() override;

private:
	Board& board;
};

