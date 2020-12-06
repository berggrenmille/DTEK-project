#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "entity.h"

extern struct entity player;

void update_logic(int dTime){
	float speed = (float)dTime * 5 / 100.0;	
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
}
