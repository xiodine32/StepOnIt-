#pragma once
#include "core.h"
#include "game.h"
#include <vector>
#include <string.h>
using namespace std;
class optionsmenu : public core
{
private:
	struct menu{
		char text[20];
		int x,y;
		bool activated;
	};
	
	vector<menu> menuItems;
	
	vector<menu>::iterator iMenuItems;

public:
	optionsmenu();

	bool MouseInRange(int mouseX,int mouseY,int x,int y,int width,int height);

	virtual void Draw();

	virtual void Tick();

	virtual void HandleEvents( SDL_Event event );

};

