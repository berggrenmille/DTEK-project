#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "entity.h"

extern struct entity player;
extern int score;
int interval = 0;

void update_logic(int dTime){
	float speed = (float)dTime * 5 / 100.0;	
	interval += dTime;
	if(get_btns(1)){
		player.x += speed;
	        if(player.x > 128 - player.w)
 			player.x = 128 - player.w;
	}
	if(get_btns(2)){
		player.x -= speed;
	        if(player.x < 0)
 			player.x = 0;			
	}
	if(get_btns(3)){
		player.y += speed;
	        if(player.y > 32 - player.h)
 			player.y = 32 - player.h;
	}
	if(get_btns(4)){
		player.y -= speed;
	        if(player.y < 0)
 			player.y = 0;
	}

	//Move the enemies
	int i;
	for(i = 0; i < 10; i++)
		enemies[i].x -= speed*(score+1000)/10000;

	//Try to randomly spawn an enemy after 2 seconds
	if(interval > 2000){
		interval = 0;
		int randEnemy = rand() % 10;
		if(enemies[randEnemy].x + enemies[randEnemy].w < 0){
			enemies[randEnemy].x = 140;
			enemies[randEnemy].y = rand() % (33 - enemies[randEnemy].h);
		}
	}
}
