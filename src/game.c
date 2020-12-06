#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "entity.h"


extern struct entity player;
extern struct entity easy_car;
extern struct entity medium_car;
extern struct entity hard_car;

extern int globaltime;
extern void delay(int ms);
extern void update_logic(int dTime);

struct entity enemies[10];

struct highscore
{
    int score;
    char initials[3];
};

struct highscore highscorelist[] = 
{
    {
        0,{'_','_','_'}
    },
    {
        0,{'_','_','_'}
    },
    {
        0,{'_','_','_'}
    }
};

int score = 0;
int diff = 0;

int isRunning = 0;
int prevTime = 0;
int currentTime = 0;
int delta = 0;

void init_world()
{
    currentTime = globaltime;
    prevTime = globaltime;
    if(diff == 0)
    {
        int i;
        for( i = 0; i<10; ++i)
        {
          enemies[i] = easy_car;
          enemies[i].x = -15.;
          enemies[i].y = -15.;
        }
    }else if(diff == 1)
    {
        int i;
        for( i = 0; i<10; ++i)
        {
          enemies[i] = medium_car;
          enemies[i].x = -15.;
          enemies[i].y = -15.;
        }
    }
    else if(diff == 2)
    {
        int i;
        for( i = 0; i<10; ++i)
        {
          enemies[i] = hard_car;
          enemies[i].x = -15.;
          enemies[i].y = -15.;
        }
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
    int newx;
    int newy;
  
     int i, j, k = 0;

    //for each row
    for(i = 0; i < player.h; ++i) 
    {

        //pixel y pos
        newy = player.y + i;
        //Check if pixel is outside screenspace
        if(newy < 0)
        continue;
        if(newy >= 32)
        break;
        //For each column
        for(j = 0; j < player.w; ++j)
        {
        //pixel x pos
        newx = player.x + j;
        //Check if pixel is outside screenspace
        if(newx < 0)
            continue;
        if(newx >= 128)
            break;
        if(imageBuffer[newy*128 + newx] && player.image[i*player.w+j])
            isRunning = 0;
        }
    }

    image_to_buffer(player.x,player.y,player.w, player.h, player.image);

}
void game_loop()
{

    int diffBtn = 0;
    for(;;)
    {
        //End menu
        while(!isRunning && score > 0 && !get_btns(1))
        {
            display_string(0, "GAME OVER");
            display_string(1, "SCORE (s * diff)");
            display_string(2, itoaconv(score * (diff+1) / 100));
            display_string(3, "1. to continue");
            display_update();
    
            //high score menu
            if(get_btns(1))
            {
                while(get_btns(1)){}
                char initials[]={'_', '_','_'};
                while(!get_btns(1) || (initials[0] == '_' || initials[0] == '_' || initials[0] == '_'))
                {
                    display_string(0, "save highscore");
                    display_string(1,initials);
                    display_string(2,"2. 3. 4. to edit");
                    display_string(3, "1. save");
                    display_update();
                    if(get_btns(4))
                    {
                        while(get_btns(4)){} // lock
                        if(initials[0] == '_' || initials[0] == 'z')
                            initials[0] = 'a';
                        else
                            initials[0]++;
                    }

                    if(get_btns(3))
                    {
                        while(get_btns(3)){} // lock
                        if(initials[1] == '_' || initials[1] == 'z')
                            initials[1] = 'a';
                        else
                            initials[1]++;
                    }

                    if(get_btns(2))
                    {
                        while(get_btns(2)){} // lock
                        if(initials[2] == '_' || initials[2] == 'z')
                            initials[2] = 'a';
                        else
                            initials[2]++;
                    }
                }
                //Save high score
                if(highscorelist[0].score < score * (diff+1) / 100)
                {
                    highscorelist[0].score = score * (diff+1) / 100;
                    highscorelist[0].initials[0] = initials[0];
                    highscorelist[0].initials[1] = initials[1];
                    highscorelist[0].initials[2] = initials[2];
                }
                else if(highscorelist[1].score < score * (diff+1) / 100)
                {
                    highscorelist[1].score = score * (diff+1) / 100;
                    highscorelist[1].initials[0] = initials[0];
                    highscorelist[1].initials[1] = initials[1];
                    highscorelist[1].initials[2] = initials[2];
                }
                else if(highscorelist[2].score < score * (diff+1) / 100)
                {
                    highscorelist[2].score = score * (diff+1) / 100;
                    highscorelist[2].initials[0] = initials[0];
                    highscorelist[2].initials[1] = initials[1];
                    highscorelist[2].initials[2] = initials[2];
                }
                score = 0;
            }
        }        
        //Main menu
        while(!isRunning && score == 0 && !get_btns(1))
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

            if(get_btns(2))
            {
                while(!get_btns(1))
                {
                    char h1[24] = "1.";
                    char h2[24] = "2.";
                    char h3[24] = "3.";
                    strcat(h1, highscorelist[0].initials);
                    strcat(h1, ": ");
                    strcat(h1, itoaconv(highscorelist[0].score));

                    strcat(h2, highscorelist[1].initials);
                    strcat(h2, ": ");
                    strcat(h2, itoaconv(highscorelist[1].score));

                    strcat(h3, highscorelist[2].initials);
                    strcat(h3, ": ");
                    strcat(h3, itoaconv(highscorelist[2].score));
                    display_string(0, "1. back");

                    display_string(1, &h1[0]);
                    display_string(2, &h2[0]);
                    display_string(3, &h3[0]);
                    display_update();
                }
            }

            //Check diff btn
            if(get_btns(3))
            {
                while(get_btns(3)){} //Prevent difficulty to change until button is released
                if(diff == 2)
                    diff = 0;
                else
                    ++diff;
            }

        }
        
        //Game
       // delay(32);
        if(isRunning)
        {
            update_logic(delta); 
            clear_buffer();
            render_world();
            render_player();
            display_buffer();
    
            //Calc deltatimer
            prevTime = currentTime;
            currentTime = globaltime;
            delta = currentTime - prevTime;

	    //Pausing
	    if(get_swts(1)){
		while(get_swts(1)){
			display_string(0, "GAME PAUSED");
			display_string(1, "CURRENT SCORE:");
			display_string(2, itoaconv(score * (diff+1) / 100));
			display_string(3, "SW1 TO UNPAUSE");
			display_update();
		}
		int pausedTime = globaltime - currentTime;
		prevTime += pausedTime;
		currentTime += pausedTime;
	    }
        }
    }

    
    //
}
