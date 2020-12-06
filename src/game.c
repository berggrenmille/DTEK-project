#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "entity.h"


extern int globaltime;
extern struct entity player;
extern struct entity easy_car;
extern struct entity medium_car;
extern struct entity hard_car;

extern void delay(int ms);
extern void update_logic(int dTime);

struct entity enemies[10];

int score = 0;
int diff = 0;

void init_world()
{
    if(diff == 0)
    {
        int i;
        for( i = 0; i<10; ++i)
        {
            
            enemies[i] = easy_car;
            //enemies[i].x = rand() % 100;
          //  enemies[i].y = (rand() % (32-enemies[i].h)) + enemies[i].h;
          enemies[i].x = 15.;
          enemies[i].y = 15.;
        }
    }else if(diff == 1)
    {
        /* code */
    }
    else if(diff == 2)
    {

    }
    
}


void render_world()
{
    int i;
    for(i = 0; i<10; ++i)
    {
        image_to_buffer(enemies[i].x,enemies[i].y,enemies[i].w,enemies[i].h,enemies[i].image);
    }
}
void render_player()
{
    clear_buffer();
    image_to_buffer(player.x,player.y,player.w, player.h, player.image);

}
void game_loop()
{
    int isRunning = 0;
    int prevTime = 0;
    int currentTime = 0;
    int delta = 0;
    int diffBtn = 0;
    for(;;)
    {
        //End menu
        while(!isRunning && score > 0)
        {
            display_string(0, "GAME OVER");
            display_update();
        }        
        //Main menu
        while(!isRunning)
        {
            display_string(0, "Extreme Racer 9000");
            display_string(1, "1. play");
            display_string(2, "2. high score");
            if(diff == 0)
                display_string(3, "3. diff: easy");
            if(diff == 1)
                display_string(3, "3. diff: medium");
            if(diff == 2)
                display_string(3, "3. diff: hard");
            display_update();
            //Check play btn
            if(get_btns(1))
            {
                srand(globaltime);
                init_world();
                isRunning = 1;
            }
            //Check diff btn
            if(get_btns(3) && !diffBtn)
            {
                diffBtn = 1; //Prevent difficulty to change until button is released
                if(diff == 2)
                    diff = 0;
                else
                    ++diff;
            }
            else if(!get_btns(3))
                diffBtn = 0; //Allow difficulty to be changed
        }
        
        //Game
       // delay(32);
        update_logic(delta);
        render_world();
        display_buffer();
        render_player();
        //Calc deltatimer
        prevTime = currentTime;
        currentTime = globaltime;
        delta = currentTime - prevTime;
    }

    
    //
}