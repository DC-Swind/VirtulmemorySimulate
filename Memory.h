#ifndef _MEMORY_H_
#define _MEMORY_H_

class Memory{
	bool valid;
	int count;
	int VA_tmp;
public:
	int change_v(bool x);
	int change_c(int x);
	int change_VA_tmp(int x);
	int get_VA_tmp();
	bool get_v();
	int get_count();
};
#endif
