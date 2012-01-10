#include "optionsmenu.h"

void optionsmenu::Draw()
{
	for (iMenuItems=menuItems.begin();iMenuItems!=menuItems.end();iMenuItems++)
		TextDrawer::Draw(iMenuItems->x,iMenuItems->y,24,!iMenuItems->activated,iMenuItems->activated,0,1,iMenuItems->text);
	TextDrawer::Draw(0,game::GameHeight-40,24,1,1,1,1,"Press any key to return...");
}

void optionsmenu::Tick()
{
	
}

void optionsmenu::HandleEvents( SDL_Event event )
{
	switch (event.type){
	case SDL_MOUSEBUTTONUP:
		for (iMenuItems=menuItems.begin();iMenuItems!=menuItems.end();iMenuItems++)
			if (MouseInRange(event.button.x,event.button.y,iMenuItems->x,iMenuItems->y,strlen(iMenuItems->text)*24,40))
				iMenuItems->activated=!iMenuItems->activated;
		if (menuItems[0].activated)
			game::music=true;
		else
			game::music=false;
		break;
	case SDL_KEYUP:
		game::SwitchToScreen(game::current::MainMenu);
		break;
	}
}

optionsmenu::optionsmenu()
{
	menu temp;
	strcpy(temp.text,"Sounds");
	temp.x=game::GameWidth/2-strlen(temp.text)*12;
	temp.y=200;
	temp.activated=true;
	menuItems.push_back(temp);
}

bool optionsmenu::MouseInRange(int mouseX,int mouseY, int x,int y,int width,int height )
{
	return (mouseX>=x && mouseY>=y && mouseX<=x+width && mouseY<=y+height);
}
