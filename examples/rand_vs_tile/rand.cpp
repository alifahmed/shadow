#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

volatile uint8_t* gm;

int main(){
	uint64_t addr;
    uint64_t hash = 0xC32ED012FEA8B4D3ULL;
    uint64_t tmpRnd;
    uint8_t tmpb;
    uint16_t tmpw;
    uint32_t tmpl;
    uint64_t tmpq;
    uint64_t allocSize = 1600124ULL;
    gm = (volatile uint8_t*)malloc(allocSize);
    if(gm == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(-1);
    }

	uint32_t* pp = (uint32_t* )gm;

    uint64_t addr_413800201 = 1600016, strd_413800201 = 0;
    uint64_t addr_413700201 = 1600016, strd_413700201 = 0;
    uint64_t addr_413600201 = 1600004, strd_413600201 = 0;
    uint64_t addr_413800101 = 1600012, strd_413800101 = 0;
    uint64_t addr_413700101 = 1600012, strd_413700101 = 0;
    uint64_t addr_413600101 = 1600000, strd_413600101 = 0;

	for(uint64_t i = 0; i < 200000; i++){
		*pp += rand();
	}

	free((void*)gm);

	return 0;
}
