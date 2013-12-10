#include "SettingsMenu.h"
#include "../UI/UIButton.h"
#include "../Screen Manager/ScreenManager.h"
#include "../OpenGL/OpenGL.h"
#include "../Libraries/jsoncpp/json.h"
#include <fstream>


SettingsMenu::SettingsMenu() : Menu(NULL, NULL),
	m_Difficulty(1),
	m_ScoreLimit(10000),
	m_TimeLimit(120.0)
{
	addButton(new UIButton("ButtonEasy"));
	addButton(new UIButton("ButtonScoreLimit1"));
	addButton(new UIButton("ButtonTimeLimit2"));
	addButton(new UIButton("ButtonExit"));
	
	m_Background = new OpenGLTexture("SettingsBG");
}

SettingsMenu::~SettingsMenu()
{

}

const char* SettingsMenu::getName()
{
	return SETTINGS_MENU_SCREEN_NAME;
}

void SettingsMenu::saveSettings()
{
	Json::Value root;
	root["Difficulty"] = m_Difficulty;
	root["ScoreLimit"] = m_ScoreLimit;
	root["TimeLimit"] = m_TimeLimit;

	// Open output stream
	std::ofstream outputStream;
	outputStream.open("settings", std::ofstream::out);

	// Create a json styled writer
	Json::StyledStreamWriter writer;
	writer.write(outputStream, root);

	// Close the output stream
	outputStream.close();
}

void SettingsMenu::buttonAction(UIButton* button)
{
	switch(getIndexForButton(button))
	{
	case 0:
		// Cycle through button textures
		if(m_Buttons.at(0)->m_NormalState->getFilename() == "ButtonEasy")
		{
			m_Buttons.at(0)->changeButtonTexture("ButtonNormal");
			m_Difficulty = 2;
		}
		else if(m_Buttons.at(0)->m_NormalState->getFilename() == "ButtonNormal")
		{
			m_Buttons.at(0)->changeButtonTexture("ButtonHard");
			m_Difficulty = 3;
		}
		else if(m_Buttons.at(0)->m_NormalState->getFilename() == "ButtonHard")
		{
			m_Buttons.at(0)->changeButtonTexture("ButtonEasy");
			m_Difficulty = 1;
		}

		break;

	case 1:
		// Change score limit
		if(m_Buttons.at(1)->m_NormalState->getFilename() == "ButtonScoreLimit1")
		{
			m_Buttons.at(1)->changeButtonTexture("ButtonScoreLimit2");
			m_ScoreLimit = 50000;
		}
		else if(m_Buttons.at(1)->m_NormalState->getFilename() == "ButtonScoreLimit2")
		{
			m_Buttons.at(1)->changeButtonTexture("ButtonScoreLimitNone");
			m_ScoreLimit = 0;
		}
		else if(m_Buttons.at(1)->m_NormalState->getFilename() == "ButtonScoreLimitNone")
		{
			m_Buttons.at(1)->changeButtonTexture("ButtonScoreLimit1");
			m_ScoreLimit = 10000;
		}

		break;

	case 2:
		// Change time limit
		if(m_Buttons.at(2)->m_NormalState->getFilename() == "ButtonTimeLimit2")
		{
			m_Buttons.at(2)->changeButtonTexture("ButtonTimeLimit5");
			m_TimeLimit = 300.0;
		}
		else if(m_Buttons.at(2)->m_NormalState->getFilename() == "ButtonTimeLimit5")
		{
			m_Buttons.at(2)->changeButtonTexture("ButtonTimeLimitNone");
			m_TimeLimit = 0;
		}
		else if(m_Buttons.at(2)->m_NormalState->getFilename() == "ButtonTimeLimitNone")
		{
			m_Buttons.at(2)->changeButtonTexture("ButtonTimeLimit2");
			m_TimeLimit = 120.0;
		}

		break;

	case 3:
		// Exit - save settings and go back to the main menu
		saveSettings();
		ScreenManager::getInstance()->switchScreen(ScreenManager::getInstance()->getPreviousScreen());
		break;


	}
}