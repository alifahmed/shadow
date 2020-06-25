#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include "immintrin.h"

int main(){
    uint64_t allocSize = 1600124ULL;
	uint64_t hash = 0x0123123;
    volatile uint8_t* gm = malloc(allocSize);
    if(gm == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(-1);
    }

    uint64_t ins_84 = 0;
    uint64_t ins_9 = 400000;
    uint64_t ins_72 = 800000;
    uint64_t ins_32 = 800000;
    uint64_t ins_70 = 1200000;
    uint64_t ins_55 = 1200000;
    uint64_t ins_46 = 1600000;
    uint64_t ins_45 = 1600000;
    uint64_t ins_44 = 1600000;
    uint64_t ins_23 = 1600000;
    uint64_t ins_22 = 1600000;
    uint64_t ins_21 = 1600000;


block0:
    for(uint64_t loop3 = 0; loop3 < 10ULL; loop3++){
        for(uint64_t loop2 = 0; loop2 < 100000ULL; loop2++){
			
            *ins_9 = 1804289383;
            ins_9 += 1;
            if(ins_9 >= 800000) ins_9 = 400000;

            volatile uint32_t ins_21_res = *ins_21;
            ins_21 += 2;
            if(ins_21 >= 1600124) ins_21 = 1600000;

            volatile uint32_t ins_22_res = *ins_22;
            ins_22 += 2;
            if(ins_22 >= 1600124) ins_22 = 1600000;

            *ins_23 = 846930886;
            ins_23 += 2;
            if(ins_23 >= 1600124) ins_23 = 1600000;

            *ins_32 = 1681692777;
            ins_32 += 1;
            if(ins_32 >= 1200000) ins_32 = 800000;

            volatile uint32_t ins_44_res = *ins_44;
            ins_44 += 2;
            if(ins_44 >= 1600124) ins_44 = 1600000;

            volatile uint32_t ins_45_res = *ins_45;
            ins_45 += 2;
            if(ins_45 >= 1600124) ins_45 = 1600000;

            *ins_46 = 1714636915;
            ins_46 += 2;
            if(ins_46 >= 1600124) ins_46 = 1600000;

            *ins_55 = 1957747793;
            ins_55 += 1;
            if(ins_55 >= 1600000) ins_55 = 1200000;

        }
        for(uint64_t loop1 = 0; loop1 < 100000ULL; loop1++){
            volatile uint32_t ins_70_res = *ins_70;
            ins_70 += 1;
            if(ins_70 >= 1600000) ins_70 = 1200000;

            volatile uint32_t ins_72_res = *ins_72;
            ins_72 += 1;
            if(ins_72 >= 1200000) ins_72 = 800000;



        }
        for(uint64_t loop0 = 0; loop0 < 100000ULL; loop0++){
            volatile uint32_t ins_84_res = *ins_84;
            ins_84 += 1;
            if(ins_84 >= 400000) ins_84 = 0;

        }
    }
    return 0;
}
