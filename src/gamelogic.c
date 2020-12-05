#include "mipslab.h"
#include "entity.h"
#include "entity.c"

extern struct entity player;
void update_logic(int dTime){
	float speed = dTime / 100;	
	if(get_btns(1)){
		player.y -= speed;
	        if(player.y < 0)
 			player.y = 0;			
	}
	if(get_btns(2)){
		player.x -= speed;
	        if(player.x < 0)
 			player.x = 0;			
	}
	if(get_btns(3)){
		player.x += speed;
	        if(player.x > 128 - player.w)
 			player.x = 128 - player.w;			
	}
	if(get_btns(4)){
		player.y += speed;
	        if(player.y > 32 - player.h)
 			player.y = 32 - player.h;			
	}
}
