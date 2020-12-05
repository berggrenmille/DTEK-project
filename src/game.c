#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include "entity.h"

extern int globaltime;
extern struct entity player;

extern void delay(int ms);
extern void update_logic(int dTime);



void render_world()
{

}
void renderPlayer()
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
        while(isRunning)
        {

        }

        //Game
       // delay(32);
        update_logic(delta);
        renderPlayer();
        prevTime = currentTime;
        currentTime = globaltime;
        delta = currentTime - prevTime;
    }
    srand(globaltime);
    
    //
}