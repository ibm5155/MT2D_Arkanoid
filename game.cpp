#include "../../MT2D/Audio_core.h"
#include "../../mt2d/Window_core.h"
#include "../../mt2d/Object.h"
#include "../../mt2d/Keyboard.h"
#include "../../mt2d/system_calls.h"
#include "../../mt2d/building_functions/generic_line.h"
#include "../../mt2d/building_functions/display_popup.h"
#ifdef _WIN32
#include <Windows.h>
#endif
#include "bar.h"
#include "Ball.h"

extern	object *bar1;
extern	object **blocks;
extern  int tot_blocks;
extern int total_score;
extern	object *ball1;
sprite *titlepic=0;
sprite *engine=0;

int level=0;
int prepare_next_level(){
	int i=0;
	return i;
}

void title(){
	int mess=0;
	int i=0;
	int linea[5]={20,24,21,23,22};
	int linea_color[5]={176,176,177,177,178};
	int lineb[5]={7,11,8,10,9};
	int lineb_color[5]={176,176,177,177,178};
	engine=Load_Sprite("engine_logo.txt");
	printf("logo loaded\n");
	titlepic=Load_Sprite("title.txt");
	printf("title loaded\n");
	MT2D_Play_Music("title.ogg");
	while(true == false/*!Keyboard_touched()*/){
		clear_display();
		while(i<5){
			linea[i]++;
			if(linea[i]==25)linea[i]=0;
			lineb[i]--;
			if(lineb[i]==-1)lineb[i]=24;
			line_draw_vertical(linea[i],linea_color[i]);
			line_draw_vertical(lineb[i],lineb_color[i]);
			i++;
		}i=0;
		put_sprite_on_window(titlepic,DISPLAY_WINDOW1,1,2);
		put_sprite_on_window(engine,DISPLAY_WINDOW1,60,18);
		if(mess>=20){
			insert_string_on_display("press any key to play",20,30,DISPLAY_WINDOW1);
			mess++;
			if(mess==40)mess=0;
		}else mess++;
		print_display(DISPLAY_WINDOW1);
		goto_topscreen();
		Delay(40);
	}
}


int game(){
	int movable_block_pos_x=2;
	int ballspeed=30000;
	int ball_cnt=0;
	int i=0;
	int j=0;

	int exit_while=false;
	int keyx;
	int endgame=false;
	MT2D_Play_Music("game.ogg");

	set_object_position(44,19,ball1);
	set_object_position(40,20,bar1);
	set_object_position(2,12,blocks[tot_blocks-1]);
	while(exit_while==false){
		//Clear Display
		clear_display();
		//Put the objects on screen memory
		i=0;
		if(blocks[tot_blocks-1]->idle->frames_speed[0]==movable_block_pos_x){
			if(blocks[tot_blocks-1]->screen_position.X + blocks[tot_blocks-1]->size.X== MAX_HOR-1 - blocks[tot_blocks-1]->size.X)
				blocks[tot_blocks-1]->speed.X=-1;
			else if(blocks[tot_blocks-1]->screen_position.X==2)
				blocks[tot_blocks-1]->speed.X=1;
			blocks[tot_blocks-1]->screen_position.X+=blocks[tot_blocks-1]->speed.X;
			movable_block_pos_x=0;

		}else movable_block_pos_x++;
		while(i<tot_blocks){//Put all blocks on sceen
		put_object_on_window(blocks[i],DISPLAY_WINDOW1);
			i++;
		}
		put_object_on_window(ball1,DISPLAY_WINDOW1);
		put_object_on_window(bar1,DISPLAY_WINDOW1);
		//Print screen memory on screen
		insert_string_on_display("SCORE:",0,48,DISPLAY_WINDOW1);
		insert_number_on_display(total_score,0,54,DISPLAY_WINDOW1);
		print_display(DISPLAY_WINDOW1);
		if(ballspeed==ball_cnt){
			endgame=ball_acelerate();
			ball_cnt=0;
		}else{
			ball_cnt++;
		}//goto_topscreen();
		if(endgame){
			MT2D_Play_Music("nomusic.wav");
			Delay(1000);
			MT2D_Play_Music("lose_music.wav");
			exit_while=true;
		}
		if(Keyboard_touched()){
			keyx=Keyboard_keytouched();
			if(keyx==_key){
				keyx=Keyboard_keytouched();
				switch(keyx){
				case key_left:
					move_bar(MOVE_LEFT);
					break;
				case key_right:
					move_bar(MOVE_RIGHT);
					break;
				case key_down:
					move_bar(MOVE_DOWN);
					break;
				}
			}
		}
		i=0;
		j=0;
		while(i<tot_blocks){
			if(blocks[i]->actual_life==0)j++;
			i++;

		}if(j==tot_blocks-1){
			level++;
			while(i<tot_blocks){
				blocks[i]->actual_life=level;
				blocks[i]->life=level;
				i++;
			}
		}
		Delay(40);
	}return exit_while;
}
