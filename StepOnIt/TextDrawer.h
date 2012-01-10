#pragma once
#include <string>
#include <cstdarg>
#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_image.h>
using namespace std;
class TextDrawer
{
private:
	static unsigned int texture;
	struct Coords{
		double sx,sy,ex,ey;
	};
	static Coords *letters;
public:
	static void Init();
	static void Draw(int x,int y,int size,double r,double g,double b,double a,char *text, ...);
	static void LoadTexture(string path="font.png");
};

