#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <SDL/SDL.h>

typedef struct{
        SDL_Surface *p_screen;
        SDL_Surface *show_picture;
	SDL_Surface *food;
} SCREEN;

extern Uint32 begin_time, end_time;

#endif

