/*作用：SDL练习
 *时间：2011－8－14
 *地点：北航科技园
 */

#include <stdio.h>
#include <SDL/SDL.h>

#define TRUE 		1
#define FALSE 		0
#define SCREEN_WIDTH  640
#define SCREEN_HEIGTH 480
#define SPRING_SIZE    32

int init_snake()
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_GetError();
		return -1;
	}

	atexit(SDL_Quit);

	return 0;
}

int quit_snake()
{
	int gameover = FALSE;
	SDL_Event   gameevent;
	
	while(!gameover)
	{
		SDL_PollEvent(&gameevent);
		if(gameevent.type == SDL_QUIT)
			gameover =TRUE;

		if(gameevent.type == SDL_KEYDOWN)
			if(gameevent.key.keysym.sym == SDLK_ESCAPE)
				gameover = TRUE;
	}
	return 0;
}

int main()
{
	init_snake();
		SDL_GetError();

	SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGTH, SPRING_SIZE, SDL_SWSURFACE);
	quit_snake();
	
	return 0;
}
