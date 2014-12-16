#ifndef _TLB_H_
#define _TLB_H_
class TLB{
	int tag;
	int PA;
	//bool dirty;
	bool valid;
	int count;
public:
	//TLB();
	int change_v(bool x);
	int change_c(int x);
	int change_pa(int x);
	int change_tag(int x);
	bool get_v();
	int get_PA();
	int get_tag();
	int get_count();
	

};
#endif
