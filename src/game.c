#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include "entity.h"

extern int globaltime();
extern struct entity player;
extern void update_logic(int dTime);

extern void renderPlayer()
{
    image_to_buffer(player.x,player.y,player.w, player.h, player.image);
    display_buffer();
}
void game_loop()
{
    int isRunning = 0;
    for(;;)
    {
        //Main menu
        while(0)
        {

        }
        update_logic(100);
        renderPlayer();
    }
    
    //
}