/*作用：包涵move.c中的宏定义以及声明
 *作者：白色鲨鱼
 *时间：2011-8-16
 *地点：北航科技园
 */

#ifndef __MOVE_H__
#define __MOVE_H__

#include "snake.h"

#define TRUE            !0
#define FLASE           0

#define SCREEN_WIDTH  645
#define SCREEN_HEIGHT 480
#define SPRING_SIZE    32

#define KEY_NO		0
#define KEY_UP		1
#define KEY_DOWN	2
#define KEY_LEFT	3
#define KEY_RIGHT	4

#define INIT_LENTH	2

#define STEP		30
#define NEXT		20
#define INIT_SPEED	180
#define WIN		60

extern int key_flag;
extern int speed;

int key_snake(int *key_flag);

extern int init_snake(SCREEN *screen, SDL_Rect *src, SDL_Rect *dst, int num);

extern int creat_screen(SCREEN *screen);

extern int clean_snake(SCREEN *screen, SDL_Rect *all_dst, int snake_lenth);

extern int move_snake(SCREEN *screen, SDL_Rect *src, SDL_Rect *all_dst, int snake_lenth);


#endif
