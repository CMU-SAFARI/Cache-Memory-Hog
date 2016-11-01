//Author: Arnab Ghosh

#include <stdio.h>
#include <string.h>

#include <unistd.h>

//#include "timer.h"


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

#define BLOCKS_IN_PAGE (1<<6)
#define BLOCK_SIZE (1<<6)
#define BYTES_IN_CACHE 6

#define GIGABYTES_RAM 6

typedef unsigned int u32;

////////////////////////////////////////////////////////////////////////
// This fragment of code tries to occupy the bandwidth by trying to 
// stress the different banks of the DRAM by keeping a particular Row loaded
// into the memory buffer so that the memory access from the DRAM Faces latency
// and hence reduces the Request Service Rate.
////////////////////////////////////////////////////////////////////////

static char array[GIGABYTES_RAM*BYTES_PER_GB];

void bypass_access(u32 sets, u32 ways)
{
    u32 i, j, k,check;
    volatile u32 s;

	i=0;check=1;
	while(1){
		for(j=0;j<128,check==1;j++){				//Loop that goes through the 128 rows of each bank , it selects a row and accesses is continuously exploiting the row buffer load property
			for(k=0;k<=7,check==1;k++){			//Loop that goes across the 8 different banks of the DRAM chip
				if((j+k<<7+i)<<6 < 6*BYTES_PER_GB)	//checks whether a valid location is accessed
					s=array[(j+k<<7+i)<<6];
				else{
					check=0;			// If an invalid location is accessed then the check condition becomes false and the loop terminates
					break;
				}
			}
		}
		i+=128*8;						
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
        bypass_access(SETS, WAYS);	
    }
    return 0;
}
