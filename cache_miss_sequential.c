//Author: Arnab Ghosh
#include <stdio.h>
#include <string.h>

#include <unistd.h>

//#include "timer.h"

////////////////////////////////////////////////////////////////////////
// Xeon L5630 Processor 
//  L1 I-Cache: 4-way   128-set  32 KiB
//  L1 D-Cache: 8-way    64-set  32 KiB
//  L2 Cache:   8-way   512-set 256 KiB
//  L3 Cache:  16-way 12288-set  12 MiB
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// My processor 
//  L1 I-Cache :4-way   128-set  32 KiB 	
//  L1 D-Cache :8-way   64-set   32 KiB	
//  L2 Cache   :8-way   512-set 256 KiB
//  L3 Cache   :12-way  8192-set  6 MiB 
////////////////////////////////////////////////////////////////////////

#define SAMPLES 5
#define TIMES (1<<20)

#define BYTES_PER_KB (1024LL)
#define BYTES_PER_MB (1024*1024LL)
#define BYTES_PER_GB (1024*1024*1024LL)

#define PAGE_SIZE (1<<12)
#define CACHE_LINE_STRIDE (1<<6)
#define L2_SET_STRIDE (1<<15)
#define L3_SET_STRIDE (9*64*1024LL)

#define GIGABYTES_RAM 6

typedef unsigned int u32;

////////////////////////////////////////////////////////////////////////////
// This fragment of code tries to miss in the cache to reduce the available
// bandwidth to the other application vying for the memory bandwidth
//
// It tries to generate a streaming pattern of requests going across pages 
// to prevent the effect of prefetching .
////////////////////////////////////////////////////////////////////////////
static char array[GIGABYTES_RAM*BYTES_PER_GB];

void bypass_access(u32 sets, u32 ways)
{
    u32 i, j, k;
    volatile u32 s;
   
	i=0;
	while(i*PAGE_SIZE*CACHE_LINE_STRIDE*2<GIGABYTES_RAM*BYTES_PER_GB){		
		s=array[i*PAGE_SIZE*CACHE_LINE_STRIDE*2];
		i++;	
	}


}

int main()
{

#ifndef SETS
#   define SETS 1024
#endif
#ifdef SETS
#if SETS<1
#   define SETS 1
#endif
#if SETS>8192
#   define SETS 8192
#endif
#endif

#ifndef WAYS
#   define WAYS 12
#endif
#ifdef WAYS
#if WAYS<1
#   define WAYS 1
#endif
#if WAYS>12
#   define WAYS 12
#endif
#endif

    while (1) {
    unsigned long long i;
        bypass_access(SETS, WAYS);
    }
    return 0;
}
