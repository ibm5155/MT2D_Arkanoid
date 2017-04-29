#include "../../mt2d/Object.h"
#include "../../mt2d/String_ansi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char objects_loaded;
extern char **barra_file;
extern char **ball_file;
extern char **block_file;
extern	object *bar1;
extern	object **blocks;
extern  int tot_blocks;
extern	object *ball1;
extern animation_sprites *idle_generic;
extern	sprite_block *bar;
extern	sprite_block *ball;
extern	sprite_block *block;

char **create_mat(int size_x,int size_y);

bool load_memory_game(){
	bool fail=false;

    if(objects_loaded==false){
        //Load generic animation memory
        printf("loading generic animation set memory:");
        idle_generic=Load_Sprite_Animation();
        if(idle_generic){
            printf("loaded\n");
        }else{
            fail=true;
            printf("failed\n");
        }

        //Load memory space for adress name
        printf("loading space for files address...\n");
        printf("loading 1:");
        barra_file=create_mat(9,1);
        if(barra_file){
            printf(":loaded\n");
        }else{
            printf(":failed\n");
            fail=true;

        }

        printf("loading 2:");
        ball_file=create_mat(9,1);
        if(ball_file){
            printf(":loaded\n");
        }else{
            printf(":failed\n");
            fail=true;
        }printf("loading 3:");
        block_file=create_mat(9,1);
        if(block_file){
            printf(":loaded\n");
        }else{
            printf(":failed\n");
            fail=true;
        }

        //Load Adress
        if(!fail){
            strcpy(barra_file[0],"barra.txt");
            strcpy(ball_file[0],"ball.txt");
            strcpy(block_file[0],"block.txt");
            printf("loading sprites adress strings:loaded\n");
        }else{
            printf("loading sprites adress strings:aborting\n");
        }

        //Load sprites
        printf("loading sprites:");
        if(!fail){
            bar=Load_Sprite_Block(barra_file,1);
            if(bar) printf("sprite 1 loaded,");
            else{
                fail=true;
                printf("sprite 1 failed,");
            }
            ball=Load_Sprite_Block(ball_file,1);
            if(ball) printf("sprite 2 loaded,");
            else{
                fail=true;
                printf("sprite 2 failed,");
            }
            block=Load_Sprite_Block(block_file,1);
            if(block) printf("sprite 3 loaded,");
            else{
                fail=true;
                printf("sprite 3 failed,");
            }
        }else printf("aborted:\n");

        //Load objects memory
        printf("loading blocks memory:");
        blocks=(object**)malloc(tot_blocks*sizeof(object*));
        if(blocks) printf("loaded\n");
        else{
            printf("failed\n");
            fail=true;
        }
    }
	return fail;
}

bool load_game_data(){
	int i=0;
	bool fail=false;
	idle_generic->frames_speed[0]=0;
	//Load block objects data
	while(i<tot_blocks-13){
		printf("loading object %d:",i);
		if(objects_loaded==false)
            blocks[i]=Load_Object(SIMPLE_OBJECT,true,1,0,4,1,0,block,idle_generic,0,0,0,0,0);
		if(blocks[i])printf("loaded\n");
		else{
			printf("failed\n");
			fail=true;
		}
		i++;
	}while(i<tot_blocks){
		printf("loading object %d:",i);
		if(objects_loaded==false)
            blocks[i]=Load_Object(SIMPLE_OBJECT,true,2,0,4,1,0,block,idle_generic,0,0,0,0,0);
		if(blocks[i])printf("loaded\n");
		else{
			printf("failed\n");
			fail=true;
		}
		i++;

	}blocks[i-1]->idle->frames_speed[0]=2;
	blocks[i-1]->speed.X=1;
	blocks[i-1]->life=8;
	blocks[i-1]->actual_life=8;
	printf("loading object ball:");
	if(objects_loaded==false)
        ball1=Load_Object(SIMPLE_OBJECT,true,1,1,1,1,0,ball,idle_generic,0,0,0,0,0);
	if(ball1)printf("loaded\n");
	else{
		printf("failed\n");
		fail=true;
	}
	printf("loading bar object:");
	if(objects_loaded==false)
        bar1=Load_Object(SIMPLE_OBJECT,true,1,0,7,1,0,bar,idle_generic,0,0,0,0,0);
	if(bar1)printf("loaded\n");
	else{
		printf("failed\n");
		fail=true;
	}
	printf("setting objects positions:");
	if(!fail){
		//Set Objects position
		set_object_position(3,3,blocks[0]);
		set_object_position(7,3,blocks[1]);
		set_object_position(11,3,blocks[2]);
		set_object_position(15,3,blocks[3]);
		set_object_position(19,3,blocks[4]);
		set_object_position(23,3,blocks[5]);
		set_object_position(27,3,blocks[6]);
		set_object_position(31,3,blocks[7]);
		set_object_position(35,3,blocks[8]);
		set_object_position(39,3,blocks[9]);
		set_object_position(43,3,blocks[10]);
		set_object_position(47,3,blocks[11]);
		set_object_position(51,3,blocks[12]);
		set_object_position(55,3,blocks[13]);
		set_object_position(59,3,blocks[14]);
		set_object_position(63,3,blocks[15]);
		set_object_position(67,3,blocks[16]);
		set_object_position(71,3,blocks[17]);
		set_object_position(12,6,blocks[18]);
		set_object_position(17,6,blocks[19]);
		set_object_position(22,6,blocks[20]);
		set_object_position(27,6,blocks[21]);
		set_object_position(32,6,blocks[22]);
		set_object_position(37,6,blocks[23]);
		set_object_position(42,6,blocks[24]);
		set_object_position(47,6,blocks[25]);
		set_object_position(52,6,blocks[26]);
		set_object_position(57,6,blocks[27]);
		set_object_position(57,6,blocks[28]);
		set_object_position(62,6,blocks[29]);
		set_object_position(67,6,blocks[30]);
		printf("completed:\n");
	}else printf("aborted:\n");
	return fail;
}
//If the game get restarted
void reload_data(){
	int i=0;
	while(i<tot_blocks-13){
		blocks[i]->actual_life=1;
		blocks[i]->life=1;
		i++;
	}while(i<tot_blocks){
		blocks[i]->actual_life=2;
		blocks[i]->life=2;
		i++;
	}blocks[i-1]->idle->frames_speed[0]=2;
	blocks[i-1]->speed.X=1;
	blocks[i-1]->life=8;
	blocks[i-1]->actual_life=8;
	printf("loading object ball:");
	printf("setting objects positions:");
}

char **create_mat(int size_x,int size_y){
	char **X=0;
	int i=0;
//	printf("\n | create mat(int %d,int %d);\n",size_x,size_y);
	if(size_y<=0 || size_x<=0){
		printf("ERROR, file must be larger than zero\n");
	}else{
		X=(char**)malloc((size_y+1)*sizeof(char*));
		if(X){
			while(i<size_y){
//				printf("\nwhile(%d<=%d){\n",i,size_y);
				X[i]=(char*)malloc(size_x*sizeof(char));
				printf("X[%d]=%d ",i,(int)X[i]);
				i++;
//				printf("%d++\n}",i-1);
			}
		}
//		printf("return X:%d\n",X);
	}return X;
}
