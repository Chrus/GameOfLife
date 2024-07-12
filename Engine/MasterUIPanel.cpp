#include "MasterUIPanel.h"
#include "InputManager.h"

MasterUIPanel::MasterUIPanel()
	:
	Container(Rect(0,0, Graphics::ScreenWidth - 1, Graphics::ScreenHeight - 1), nullptr)
{
	setContents();
	debugPanel.drawPanel = false;
	debugPanel.drawBackground = true;
}

DebugInfo MasterUIPanel::getDebugInfo() const
{
	std::string body = "# of Contents: " + std::to_string(contents.size());
	return std::make_pair("MasterUIPanel: ", body);
}

void MasterUIPanel::setContents()
{
	contents.push_back(&board);
	contents.push_back(&controls);

	//debug needs to be last
	contents.push_back(&debugPanel);

	//testing/debugging code, to remove
	//contents.push_back(&c1);
	//contents.push_back(&c2);
	//contents.push_back(&c3);
	//contents.push_back(&c4);
	//contents.push_back(&c5);
	contents.push_back(&eP);
}

void MasterUIPanel::updateDebugPanel(std::string text, bool display)
{
	if (display)
	{
		debugPanel.setText(text);
		debugPanel.drawPanel = true;
	}
	else
	{
		debugPanel.setText("");
		debugPanel.drawPanel = false;
	}
}
