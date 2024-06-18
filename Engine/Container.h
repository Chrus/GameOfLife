#pragma once
#include "ActionPanel.h"
#include <vector>

class Container:public ActionPanel
{
public:
	//Constructors
	Container(Rect rect, Container* parent);

	//Functions
	bool interactsWith(const Tuple point) const override;
	std::string getDebugInfo() const override;

private:
	virtual void setContents() = 0;

	Container* parent = nullptr;
	std::vector<Panel*> contents;
};