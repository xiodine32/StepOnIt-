#include "gamescreen.h"

gamescreen::gamescreen(void)
{
	statCircles=0;statClicks=0;statAccuracy=0;statReactionTime=99999;statScore=0;
	lifes=10;
	mDiff=mHit=mMiss=mLifeHit=NULL;
	mDiff=Mix_LoadWAV("difficultyIncreased.wav");
	mHit=Mix_LoadWAV("itemHit.wav");
	mMiss=Mix_LoadWAV("itemMiss.wav");
	mLifeHit=Mix_LoadWAV("lifeHit.wav");
	printf("Loaded stuff...\n");
}


gamescreen::~gamescreen(void)
{
	Mix_HaltMusic();
	Mix_FreeChunk(mDiff);
	Mix_FreeChunk(mHit);
	Mix_FreeChunk(mMiss);
	Mix_FreeChunk(mLifeHit);
	mDiff=NULL;mHit=NULL;mMiss=NULL;mLifeHit=NULL;
	gameCircles.clear();
	printf("Unloaded stuff... stopped music ... cleared circles! \n");
	FILE *f=fopen("lastGame.sav","wb");
	fwrite(&statCircles,sizeof(statCircles),1,f);
	fwrite(&statClicks,sizeof(statClicks),1,f);
	fwrite(&statAccuracy,sizeof(statAccuracy),1,f);
	fwrite(&statReactionTime,sizeof(statReactionTime),1,f);
	fwrite(&statScore,sizeof(statScore),1,f);
	fclose(f);
}

