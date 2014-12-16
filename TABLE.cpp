#include "TABLE.h"
int TABLE::change_v(bool x){valid = x; return 0;}
int TABLE::change_pa(int x){PA=x; return 0;}
bool TABLE::get_v(){ return valid;}
int TABLE::get_PA(){ return PA;}
