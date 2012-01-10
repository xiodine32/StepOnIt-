#include "game.h"
#include "TextDrawer.h"
#include "gamescreen.h"
#include "endscreen.h"
#include "helpmenu.h"
#include "optionsmenu.h"


game::game(){
	fullscreen=false;
	running=true;
	currentScreen=new mainmenu();
	TextDrawer::Init();
	TextDrawer::LoadTexture();
	needsChange=false;
}
void game::Tick(){
	static int totalTicks=0,lastSecond;
	totalTicks+=1;
	if (currentTick-lastSecond>1000){
		lastSecond=currentTick;
		fps=totalTicks;
		totalTicks=0;
	}
	currentScreen->Tick();
}

void game::Draw(){
		TextDrawer::Draw(0,0,12,1,1,1,1,"FPS:%d",fps);
		currentScreen->Draw();
	}

void game::HandleEvents(){
	SDL_Event Event;
	while (SDL_PollEvent(&Event)){
		switch (Event.type){
		case SDL_QUIT:running=false;return;
		case SDL_KEYDOWN:
		case SDL_KEYUP :
		case SDL_MOUSEBUTTONUP :
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEMOTION:
			if (Event.type==SDL_KEYUP && Event.key.keysym.sym==SDLK_F10){
				int args=SDL_OPENGL;
				fullscreen=fullscreen?0:1;
				if (fullscreen)
					args|=SDL_FULLSCREEN;
				SDL_SetVideoMode(game::GameWidth,game::GameHeight,0,args);
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glViewport(0,0,game::GameWidth,game::GameHeight);
				glOrtho(0,game::GameWidth,game::GameHeight,0,-1,1);


				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_TEXTURE_2D);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				TextDrawer::LoadTexture();
			}
			currentScreen->HandleEvents(Event);
			break;
		}
	}
}
void game::Run()
{
	const double targetFPS=1000.0/60.0;
	double lastTick=double(SDL_GetTicks());
	while (running){
		glClear(GL_COLOR_BUFFER_BIT);

		if (needsChange){
			needsChange=false;
			delete currentScreen;
			switch (toChange){
			case Game:
				currentScreen=new gamescreen();
				break;
			case MainMenu: 
				currentScreen=new mainmenu();
				break;
			case End:
				currentScreen=new endscreen();
				break;
			case Help:
				currentScreen=new helpmenu();
				break;
			case Options:
				currentScreen=new optionsmenu();
			}
		}

		HandleEvents();

		currentTick=SDL_GetTicks();
		while (currentTick-lastTick>targetFPS){
			lastTick+=targetFPS;
			Tick(); 
			 
		}
		Draw();
		SDL_GL_SwapBuffers();
	}
}	

void game::SwitchToScreen( current x )
{
	needsChange=true;
	toChange=x;
}

core *game::currentScreen=NULL;
int game::GameWidth=800,game::GameHeight=600,game::currentTick=0;
bool game::running=false,game::music=true,game::needsChange;
game::current game::toChange=game::current::MainMenu;