void gamescreen::DrawCircle(int x,int y,double size,bool hollow, double r,double g,double b,double a){
	double i=0,PI=3.1415926535;
	glColor4d(r,g,b,a);
	glDisable(GL_TEXTURE_2D);
	if (!hollow)
		glBegin(GL_POLYGON);
	else{
		glBegin(GL_LINE_LOOP);
		size+=0.01;
	}
		for (i=0;i<=2*PI;i+=0.01){
			glVertex2d(x+sin(i)*size,y+cos(i)*size);
		}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

bool gamescreen::MouseInsideCircle(gameElement circle){
	return (mouseX-circle.x)*(mouseX-circle.x)+(mouseY-circle.y)*(mouseY-circle.y)<circle.size*circle.size;;
}

void gamescreen::Draw()
{
	//TextDrawer::Draw(0,100,12,1,1,1,1,"sC:%d\nsCC:%d\nsA:%d\nsRT:%d\nsS:%d",statCircles,statClicks,statAccuracy,statReactionTime,statScore);
	//drawing increased difficulty
	if (triggerIncreasedDifficulty)
		TextDrawer::Draw(0,70,12,1,1,1,1,"Difficulty increased!");
	//drawing lifes
	int i=0;
	for (i=1;i<=lifes;i++)
		TextDrawer::Draw(i*16-16,50,16,1,0,0,1,"%c",3);
	TextDrawer::Draw(i*16-16,50,16,1,1,1,1,"-%d",lifes);
	//drawing game elements - circles
	for (vector<gameElement>::iterator i=gameCircles.begin();i!=gameCircles.end();i++){
		DrawCircle(i->x,i->y,i->size*(game::currentTick-i->tickAtStart)/double(i->lifeSpan),false,i->r,i->g,i->b,1);
		DrawCircle(i->x,i->y,i->size,true,i->r,i->g,i->b,1);
	}
	//drawing score added

	for (vector<displayScore>::iterator i=hitPlusScore.begin();i!=hitPlusScore.end();i++){
		glPushMatrix();
			glTranslated(i->X+i->size,i->Y+i->size/2,0);
			glRotated(i->rot,0,0,1);
			TextDrawer::Draw(int(-i->size),int(-i->size/2),int(i->size),i->r,i->g,i->b,i->a,"+%d",i->score);
		glPopMatrix();
	}
}

void gamescreen::Tick()
{
	static int lastSpawned=-1,lastNotified;
	lastSpawned++;
	if (lastSpawned==0){
		lastSpawned=-60;
		if (statCircles==20 || statCircles==30 || statCircles==80){
			triggerIncreasedDifficulty=true;
		}
		else
		{
			if (triggerIncreasedDifficulty){
				triggerIncreasedDifficulty=false;
				if (game::music)
					Mix_PlayChannel(-1,mDiff,0);
			}
		}
		if (statCircles>2){
			lastSpawned=-45;
		}
		if (statCircles>10){
			lastSpawned=-40;
		}
		if (statCircles>20){
			lastSpawned=-35;
		}
		if (statCircles>30){
			lastSpawned=-30;
		}
		if (statCircles>80){
			lastSpawned=-20;
		}
		gameElement temp;
		temp.lifeSpan=1000+rand()%10000+(statCircles>100?-(statCircles*5):statCircles);
		temp.x=rand()%800;
		temp.y=rand()%600;
		temp.r=(rand()%100)/100.0;
		temp.g=(rand()%100)/100.0;
		temp.b=(rand()%100)/100.0;		
		temp.tickAtStart=game::currentTick;
		temp.size=20+(rand()%100)/10.0+(statCircles>100?100:statCircles)/2.0;
		temp.points=int(temp.size/4);
		gameCircles.push_back(temp);
	}
	int counter=0;
	stack<int> toDelete;
	for (vector<gameElement>::iterator i=gameCircles.begin();i!=gameCircles.end();i++){
		if (game::currentTick-i->lifeSpan-i->tickAtStart>0){
			toDelete.push(counter);
		}

		counter++;
	}
	while (!toDelete.empty()){//Deleted a circle
		if (game::music)
			Mix_PlayChannel(-1,mLifeHit,0);
		lifes--;
		gameCircles.erase(gameCircles.begin()+toDelete.top());
		toDelete.pop();
		if (lifes==0){
			game::SwitchToScreen(game::current::End);
		}
	} 
	counter=-1;
	for (vector<displayScore>::iterator i=hitPlusScore.begin();i!=hitPlusScore.end();i++){
		counter++;
		i->rot+=i->rotAlpha;
		i->X+=i->rot<0?-1:1;
		if (i->rot<-30){i->rotAlpha=1;}
		if (i->rot>30){i->rotAlpha=-1;}
		i->Y-=0.5;
		i->a-=0.002;
		if (i->a<0){
			toDelete.push(counter);
		}
	}
	while (!toDelete.empty()){
		hitPlusScore.erase(hitPlusScore.begin()+toDelete.top());
		toDelete.pop();
	}
}

void gamescreen::HandleEvents( SDL_Event event )
{
	int rTime=0;
	switch (event.type){
	case SDL_MOUSEMOTION:
		mouseX=event.motion.x;
		mouseY=event.motion.y;
		break;
	case SDL_MOUSEBUTTONUP:
		statClicks++;
		int counter=-1;bool found=false;
		for (vector<gameElement>::iterator i=gameCircles.begin();i!=gameCircles.end();i++){
			counter++;
			if (MouseInsideCircle(*i)){
				found=true;
				rTime=game::currentTick-i->tickAtStart;

				displayScore temp;
				temp.score=i->points;
				temp.X=i->x;temp.Y=i->y;
				temp.size=12+rand()%5;
				temp.rot=0;temp.rotAlpha=-1;
				temp.r=i->r;
				temp.g=i->g;
				temp.b=i->b;
				temp.a=1;
				hitPlusScore.push_back(temp);
				break;
			}
		}
		if (found){//Clicked a circle

			

			if (statReactionTime>rTime)
				statReactionTime=rTime;
			statScore+=gameCircles[counter].points;
			gameCircles.erase(gameCircles.begin()+counter);
			statCircles++;
			if (game::music)
				Mix_PlayChannel(-1,mHit,0);
		} else{
			if (game::music)
				Mix_PlayChannel(-1,mMiss,0);
		}
		statAccuracy=int(statCircles/(double)statClicks*100);
		break;
	}
}

