#pragma once
#include "main_header.h"
#include "read_write.h"
#include <map>
class type;

#define O_LOAD(func_name)		char *	(func_name) (char *parent_space)
#define O_UPDATE(func_name)		bool	(func_name) (char *o, float dt)
#define O_RENDER(func_name)		void	(func_name) (char *o, bool *repeat)
#define O_DEL(func_name)		void	(func_name) (char *o)
#define O_RESET(func_name)		void	(func_name) (char *o, char *source, char *parent_space)
#define O_STORE(func_name)		void	(func_name) (char *o, char *destination)

typedef O_LOAD(*o_load);
typedef O_UPDATE(*o_update);
typedef O_RENDER(*o_render);
typedef O_DEL(*o_del);
typedef O_RESET(*o_reset);
typedef O_STORE(*o_store);

struct std_obj_functions {
	std_obj_functions (o_load l, o_update u, o_render r, o_del d, o_reset res = NULL, o_store s = NULL, bool reset_same_part_ = false) :
		load (l), update (u), render (r), del (d), reset (res), store (s), reset_same_part (reset_same_part_) {};
	std_obj_functions (o_load l, o_del d) :
		load (l), update (NULL), render (NULL), del (d), reset (NULL), store (NULL), reset_same_part (false) {};
	o_load load;
	o_update update;
	o_render render;
	o_del del;
	o_reset reset;
	o_store store;
	bool reset_same_part;
};

#define O_DECL(type_, object_pointer_)			type_ *object_pointer_ = (type_ *) o
#define O_SOURCE(type_, object_pointer_)		type_ *object_pointer_ = (type_ *) source
#define O_DESTINATION(type_, object_pointer_)	type_ *object_pointer_ = (type_ *) destination

extern O_LOAD(no_load);

struct my_type_info {
	my_type_info () : num(0), index_in_fp_array (0) {}
	my_type_info (int number, int index) : num (number), index_in_fp_array (index) {}
	int index_in_fp_array;
	int num;
};

extern std::map <std::string, my_type_info> min_type_info;