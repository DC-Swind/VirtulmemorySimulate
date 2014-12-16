#ifndef _FUNC_H_
#define _FUNC_H_
#include <iostream>
using namespace std;
int cal_2(int x){
	int tmp=1;
	while (x>0){ tmp*=2; x--;}
	return tmp;
}
long long Fto2(char* x){
	long long tmp=0;
	for (int i=0; i<8; i++){
		tmp*=16;
		switch (x[i]){
		case '0': tmp+=0; break;
		case '1': tmp+=1; break;
		case '2': tmp+=2; break;
		case '3': tmp+=3; break;
		case '4': tmp+=4; break;
		case '5': tmp+=5; break;
		case '6': tmp+=6; break;
		case '7': tmp+=7; break;
		case '8': tmp+=8; break;
		case '9': tmp+=9; break;
		case 'a': tmp+=10; break;
		case 'b': tmp+=11; break;
		case 'c': tmp+=12; break;
		case 'd': tmp+=13; break;
		case 'e': tmp+=14; break;
		case 'f': tmp+=15; break;
		}
	}
	return tmp;
}
#endif
