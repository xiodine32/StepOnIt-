#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include "game.h"

int main(int arg,char **arvg){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	SDL_WM_SetCaption("Step on It! 1.0",NULL);
	SDL_Surface *main;
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
	int audio_channels = 2;
	int audio_buffers = 4096;
	Mix_OpenAudio(audio_rate,audio_format,audio_channels,audio_buffers);

	main=SDL_SetVideoMode(game::GameWidth,game::GameHeight,0,SDL_OPENGL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,game::GameWidth,game::GameHeight);
	glOrtho(0,game::GameWidth,game::GameHeight,0,-1,1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	

	game *Game=new game();
	Game->Run();
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}