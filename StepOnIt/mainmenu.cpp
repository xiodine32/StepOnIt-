#include "mainmenu.h"
#include "TextDrawer.h"
#include "game.h"
#include <string.h>


void mainmenu::Draw()
{
	TextDrawer::Draw(game::GameWidth/2-11*16,10,32,sin(ticks/100.0),cos(ticks/100.0),1-sin(ticks/100.0),1,"Step on IT!");
	for (vector<menu>::iterator i=menuItems.begin();i!=menuItems.end();i++){
		TextDrawer::Draw(i->x,i->y,24,1,!i->selected,!i->selected,1,i->name);
	}
}
bool mainmenu::MouseInRange(int x,int y,int width,int height){
	return (mx>=x && my>=y && mx<=x+width && my<=y+height);
}
void mainmenu::Tick()
{
	ticks++;
	for (vector<menu>::iterator i=menuItems.begin();i!=menuItems.end();i++){
		if (MouseInRange(i->x,i->y,strlen(i->name)*24,40))
			i->selected=true;
		else
			i->selected=false;
	}
}

void mainmenu::HandleEvents(SDL_Event event)
{
	switch (event.type){
	case SDL_MOUSEMOTION:
		mx=event.motion.x;
		my=event.motion.y;
		break;
	case SDL_MOUSEBUTTONUP:
		if (menuItems[3].selected)
			game::running=false;
		if (menuItems[0].selected){
			game::SwitchToScreen(game::current::Game);
			return;
		}
		if (menuItems[2].selected){
			game::SwitchToScreen(game::current::Help);
			return;
		}
		if (menuItems[1].selected){
			game::SwitchToScreen(game::current::Options);
			return;
		}
		break;
	}
}

mainmenu::mainmenu()
{
	ticks=0;
	menu temp;memset(temp.name,0,sizeof(temp.name));
	strcpy(temp.name,"Play");
	temp.x=game::GameWidth/2-strlen(temp.name)*12;
	temp.y=100;
	temp.selected=false;
	menuItems.push_back(temp);

	strcpy(temp.name,"Options");
	temp.x=game::GameWidth/2-strlen(temp.name)*12;
	temp.y=200;
	temp.selected=false;
	menuItems.push_back(temp);

	strcpy(temp.name,"Help");
	temp.x=game::GameWidth/2-strlen(temp.name)*12;
	temp.y=300;
	temp.selected=false;
	menuItems.push_back(temp);

	strcpy(temp.name,"Quit");
	temp.x=game::GameWidth/2-strlen(temp.name)*12;
	temp.y=400;
	temp.selected=false;
	menuItems.push_back(temp);

}

mainmenu::~mainmenu()
{
	printf("Main menu away!");
	menuItems.clear();
}
