#pragma once
#include <SDL_opengl.h>
#include <SDL.h>
class core
{
protected:
	int *time;
public:
	virtual void Draw()=0;
	virtual void Tick()=0;
	virtual void HandleEvents( SDL_Event event)=0;
	virtual ~core()=0;
};

