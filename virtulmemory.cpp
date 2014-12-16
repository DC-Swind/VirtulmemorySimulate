#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Cache.h"
#include "TLB.h"
#include "TABLE.h"
#include "Memory.h"
#include "func.h"
#include "heap_var.h"
#include <time.h>
ofstream fout("../traces/ans.txt");
using namespace std;
int init()
{
	tlb_hit = tlb_miss = table_hit = table_miss = cache_hit = cache_miss =0;
	for (int i=0; i<tlb_size; i++) { tlb[i].change_v(false); tlb[i].change_c(0);}
	for (int i=0; i<table_size; i++) table[i].change_v(false);
	for (int i=0; i<memory_size; i++) { memory[i].change_v(true); memory[i].change_c(0);}
	for (int i=0; i<cache_size; i++){cache[i].change_v(false); cache[i].change_count(0);}
	return 0;
}
int search_table(int va)
{
	if (table[va].get_v()) { table_hit++; return table[va].get_PA(); }               //hit
	//miss
	table_miss++;
	int max=-10; int j; bool flag = false;
	for (int i=0; i<memory_size; i++)if (memory[i].get_v() && !flag){                //内存找到空行
		memory[i].change_v(false);
		memory[i].change_VA_tmp(va);												 //为了优化程序，存储了虚拟页号
		table[va].change_pa(i);
		table[va].change_v(true);
		memory[i].change_c(0);
		flag =true;
	}else{                                                                           //LRU计数比较
		if (memory[i].get_count()>max){
			max=memory[i].get_count();
			j=i;
		}
		memory[i].change_c(memory[i].get_count()+1);
	}
	if (!flag){																		//miss  替换
		table[memory[j].get_VA_tmp()].change_v(false);                              //将原来页表中的项清零
		memory[j].change_VA_tmp(va);                                   
		memory[j].change_c(0);
		memory[j].change_v(false);
		table[va].change_v(true);
		table[va].change_pa(j);
	}
	return table[va].get_PA();
}
int search_tlb(int va)
{
	int pa = -1;    //返回值
	int max = -10; int j;
	int group = va & mask_4;
	int tag = va >> 4;
	for (int i=group*4; i<group*4+4; i++) if (pa == -1 && tlb[i].get_v() && tlb[i].get_tag() == tag){   //hit
		tlb[i].change_c(0);              //将count置零
		pa = tlb[i].get_PA();            //获得物理地址页框号
		tlb_hit++;
	}else{
		tlb[i].change_c(tlb[i].get_count()+1);     //将其余的LRU计数+1
		if (tlb[i].get_count()>max){
			max = tlb[i].get_count();              //记录最大值
			j=i;
		}
	}
	if (pa == -1){                //miss
		tlb_miss++;
		pa = search_table(va);    //进入内存，查找table
		tlb[j].change_c(0);       //替换
		tlb[j].change_pa(pa);
		tlb[j].change_tag(tag);
		tlb[j].change_v(true);
	}
	return pa;
}
int search_cache(int pa)
{
	int max=-10; int j; bool flag=false;
	int group = (pa>>block_size) & mask_9;                          //物理地址分解为组号
	int tag = (pa>>(block_size+9))& mask_10;						//tag
	for (int i=group*4; i<group*4+4; i++) if (!flag && cache[i].get_v() && cache[i].get_tag() == tag){ //hit
		cache[i].change_count(0);
		cache_hit++;
		flag = true;
	}else{															//LRU计数比较
		if (cache[i].get_count()>max){
			max = cache[i].get_count();
			j=i;
		}
		cache[i].change_count(cache[i].get_count()+1);
	}
	if (!flag){                                                     //miss
		cache_miss++;
		cache[j].change_count(0);
		cache[j].change_tag(tag);
		cache[j].change_v(true);
	}
	return 0;
}
int read()
{
	char *file_way[5];
	file_way[0]="../traces/gcc.trace";
	file_way[1]="../traces/gzip.trace";
	file_way[2]="../traces/mcf.trace";
	file_way[3]="../traces/swim.trace";
	file_way[4]="../traces/twolf.trace";
	for (int i=0;i<5;i++){
		cout<<"Start "<<file_way[i]<<endl;
		fout<<"Output of "<<file_way[i]<<endl;
		ifstream fin(file_way[i]);            //open file
		init();
		int time0 = clock();                  //init time
		char ls,dirty;
		while (fin>>ls){
			if (!(ls == 's' || ls == 'l')) break;
			fin>>dirty>>dirty;                //去掉无用字符
			fin>>address;
			long long ad=Fto2(address);       //进制转换，转成10进制（计算机中2进制）
			VA = ad >> page_size;  VA=VA & mask_20;         //分解虚拟地址的页号
			int offset = ad&mask_12;                        //页内偏移量
			////////////////////////////////////////////////////////// search tlb
			PA = search_tlb(VA);
			/////////////////////////////////////////////////////////
			PAandOff = PA<<page_size; PAandOff+=offset;                //组成完整的物理地址
			///////////////////////////////////////////////////////// search cache
			search_cache(PAandOff);
			////////////////////////////////////////////////////////
			ls='#';
		}
		cout<<"running time:          "<<clock()-time0<<"ms"<<endl;
		fout<<"running time:		  "<<clock()-time0<<"ms"<<endl;
		fout<<"total access:          "<<cache_hit+cache_miss<<endl;
		//fout<<"cache_hit:			  "<<cache_hit<<endl;
		//fout<<"cache_miss:        "<<cache_miss<<endl;
		fout<<"cache_hit_rate:        "<<double(cache_hit)/double(cache_hit+cache_miss)*100<<"%"<<endl;
		//fout<<"tlb_hit:           "<<tlb_hit<<endl;
		//fout<<"tlb_miss:          "<<tlb_miss<<endl;
		fout<<"tlb_hit_rate:          "<<double(tlb_hit)/double(tlb_hit+tlb_miss)*100<<"%"<<endl;
		//fout<<"pagetable_hit:         "<<table_hit<<endl;
		//fout<<"pagetable_miss:        "<<table_miss<<endl;
		fout<<"pagetable_hit_rate:    "<<double(table_hit+tlb_hit)/double(tlb_miss+tlb_hit)*100<<"%"<<endl;
		fout<<"page fault:            "<<table_miss<<endl<<endl;
	}

	return 0;
}
int main()
{
	read();
	system("pause");
	return 0;
}
