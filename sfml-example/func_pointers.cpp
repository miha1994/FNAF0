#include "func_pointers.h"
#include "o_control.h"
#include "o_picture.h"
#include "o_button.h"
#include "o_rooms.h"

std_obj_functions *fp_array [] = {
	&control_f,			//0
	&picture_f,			//1
	&button_f,			//2
	&rooms_f			//3
};