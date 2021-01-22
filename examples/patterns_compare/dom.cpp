#include <cstdlib>
#include <cstdint>
#include <cstdio>

volatile uint8_t* gm;

int main(){
    uint64_t addr;
    uint64_t hash = 0xC32ED012FEA8B4D3ULL;
    uint64_t tmpRnd;
    uint8_t tmpb;
    uint16_t tmpw;
    uint32_t tmpl;
    uint64_t tmpq;
    uint64_t allocSize = 1837440ULL;
    gm = (volatile uint8_t*)malloc(allocSize);
    if(gm == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(-1);
    }

    uint64_t addr_593300101 = 1050628;
    uint64_t addr_592100101 = 1051648;
    uint64_t addr_577600101 = 1312768, strd_577600101 = 0;
    uint64_t addr_579800101 = 1312768;
    uint64_t addr_580900101 = 1312772;
    uint64_t addr_578700101 = 1313792;
    uint64_t addr_563400101 = 1837056, strd_563400101 = 0;
    uint64_t addr_563500101 = 1837068, strd_563500101 = 0;
    uint64_t addr_563600101 = 1837068, strd_563600101 = 0;

    for(uint64_t loop2 = 0; loop2 < 256ULL; loop2++){
		for(uint64_t loop1 = 0; loop1 < 256ULL; loop1++){
		    addr_593300101 = 1050628 + (loop1*1024);
		    for(uint64_t loop0 = 0; loop0 < 256ULL; loop0++){
		        __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr_593300101) : "memory");
		        addr_593300101 += 4;
		        if(addr_593300101 >= 1312768) addr_593300101 = 1050628;
		    }
		}
	}
    
    free((void*)gm);
    return 0;
}
