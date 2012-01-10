#include "endscreen.h"
#include <math.h>
#include "gamescreen.h"
#include "TextDrawer.h"
#include "game.h"
#include <stdio.h>
#include <fstream>
using namespace std;
endscreen::endscreen()
{
	FILE *f=fopen("lastGame.sav","rb");
	fread(&circles,sizeof(circles),1,f);
	fread(&clicks,sizeof(clicks),1,f);
	fread(&accuracy,sizeof(accuracy),1,f);
	fread(&reactionTime,sizeof(reactionTime),1,f);
	fread(&score,sizeof(score),1,f);
	fclose(f);
	ifstream temp("bestGame.dat");
	if (!temp.good()){
		temp.close();
		bestScore=score;
		bestCircles=circles;
		bestAccuracy=accuracy;
		bestReactionTime=reactionTime;
		SaveBest();
	}

	f=fopen("bestGame.dat","rb");
		fread(&bestScore,sizeof(bestScore),1,f);
		fread(&bestCircles,sizeof(bestCircles),1,f);
		fread(&bestAccuracy,sizeof(bestAccuracy),1,f);
		fread(&bestReactionTime,sizeof(bestReactionTime),1,f);
	fclose(f);

	drawedScore=0;
	for (int i=0;i<=9;i++){
		drawedScoreColor[i].r=drawedScoreColor[i].g=drawedScoreColor[i].b=drawedScoreColor[i].number=0;
	}
	mLost=Mix_LoadMUS("gameOver.wav");
	if (game::music)
		Mix_PlayMusic(mLost,0);
	memset(drawedScoreColor,0,sizeof(drawedScoreColor));
}


endscreen::~endscreen()
{
	SaveBest();
	Mix_HaltMusic();
	Mix_FreeMusic(mLost);
	mLost=NULL;
}

void endscreen::Draw()
{
	
	TextDrawer::Draw(100,100,24,1,1,1,1,"You obtained: ");
	int temp=-1;
	if (score==0)
		TextDrawer::Draw(444,100,24,1,0,0,1,"0");
	for (int i=drawedScoreColor[0].number;i>=1;i--)
	{
		temp++;
		TextDrawer::Draw(444+temp*24,100,24,drawedScoreColor[i].r,drawedScoreColor[i].g,drawedScoreColor[i].b,1,"%d",drawedScoreColor[i].number);

	}
	
	if (score>=bestScore)	TextDrawer::Draw(600-24,100,24,1,0,0,1,"NEW BEST!");
	TextDrawer::Draw(0,200,12,1,1,1,1,"Circles Hit: %d",circles);
	if (circles>=bestCircles)	TextDrawer::Draw(500,200,12,1,0,0,1,"NEW BEST!");
	TextDrawer::Draw(0,220,12,1,1,1,1,"Accuracy: %d%c",accuracy,'%');
	if (accuracy>=bestAccuracy)	TextDrawer::Draw(500,220,12,1,0,0,1,"NEW BEST!");
	TextDrawer::Draw(0,240,12,1,1,1,1,"Fastest Reaction Time: %dms",reactionTime);
	if (reactionTime<=bestReactionTime)	TextDrawer::Draw(500,240,12,1,0,0,1,"NEW BEST!");

}

void endscreen::Tick()
{
	static int counter=0;
	if (drawedScore!=score){
		int tmpa,tmpb;
		tmpb=drawedScore;
		drawedScore+=int(ceil((score-drawedScore)/360.0));
		counter=0;
		tmpa=drawedScore;
		
		int v[10]={0,0};
		while (tmpb>0){
			v[++v[0]]=tmpb%10;
			tmpb/=10;
		}
		drawedScoreColor[0].number=0;
		while (tmpa>0){
			drawedScoreColor[++drawedScoreColor[0].number].number=tmpa%10;
			tmpa/=10;
		}
		for (int i=1;i<=drawedScoreColor[0].number;i++){
			if (drawedScoreColor[i].number!=v[i] || v[0]!=drawedScoreColor[0].number){
				drawedScoreColor[i].r=(rand()%100)/100.0+0.1f;
				drawedScoreColor[i].g=(rand()%100)/100.0+0.1f;
				drawedScoreColor[i].b=(rand()%100)/100.0+0.1f;	

			}
		}
	}
}

void endscreen::HandleEvents( SDL_Event event )
{
	switch (event.type){
	case SDL_KEYUP:
		if (event.key.keysym.sym==SDLK_ESCAPE)
			game::SwitchToScreen(game::current::MainMenu);
		break;
	}
}

void endscreen::SaveBest()
{
	if (circles>bestCircles)
		bestCircles=circles;
	if (score>bestScore)
		bestScore=score;
	if (reactionTime<bestReactionTime)
		bestReactionTime=reactionTime;
	if (accuracy>bestAccuracy)
		bestAccuracy=accuracy;
	FILE *f;
	f=fopen("bestGame.dat","wb");
	fwrite(&bestScore,sizeof(bestScore),1,f);
	fwrite(&bestCircles,sizeof(bestCircles),1,f);
	fwrite(&bestAccuracy,sizeof(bestAccuracy),1,f);
	fwrite(&bestReactionTime,sizeof(bestReactionTime),1,f);
	fclose(f);
}
