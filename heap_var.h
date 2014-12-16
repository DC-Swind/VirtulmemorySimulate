#ifndef _HEAP_VAR_H_
#define _HEAP_VAR_H_

#include "TLB.h"
#include "Memory.h"
#include "Cache.h"
#include "TABLE.h"

#define tlb_size 64
#define memory_size 4096
#define table_size 1048576                       //าณฑํฯ๎ส
#define VA_size 20
#define PA_size 12
#define page_size 12
#define block_size 5
#define cache_size 2048

int mask_4 = 15;
int mask_9 = 511;
int mask_10 = 1023;
int mask_12 =4095;
int mask_20 =1048575;

int VA,PA,PAandOff;
char address[9];
int tlb_hit;
int tlb_miss;
int table_hit;
int table_miss;
int cache_hit;
int cache_miss;

TLB *tlb = new TLB[tlb_size];                           //create tlb;
TABLE *table = new TABLE[table_size];               //create memory;
Memory *memory = new Memory[memory_size];
Cache *cache = new Cache[cache_size];
#endif
