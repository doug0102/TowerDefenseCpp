#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../Screen Manager/Screen.h"
#include "../UI/UISideMenu.h"

class GameObject;
class Level;
class UISideMenu;
class Tower;

class Game : public Screen, public UISideMenuListener
{
public:
	Game();
	~Game();

	//Game lifecycle methods
	void update(double delta);
	void paint();
	void reset();

	//Screen name, must be implemented, it's a pure
	//virtual method in the Screen class
	const char* getName();

	Level* getLevel();

private:

	//Mouse Events
	void mouseMovementEvent(float deltaX, float deltaY, float positionX, float positionY);
	void mouseLeftClickUpEvent(float positionX, float positionY);
	void keyUpEvent(int keyCode);

	// Side menu events
	void sideMenuButtonAction(UISideMenu* sideMenu, UIButton* button, int buttonIndex);
    void sideMenuToggleAction(UISideMenu* sideMenu, UIToggle* toggle, int toggleIndex);

	// Level pointer
	Level* m_Level;

	// Side menu for placing towers
	UISideMenu* m_TowersMenu;

	// Side menu for upgrading towers, scoring, time etc.
	UISideMenu* m_ControlMenu;

	int m_SelectedTileIndex;
	int m_LocationOfSelection;

	// Textures for displaying game info
	OpenGLTexture* m_TimeLabel;
	OpenGLTexture* m_ScoreLabel;
	OpenGLTexture* m_MoneyLabel;
	OpenGLTexture* m_LivesLabel;

	Tower* m_SelectedTower;
};

#endif