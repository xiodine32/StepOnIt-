#include "helpmenu.h"


helpmenu::helpmenu(void)
{
	strcpy(text,"Scope: Survival\nRequirements: Mouse\nDifficulty: From very easy\nto GODLIKE\n\nHow to do it?\n--------------\n\n\nClick on the circle before\nit fills up\n\nPress any key to return...");
	progress=0;
	memset(lastDraw,0,sizeof(lastDraw));
	memset(toDraw,0,sizeof(lastDraw));
	alpha=0;
	displayY=20;
}


helpmenu::~helpmenu(void)
{
}

void helpmenu::Draw()
{
	TextDrawer::Draw(0,20,24,1,1,1,1,lastDraw);
	TextDrawer::Draw(displayX-26*2,displayY,24,1,1,1,alpha,"%c",toDraw[strlen(toDraw)-1]);
	
	
}

void helpmenu::Tick()
{
	//0 = 1
	//-f -> h?
	//h=-f/x
	static int lastUpdate=-1;
	lastUpdate++;
	alpha=1-double(lastUpdate)/double(TextDelay(text[progress]));
	if (lastUpdate==0 && progress<=(int)strlen(text)){
		strcpy(lastDraw,toDraw);
		progress++;
		lastUpdate=TextDelay(text[progress],true);
		if (progress>(int)strlen(text))
			progress=strlen(text);
		strcpy(toDraw,text);
		toDraw[progress]=0;
	}
}

void helpmenu::HandleEvents( SDL_Event event )
{
	if (event.type==SDL_KEYUP)
		game::SwitchToScreen(game::current::MainMenu);
}

int helpmenu::TextDelay( char x ,bool finish)
{
	if (finish) displayX+=26;
	if (x>='a' && x<='z') return -7;
	if (x>='A' && x<='Z') return -10;
	
	switch (x){
	case '.':return -60;
	case '-':return -2;
	case ' ': return -4;
	case '\n':if (finish) {displayX=0;displayY+=40;} return -4;
	default: return -12;

	}
// 	if (text[progress]=='.')
// 		lastUpdate=-60;
// 	if (text[progress]=='-')
// 		lastUpdate=-2;else
// 		if (text[progress]==' ' || text[progress]=='\n')
// 			lastUpdate-=4; else
// 			if (text[progress]>='A' && text[progress]<='Z')
// 				lastUpdate-=10; else
// 				if (text[progress]>='a' && text[progress]<='z')
// 					lastUpdate-=7; else
// 					lastUpdate-=12;
}
