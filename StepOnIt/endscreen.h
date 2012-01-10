#pragma once
#include "core.h"
#include <SDL_mixer.h>
#include <vector>
using namespace std;
class endscreen : public core
{
private:
	int circles,clicks,accuracy,reactionTime,score;
	int bestScore,bestCircles,bestAccuracy,bestReactionTime;
	int drawedScore;
	Mix_Music *mLost;
	int previousScore;
	double previousAccuracy;
	struct color{
		int number;
		double r,g,b;
	} drawedScoreColor[10];
	void SaveBest();
public:
	endscreen();
	~endscreen();

	virtual void Draw();

	virtual void Tick();

	virtual void HandleEvents( SDL_Event event );
};

