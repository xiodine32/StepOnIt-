#pragma once
#include "core.h"
#include "game.h"
#include <math.h>
#include "TextDrawer.h"
#include <stack>
#include <vector>
#include <SDL_audio.h>
#include <SDL_mixer.h>
using namespace std;
class gamescreen : public core
{
private:
	struct gameElement{
		int x,y;
		double size;
		int tickAtStart;
		int lifeSpan;
		int points;
		double r,g,b;
	};
	struct displayScore{
		int score;
		double X,Y;
		double size,rot,rotAlpha;
		double r,g,b,a;
	};
	vector<displayScore> hitPlusScore;
	Mix_Chunk *mDiff,*mHit,*mMiss,*mLifeHit;
	bool triggerIncreasedDifficulty;
	int mouseX,mouseY;
	vector<gameElement> gameCircles;
	int lifes;
	int statCircles,statClicks,statAccuracy,statReactionTime,statScore;

public:

	
	gamescreen();
	~gamescreen();
	virtual void Draw();
	virtual void Tick();
	virtual void HandleEvents( SDL_Event event);
	void DrawCircle(int x,int y,double size,bool hollow, double r,double g,double b,double a);
	bool MouseInsideCircle(gameElement circle);
};

