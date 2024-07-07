#include "MasterUIPanel.h"
#include "InputManager.h"

MasterUIPanel::MasterUIPanel()
	:
	Container(Rect(0,0, Graphics::ScreenWidth, Graphics::ScreenHeight), nullptr)
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
	//testing/debugging code, to remove
	contents.push_back(&c1);
	contents.push_back(&c2);
	contents.push_back(&c3);
	contents.push_back(&c4);
	contents.push_back(&c5);
	//contents.push_back(&sprite1);
	//contents.push_back(&text1);
	//text1.drawBorder = true;
	//text1.drawBackground = true;

	contents.push_back(&debugPanel);
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
