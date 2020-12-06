#include "entity.h"

uint8_t player_image[] = 
	{	
		1,0,0,1,
		1,1,1,1,
		1,1,1,1,
		1,0,0,1,
	};
uint8_t medium_image[] = 
	{	
			1,0,1,1,0,1,
        	1,1,1,1,1,1,
        	1,1,1,1,1,1,
        	1,0,1,1,0,1
	};

uint8_t hard_image[] = 
	{	
		0,1,1,0,0,1,1,0,
        	0,1,1,0,0,1,1,0,
        	1,1,1,1,1,1,1,1,
        	1,1,1,1,1,1,1,1,
        	0,1,1,0,0,1,1,0,
        	0,1,1,0,0,1,1,0
	};

struct entity player =
{
	1.0,16.,4,4,player_image
};

struct entity easy_car =
{
	150.,16.,4,4,player_image
};

struct entity medium_car =
{
	10.,16.,6,4,medium_image

};

struct entity hard_car =
{
	150.,16.,8,6, hard_image

};
