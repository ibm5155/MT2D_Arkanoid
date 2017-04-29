#include "bar.h"
#include "../../mt2d/Object.h"
#include "../../mt2d/Window_core.h"

extern	object *bar1;

void move_bar(int direction){
	if(direction==MOVE_LEFT){
		if(bar1->screen_position.X>0)
			move_object(MOVE_LEFT,bar1);
	}else if(direction==MOVE_RIGHT){
		if(bar1->screen_position.X+bar1->size.X<MAX_HOR-1)
			move_object(MOVE_RIGHT,bar1);
	}else if(direction==MOVE_DOWN){
		set_object_position(MAX_HOR/2,bar1->screen_position.Y,bar1);
	}

}
