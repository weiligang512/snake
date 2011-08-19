/*作用：贪吃蛇主函数
 *
 *
 *
 */

#include <stdio.h>

#include "../include/snake.h"
#include "../include/move.h"
#include "../include/food.h"


int snake_lenth = INIT_LENTH;
int speed = INIT_SPEED;

int main(void)
{
	SCREEN screen;
	SDL_Surface sprite;
	SDL_Rect src, food_place;		
	SDL_Rect all_dst[32];
	int quit_screen = TRUE;
	int key_quit = KEY_NO;

	/*创建一个窗口*/
	creat_screen(&screen);
	/*初始化蛇的位置*/
	init_snake(&screen, &src, all_dst, snake_lenth);

	begin_time = SDL_GetTicks();

	food_place = rand_xy(&food_place); 

	while (quit_screen)
	{	
		/*移动*/
		quit_screen = move_snake(&screen, &src, all_dst, snake_lenth);
		/*判断是否吃到食物*/
		if (getfood(&all_dst[0], &food_place))
		{
			/*刷新一个食物*/
			food_place = rand_xy(&food_place);
			/*长度加1*/
			snake_lenth++;
			/*如果长度大于NEXT， 速度加快，进入下一关*/
			if (snake_lenth > NEXT)
			{
				/*清除蛇结点*/
				clean_snake(&screen, all_dst, snake_lenth);
				/*速度增加*/
				speed -= STEP;
				/*长度变为初始化长度*/
				snake_lenth = INIT_LENTH;
			}

			/*如果速度速度达到WIN， 胜利*/
			if (speed < WIN)
			{
				/*显示胜利*/
				game_win(screen.p_screen);
				while (quit_screen)
					quit_screen = key_snake(&key_quit);
			}
		}
		
		/*意外判断， 撞到边界、撞到自己*/
		if (check(all_dst))
		{
			/*显示gameover*/
			game_over(screen.p_screen);
			while (quit_screen)
				quit_screen = key_snake(&key_quit);
		}
		appa(screen.p_screen, &sprite, &food_place);
		SDL_Flip(screen.p_screen);
	
	}
	SDL_FreeSurface(screen.p_screen);

	return 0;
}









