#include <stdio.h>
#include <stdlib.h>
#include "../../mt2d/Object.h"
#include "../../mt2d/Io_FILE.h"
#include "Load_Game_Memory.h"
#include "../../MT2D/Audio_core.h"
#include "game.h"
#include "../../mt2d/building_functions/generic_menu.h"
#include "../../mt2d/building_functions/generic_string_reader.h"

    char objects_loaded=false;
	char **barra_file=0;
	char **ball_file=0;
	char **block_file=0;
	object **blocks=0;
	int tot_blocks=32;
	int total_score=0;
	bool nosound=false;
	object *ball1=0;
	object *bar1=0;
	sprite_block *bar=0;
	sprite_block *ball=0;
	sprite_block *block=0;
	animation_sprites *idle_generic=0;

void save_score(char *name, int score);


int main(int arg){
	int i=0;
	int menu=4;
	int out_loop=false;
	char *name;
	//Start SDL Sound System
	MT2D_Start_Audio_System();
	i=load_memory_game();
	if(i){
		printf("the game has encountered a problem with the memory, aborting...\n");
		system("pause");
	}else{
		i=load_game_data();
		if(i){
			printf("the game has encountered a problem with the memory, aborting...\n");
			system("pause");
		}
	}
	printf("MT2D CREATED BY IBM5155\n");
	if(!i){
		while(!out_loop){
			//system("cls");
			if(menu==1){
				game();
				menu=generic_menu("Game over, what would you like to do",1,5,2,0,true,'.',175,"Play Again","Save Score","Show Scores","Restart","Exit",0,0,0,0,0,0,0,0,0,0,0,0,0,5);
				if(menu==1 || menu==4){
					reload_data();
					total_score=0;
				}
			}else if(menu==2){
				name=get_string_popup("Type your name");
				save_score(name,total_score);
				out_loop=true;
			}else if(menu==4){
				title();
				game();

				menu=generic_menu("Game over, what would you like to do",1,5,2,0,true,'.',175,"Play Again","Save Score","Show Scores","Restart","Exit",0,0,0,0,0,0,0,0,0,0,0,0,0,5);
				if(menu==1 || menu==4){
					reload_data();
					total_score=0;
				}
			}else out_loop=true;
		}
		MT2D_Close_Audio_System();
	}
//	print_popup("SYSTEM PASUE");
    return 0;
}

void save_score(char *name, int score){
	FILE *x;
	x=open_file("score.txt","a");
	fprintf(x,"NAME:%s *SCORE:%d\n",name,score);
	fclose(x);
}
