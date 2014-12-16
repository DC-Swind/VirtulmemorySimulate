#include "Memory.h"
int Memory::change_v(bool x){valid = x; return 0;}
int Memory::change_c(int x){count=x; return 0;}
bool Memory::get_v(){ return valid;}
int Memory::get_count(){ return count;}
int Memory::change_VA_tmp(int x){VA_tmp = x; return 0;}
int Memory::get_VA_tmp(){return VA_tmp;}
