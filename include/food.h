#ifndef __FOOD_H__
#define __FOOD_H__

#include "snake.h"

extern int snake_lenth;

extern int getfood(SDL_Rect *head, SDL_Rect *food);

extern int check(const SDL_Rect *snake);

extern SDL_Rect rand_xy(SDL_Rect *rcSprite);

extern SDL_Rect appa(SCREEN *screen, SDL_Rect *rcSprite);

extern void game_over(SDL_Surface *screen);

extern void game_win(SDL_Surface *screen);

int self(const SDL_Rect *snake);

#endif
