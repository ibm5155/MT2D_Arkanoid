#include <stdio.h>
#include <stdlib.h>
#include "../../mt2d/Object.h"
#include "../../mt2d/Window_core.h"
#include "../../MT2D/Audio_core.h"

extern	object *bar1;
extern	object **blocks;
extern  int tot_blocks;
extern	object *ball1;
extern  int total_score;
#define WALL_NONE 0
#define WALL_UP 1
#define WALL_DOWN 2
#define WALL_LEFT 3
#define WALL_RIGHT 4
#define BALL_DEATH -1
int ball_wall_colision(){
//0 NONE
//1 WALL UP
//2 WALL DOWN
//3 WALL LEFT
//4 WALL RIGHT
	int wall=0;
	if(ball1->screen_position.X+ball1->speed.X >= MAX_HOR-1){
		MT2D_Play_Audio("touch.wav");
		wall=WALL_RIGHT;
	}else if(ball1->screen_position.X+ball1->speed.X < 0){
		MT2D_Play_Audio("touch.wav");
		wall=WALL_LEFT;
	}else if(ball1->screen_position.Y+ball1->speed.Y < 0){
		wall=WALL_UP;
		MT2D_Play_Audio("touch.wav");
	}else if(ball1->screen_position.Y+ball1->speed.Y >= MAX_VER){
		wall=WALL_DOWN;
		MT2D_Play_Audio("end.wav");
	}return wall;
}

int ball_colision_detect(){
	int i=0;
	int j=0;
	int block_colided=0;
	i=ball_wall_colision();
	if(i){//Wall colision, update X/Y aceleration
		switch(i){
			case WALL_RIGHT:
				ball1->speed.X*=-1;
				i=0;
				break;
			case WALL_LEFT:
				ball1->speed.X*=-1;
				i=0;
				break;
			case WALL_UP:
				ball1->speed.Y*=-1;
				i=0;
				break;
			case WALL_DOWN:
				i=BALL_DEATH;
				break;
		}
	}else{//Check for object colision
		while(j<tot_blocks){
			if(blocks[j]->actual_life>0){
				if(ball1->screen_position.Y+ball1->speed.Y==blocks[j]->screen_position.Y){
					if(ball1->screen_position.X + ball1->speed.X == blocks[j]->screen_position.X){
						ball1->speed.Y=ball1->speed.Y*-1;
						MT2D_Play_Audio("touch2.wav");
						total_score+=100;
						blocks[j]->actual_life--;
						j=tot_blocks;
						block_colided=true;
					}else if(ball1->screen_position.X+ball1->speed.X==blocks[j]->screen_position.X+blocks[j]->size.X){
						ball1->speed.Y=ball1->speed.Y*-1;
						MT2D_Play_Audio("touch2.wav");
						total_score+=100;
						blocks[j]->actual_life--;
						j=tot_blocks;
						block_colided=true;
					}else if(ball1->screen_position.X+ball1->speed.X>blocks[j]->screen_position.X && ball1->screen_position.X+ball1->speed.X<blocks[j]->screen_position.X+blocks[j]->size.X){
						ball1->speed.Y=ball1->speed.Y*-1;
						MT2D_Play_Audio("touch2.wav");
						total_score+=100;
						blocks[j]->actual_life--;
						j=tot_blocks;
						block_colided=true;
					}
				}
			}
			j++;
		}
//CHECK BAR COLISION
	}if(ball1->screen_position.Y + ball1->speed.Y  == bar1->screen_position.Y){
		if(ball1->screen_position.X + ball1->speed.X >= bar1->screen_position.X && ball1->screen_position.X + ball1->speed.X <= bar1->screen_position.X + bar1->size.X){
			ball1->speed.Y=-1;
			if(ball1->screen_position.X + ball1->speed.X <= bar1->screen_position.X + (bar1->size.X)/2){
				if(ball1->screen_position.X + ball1->speed.X == bar1->screen_position.X){
					ball1->speed.X=-2;
				}else// if(ball1->speed.X==1)
					ball1->speed.X=-1;
			}else{
				if(ball1->screen_position.X + ball1->speed.X == bar1->screen_position.X + bar1->size.X -1){
					ball1->speed.X=2;
				}else{// if(ball1->speed.X==-1){
					ball1->speed.X=1;
				}
			}
			MT2D_Play_Audio("bar_touch.wav");
			block_colided=true;
		}
	}
	return i;
}

bool ball_acelerate(){//0 didnt lost the ball, 1 lost the ball
	int i=0;
	i=ball_colision_detect();
	ball1->screen_position.X+=ball1->speed.X;
	ball1->screen_position.Y+=ball1->speed.Y;
	if(i==-1){
		i=true;
	}
	if(i==1){
		i=i;
	}
	return i;
}
