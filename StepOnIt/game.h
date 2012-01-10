#pragma once
#include "core.h"
#include "mainmenu.h"

class game
{
private:
	int fps;
	bool fullscreen;
public:
	static enum current {
		Game,Options,Help,MainMenu,End
	} ;
	static current toChange;static bool needsChange;
	static core *currentScreen;
	game();
	static int GameWidth,GameHeight;
	static bool running,music;
	static void SwitchToScreen(current);
	static int currentTick;
	void Tick();
	void Draw();
	void Run();
	void HandleEvents();
};

