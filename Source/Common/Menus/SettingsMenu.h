
#include "Menu.h"

class OpenGLTexture;

class SettingsMenu : public Menu
{
public:
	SettingsMenu();
	~SettingsMenu();

	// Returns the name of the screen
	const char* getName();

	void saveSettings();

private:
    void buttonAction(UIButton* button);

	int m_Difficulty;
	int m_ScoreLimit;
	double m_TimeLimit;
};