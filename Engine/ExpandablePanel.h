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
	void handleEvent(const InputHandler::Event event, InputManager* manager) override;
	bool checkFocus(InputHandler::Event event) const override;
	void loseFocus() override;
	//Inherited via Panel
	void draw(Graphics& gfx) const override;
	DebugInfo getDebugInfo() const override;

protected:
	class HeaderButton : public Button
	{
	public:
		HeaderButton()
			:
			Button(Rect(),""),
			parent(nullptr)
		{}
		HeaderButton(Rect rect, std::string text, ExpandablePanel* parent)
			:
			Button(rect, text),
			parent(parent)
		{}

		// Inherited via Panel
		DebugInfo getDebugInfo() const override
		{
			return DebugInfo("Button: ", text.getText());
		}
		// Inherited via ActionPanel
		void handleEvent(const InputHandler::Event event, InputManager* manager) override
		{
			if (event.type == InputHandler::Event::Type::LPress)
				parent->expanderClick(manager);
		}

		ExpandablePanel* parent;
	};

	//Variables
	HeaderButton expander;
	bool isOpen = false;

	//Functions
	void expanderClick(InputManager* manager);

private:

};

