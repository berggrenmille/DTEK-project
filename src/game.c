#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "entity.h"


extern int globaltime;
extern struct entity player;

extern void delay(int ms);
extern void update_logic(int dTime);

struct entity enemies[10];
int currentenemies = 0;

int score = 0;

void spawnenemy()
{

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
    display_buffer();
}
void game_loop()
{
    int isRunning = 0;
    int prevTime = 0;
    int currentTime = 0;
    int delta = 0;
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
            display_string(3, "3. Diff: easy");
            display_update();
            if(get_btns(1))
                isRunning = 1;

        }
        srand(globaltime);
        //Game
       // delay(32);
        update_logic(delta);
        render_world();
        render_player();
        //Calc deltatimer
        prevTime = currentTime;
        currentTime = globaltime;
        delta = currentTime - prevTime;
    }

    
    //
}