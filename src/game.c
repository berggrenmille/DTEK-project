#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "entity.h"


extern int globaltime;
extern struct entity player;

extern void delay(int ms);
extern void update_logic(int dTime);



void render_world()
{

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
        render_player();
        //Calc deltatimer
        prevTime = currentTime;
        currentTime = globaltime;
        delta = currentTime - prevTime;
    }

    
    //
}