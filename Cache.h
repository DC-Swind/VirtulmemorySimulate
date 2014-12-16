#ifndef _CACHE_H_
#define _CACHE_H_
class Cache{
	bool valid;
	int tag;
	int count;
public:
	int change_v(bool x);
	int change_tag(int x);
	int change_count(int x);

	bool get_v();
	int get_tag();
	int get_count();
};
#endif
