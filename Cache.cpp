#include "Cache.h"	
int Cache::change_v(bool x){valid = x; return 0;}
int Cache::change_tag(int x){tag = x; return 0;}
int Cache::change_count(int x){count = x; return 0;}

bool Cache::get_v(){return valid;}
int Cache::get_tag(){return tag;}
int Cache::get_count(){return count;}
