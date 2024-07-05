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
	void getDebugInfo(std::vector<DebugInfo>* info) const override;
	// Inherited via InputHandler
	ActionPanel* handleEvent(InputHandler::Event event) override;
	bool checkFocus(InputHandler::Event event) const override;
	void loseFocus() override;

	//Functions

protected:
	virtual void setContents() {}

	Container* parent = nullptr;
	std::vector<Panel*> contents;
};