/*作用：转换蛇的方向
 *作者：白色鲨鱼
 *时间：2011-8-16
 *地点：北航科技园
 */

#include <stdio.h>

#include "../include/move.h"

Uint32 begin_time, end_time;

/*判断调用SDL库函数是否成功*/
int sdl_error(char *name, void *value)
{
	if (value == NULL)
	{
		printf("%s failed:%s\n", name, SDL_GetError());
		return -1;
	}

	return 0;
}

/*初始化蛇的位置*/
int init_snake(SCREEN *screen, SDL_Rect *src, SDL_Rect *dst, int num)
{
	int i;

	/*蛇结点大小和位置*/
	src->x = 10;
	src->y = 10;
	src->w = 15;
	src->h = 15;

	for (i = 0; i < num; i++)
	{
		(dst + i)->x = 315 - i * 15;
		(dst + i)->y = 225;
		(dst + i)->w = 15;
		(dst + i)->h = 15;
	}
	for (i = num; i < 32; i++)
	{
		(dst + i)->x = 900;
		(dst + i)->y = 900;
		(dst + i)->w = 15;
		(dst + i)->h = 15;
		
	}
	/*装载蛇结点图片*/	
	screen->show_picture = SDL_LoadBMP("/usr/games/snakes/image/snake.BMP");
        sdl_error("SDL_LoadBMP", screen->show_picture);
	return 0;
}

/*将按键值转换*/
int key_snake(int *key_flag)
{
	SDL_Event   gameevent;
	
	SDL_PollEvent(&gameevent);

	switch (gameevent.type)
	{
			/*点窗口上的 X */
		case SDL_QUIT	 : return FLASE;
			break;	
			/*按下按键*/
		case SDL_KEYDOWN :
		switch (gameevent.key.keysym.sym)
		{
			/*按下上键*/
			case SDLK_UP 	: *key_flag = KEY_UP;
				break;
			/*按下下键*/
			case SDLK_DOWN 	: *key_flag = KEY_DOWN;
				break;
			/*按下左键*/
			case SDLK_LEFT 	: *key_flag = KEY_LEFT;
				break;
			/*按下右键*/
			case SDLK_RIGHT : *key_flag = KEY_RIGHT;
				break;
			/*按下ESC*/
			case SDLK_ESCAPE :return FLASE;
				break;
			default :
				break;
		}
			break;
			/*按下松开*/
		case SDL_KEYUP	 :*key_flag = KEY_NO;
			break;
		default :
			break;
	}

	return TRUE;
}

/*转向*/
int change_snake(SDL_Rect all_dst[], int *key_flag, int num)
{
	static int FLAG = 0x0000; 
	int MOVED = FLASE;
	SDL_Rect temp_dst = all_dst[0];

	/*将蛇头位置赋给temp_dst*/
	temp_dst = all_dst[0];
	/*向上移动*/
	if ((*key_flag == KEY_UP && !(FLAG & 0x0010)) || FLAG & 0x0001)
	{
		/*将其它方向屏蔽*/	
		FLAG &= 0x0000;
		/*设置自己的方向*/
		FLAG |= 0x0001;

		/*如果大于100MS就将蛇头移到下一位置*/
		if(end_time - begin_time > speed)
		{	
			/*蛇头向上移动5个像素*/
			temp_dst.y -= 15;
			/*开始新的计时*/
			begin_time = end_time;
			/*移动标志位为真*/
			MOVED = TRUE;
		}
	}

	/*向下移动*/
	if ((*key_flag == KEY_DOWN && !(FLAG & 0x0001)) || FLAG & 0x0010)
	{
		/*将其它方向屏蔽*/	
		FLAG &= 0x0000;
		/*设置自己的方向*/
		FLAG |= 0x0010;

		/*如果大于100MS就将蛇头移到下一位置*/
		if(end_time - begin_time > speed)
		{	
			/*蛇头向下移动5个像素*/
			temp_dst.y += 15;
			/*开始新的计时*/
			begin_time = end_time;
			/*移动标志位为真*/
			MOVED = TRUE;
		}
	}

	/*向左移动*/
	if ((*key_flag == KEY_LEFT && !(FLAG & 0x1000)) || FLAG & 0x0100)
	{
		/*将其它方向屏蔽*/	
		FLAG &= 0x0000;
		/*设置自己的方向*/
		FLAG |= 0x0100;

		/*如果大于100MS就将蛇头移到下一位置*/
		if(end_time - begin_time > speed)
		{	
			/*蛇头向左移动5个像素*/
			temp_dst.x -= 15;
			/*开始新的计时*/
			begin_time = end_time;
			/*移动标志位为真*/
			MOVED = TRUE;
		}
	}

	/*向右移动*/
	if ((*key_flag == KEY_RIGHT && !(FLAG & 0x0100)) || FLAG & 0x1000)
	{
		/*将其它方向屏蔽*/	
		FLAG &= 0x0000;
		/*设置自己的方向*/
		FLAG |= 0x1000;

		/*如果大于100MS就将蛇头移到下一位置*/
		if(end_time - begin_time > speed)
		{	
			/*蛇头向右移动5个像素*/
			temp_dst.x += 15;
			/*开始新的计时*/
			begin_time = end_time;
			/*移动标志位为真*/
			MOVED = TRUE;
		}
	}

	/*更新蛇结点的位置*/
	if (MOVED)
	{
		int i;
		for (i = 1; i < num; i++)
		{
			/*将前一个位置赋给后一个位置*/
			all_dst[num - i] = all_dst[num - 1 - i];
		}
		/*更新蛇头位置*/
		all_dst[0] = temp_dst;
		/*移动标志位为假*/
		MOVED = FLASE;
	}

	return 0;
}

/*创建一个窗口*/
int creat_screen(SCREEN *screen)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	atexit(SDL_Quit);

	screen->p_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SPRING_SIZE, SDL_SWSURFACE);
	sdl_error("SDL_SetVideoMode", screen->p_screen);

	return 0;
}

/*清除蛇结点*/
int clean_snake(SCREEN *screen, SDL_Rect *all_dst, int snake_lenth)
{
	int i;

	for (i = 0; i < snake_lenth; i ++)
	{
		SDL_FillRect(screen->p_screen, &all_dst[i], 0);
	}

	for (i = 0; i < snake_lenth; i ++)
	{
		all_dst[i + INIT_LENTH].x = 900;
		all_dst[i + INIT_LENTH].y = 900;
	}

	return 0;
}

/*移动蛇结点*/
int move_snake(SCREEN *screen, SDL_Rect *src, SDL_Rect *all_dst, int snake_lenth)
{
	int i, gameover = TRUE;
	static	int key_flag = KEY_NO;	

	/*清除最后一个结点*/
	SDL_FillRect(screen->p_screen, &all_dst[snake_lenth -1], 0);
	gameover = key_snake(&key_flag);
	change_snake(all_dst, &key_flag, snake_lenth);
	
	for (i = 0; i < snake_lenth; i ++)
	{
		SDL_BlitSurface(screen->show_picture, src, screen->p_screen, all_dst + i);
	}
	end_time = SDL_GetTicks();

	return gameover;
}
