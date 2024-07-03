#pragma once
#include "ActionPanel.h"
#include <vector>

class Container:public ActionPanel
{
public:
	//Constructors
	Container(Rect rect, Container* parent);

	//Inherited from ActionPanel
	bool interactsWith(const Tuple point) const override;
	//Inherited from Panel
	virtual void update() override;
	virtual void draw(Graphics& gfx) const override;
	std::string getDebugInfo() const override;

	//Functions

protected:
	virtual void setContents();

	Container* parent = nullptr;
	std::vector<Panel*> contents;
};