#pragma once
#include "Container.h"
#include "Button.h"

class ExpandablePanel: public Container
{
public:
	//Constructors
	ExpandablePanel(Rect expanderRect, Rect contentsRect, Container* parent, std::string text);

	//Inherited via ActionPanel
	bool interactsWith(const Tuple point) const override;
	//Inherited via InputHandler
	bool handleEvent(const Mouse::Event event, LRHeld held, InputManager* manager) override;
	void loseFocus() override;
	//Inherited via Panel
	void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override;

protected:
	class HeaderButton : public Button
	{
	public:
		HeaderButton(Rect rect, std::string text, ExpandablePanel& parent)
			:
			Button(rect, std::string(TextPanel::TEXT_SPRITE16X28), text, parent){	}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("ExpandablePanel Header: ", 
				sprite->getDebugInfo().first + sprite->getDebugInfo().second);
		}
		// Inherited via ActionPanel
		bool handleEvent(const Mouse::Event event, LRHeld held, InputManager* manager) override
		{
			Button::handleEvent(event, held, manager);

			if (event.GetType() == Mouse::Event::Type::LPress
				&& !held.first)
			{
				return dynamic_cast<ExpandablePanel*>(parent)->expanderClick(manager);
			}
			return dynamic_cast<ExpandablePanel*>(parent)->isOpen;
		}
	};

	//Variables
	HeaderButton expander;
	bool isOpen = false;

	//Functions
	bool expanderClick(InputManager* manager);

private:

};

