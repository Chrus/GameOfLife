#pragma once
#include "ActionPanel.h"
#include <vector>

class Container:public ActionPanel
{
public:
	//Constructors
	Container(Rect rect, Container* parent);
	~Container();

	//Inherited from ActionPanel
	bool interactsWith(const Tuple point) const override;
	//Inherited from Panel
	virtual void update() override;
	virtual void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override;
	// Inherited via InputHandler
	bool handleEvent(const Mouse::Event event, const LRHeld held, InputManager* manager) override;

protected:
	virtual void setContents() {}

	Container* parent = nullptr;
	std::vector<Panel*> contents;
};