#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "../include/food.h"
#include "../include/move.h"

SDL_Rect rand_xy(SDL_Rect *rcSprite)
{
	int i,j;

	srand(time(NULL));
	i=rand()%(SCREEN_WIDTH-15);
	j=rand()%(SCREEN_HEIGHT-15);
	rcSprite->x = i > 15 ? i - i % 15 : 0;	
	rcSprite->y = j > 15 ? j - j % 15 : 0;	
	return *rcSprite;
		
}

SDL_Rect appa(SDL_Surface *screen, SDL_Surface *sprite, SDL_Rect *rcSprite)
{
	SDL_FillRect(screen, rcSprite, 0);
	sprite = SDL_LoadBMP("/usr/games/snakes/image/food.bmp");      	 
		SDL_BlitSurface(sprite, NULL, screen, rcSprite);
	return *rcSprite;
}

int getfood(SDL_Rect *head, SDL_Rect *food)
{
	if ((head->x == food->x) && (head->y == food->y))
		return 1;
	else return 0;
}

int check(const SDL_Rect *snake)
{
	if(snake[0].x > SCREEN_WIDTH - 15 || snake[0].x < 0 || snake[0].y > SCREEN_HEIGHT - 15 || 
		snake[0].y < 0 || self(snake))
			return 1;
	else return 0;
}

int self(const SDL_Rect *snake)//全局lenth
{
	int i;
	for (i=1;i<snake_lenth;i++)
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
			return 1;
	return 0;
}

void e_x_i_t(SDL_Surface *screen)
{
	Uint8 *keystate;

	keystate = SDL_GetKeyState(NULL);
     SDL_Quit();
}


void game_over(SDL_Surface *screen)
{
	SDL_Surface *sprite;
	SDL_Rect rcSprite;
	sprite = SDL_LoadBMP("/usr/games/snakes/image/gameover.bmp");

	/* set sprite position */
	rcSprite.x = 100;
	rcSprite.y = 100;
		/* draw the sprite */
	SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

		/* update the screen */
	SDL_Flip(screen);
}

void game_win(SDL_Surface *screen)
{
	SDL_Surface *sprite;
	SDL_Rect rcSprite;
	sprite = SDL_LoadBMP("/usr/games/snakes/image/gamewin.bmp");

	/* set sprite position */
	rcSprite.x = 100;
	rcSprite.y = 100;
		/* draw the sprite */
	SDL_BlitSurface(sprite, NULL, screen, &rcSprite);

		/* update the screen */
	SDL_Flip(screen);
}



