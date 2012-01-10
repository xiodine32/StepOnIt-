#pragma once
#include "core.h"
#include <math.h>
#include <vector>
#include "TextDrawer.h"
using namespace std;
class mainmenu : public core
{
private:
	struct menu{
		char name[20];
		int x,y;
		bool selected;
	};
	vector<menu> menuItems;
	int mx,my,ticks;
public:
	mainmenu();
	~mainmenu();
	
	bool MouseInRange(int x,int y,int width,int height);

	void Draw();

	void Tick();

	void HandleEvents( SDL_Event event);

};

