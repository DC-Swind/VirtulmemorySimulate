#include "TLB.h"
int TLB::change_v(bool x){valid=x; return 0;}
bool TLB::get_v(){return valid;}
int TLB::get_PA(){return PA;}
int TLB::get_tag(){return tag;}
int TLB::get_count(){return count;}
int TLB::change_c(int x){count=x; return 0;}
int TLB::change_pa(int x){PA=x; return 0;}
int TLB::change_tag(int x){tag=x; return 0;}
