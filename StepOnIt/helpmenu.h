#pragma once
#include "core.h"
#include "game.h"
#include <string.h>
#include "TextDrawer.h"
class helpmenu : public core
{
private:
	char text[1001],toDraw[1001],lastDraw[1001];
	int progress;
	int displayX,displayY;
public:
	
	double alpha;
	helpmenu(void);
	~helpmenu(void);
	virtual void Draw();
	virtual void Tick();
	virtual void HandleEvents( SDL_Event event );
	int TextDelay(char x,bool finish=false);
};

