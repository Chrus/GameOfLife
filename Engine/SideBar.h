#pragma once
#include "Container.h"
#include "Board.h"

class SideBar : public Container
{
public:
	//Constructors
	SideBar(Rect rect, Container* parent, Board& board);

	//Inherited via Panel
	DebugInfo getDebugInfo() const override;

protected:
	//Inherited via Container
	void setContents() override;

private:
	Board& board;
};

