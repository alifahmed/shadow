#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include "immintrin.h"

__attribute__((always_inline)) static inline uint64_t bounded_rnd(uint64_t bound) {
    static uint64_t hash = 0xC32ED012FEA8B4D3ULL;
    hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);
    return (hash * (__uint128_t)bound) >> 64;
}

#define READ_1b(X)  __asm__ __volatile__ ("movb       (%1,%2), %0" : "=r"(tmp1)  : "r"(gm), "r"(X) : "memory")
#define READ_2b(X)  __asm__ __volatile__ ("movw       (%1,%2), %0" : "=r"(tmp2)  : "r"(gm), "r"(X) : "memory")
#define READ_4b(X)  __asm__ __volatile__ ("movl       (%1,%2), %0" : "=r"(tmp4)  : "r"(gm), "r"(X) : "memory")
#define READ_8b(X)  __asm__ __volatile__ ("movq       (%1,%2), %0" : "=r"(tmp8)  : "r"(gm), "r"(X) : "memory")
#define READ_16b(X) tmp16 = _mm_load_si128((__m128i const*)(gm + (X)))
#define READ_32b(X) tmp32 = _mm256_load_si256((__m256i const*)(gm + (X)))
#define READ_64b(X) tmp64 = _mm512_load_si512((__m512i const*)(gm + (X)))

#define WRITE_1b(X)  __asm__ __volatile__ ("movb      %2, (%0,%1)" : : "r"(gm), "r"(X), "r"(tmp1)  : "memory")
#define WRITE_2b(X)  __asm__ __volatile__ ("movw      %2, (%0,%1)" : : "r"(gm), "r"(X), "r"(tmp2)  : "memory")
#define WRITE_4b(X)  __asm__ __volatile__ ("movl      %2, (%0,%1)" : : "r"(gm), "r"(X), "r"(tmp4)  : "memory")
#define WRITE_8b(X)  __asm__ __volatile__ ("movq      %2, (%0,%1)" : : "r"(gm), "r"(X), "r"(tmp8)  : "memory")
#define WRITE_16b(X) _mm_store_si128((__m128i*)(gm + (X)), tmp16)
#define WRITE_32b(X) _mm256_store_si256((__m256i*)(gm + (X)), tmp32)
#define WRITE_64b(X) _mm512_store_si512((__m512i*)(gm + (X)), tmp64)

#define RMW_1b(X)  __asm__ __volatile__ ("addb $1, (%0,%1)" : : "r"(gm), "r"(X) : "memory")
#define RMW_2b(X)  __asm__ __volatile__ ("addw $1, (%0,%1)" : : "r"(gm), "r"(X) : "memory")
#define RMW_4b(X)  __asm__ __volatile__ ("addl $1, (%0,%1)" : : "r"(gm), "r"(X) : "memory")
#define RMW_8b(X)  __asm__ __volatile__ ("addq $1, (%0,%1)" : : "r"(gm), "r"(X) : "memory")

volatile uint8_t* gm;
#ifdef __SSE2__
    volatile __m128i tmp16;
#endif
#ifdef __AVX__
    volatile __m256i tmp32;
#endif
#ifdef __AVX512F__
    volatile __m512i tmp64;
#endif

int main(){
    int64_t addr;
    uint64_t tmpRnd;
    uint8_t tmp1;
    uint16_t tmp2;
    uint32_t tmp4;
    uint64_t tmp8;
    uint64_t allocSize = 25206784ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 826504310
    {
        int64_t addr_425900101 = 16814096LL;
        int64_t addr_426900101 = 8912LL, strd_426900101 = 0;
        int64_t addr_427100101 = 16810004LL;
        int64_t addr_415400101 = 21008404LL;
        int64_t addr_415200101 = 8912LL, strd_415200101 = 0;
        int64_t addr_414300101 = 21008400LL;
        int64_t addr_414100101 = 704LL, strd_414100101 = 0;
        int64_t addr_413200101 = 21012496LL;
        int64_t addr_412100101 = 21008400LL, strd_412100101 = 0;
block0:
        goto block37;

block37:
        for(uint64_t loop2 = 0; loop2 < 4ULL; loop2++){
            addr_425900101 = 16814096LL;
            addr_427100101 = 16810004LL;
            addr_415400101 = 21008404LL;
            addr_414300101 = 21008400LL;
            addr_413200101 = 21012496LL;
            for(uint64_t loop0 = 0; loop0 < 1048576ULL; loop0++){
                //Loop Indexed
                addr = 21008400LL + (4 * loop0);
                READ_4b(addr);

                //Small tile
                READ_4b(addr_412100101);
                switch(addr_412100101) {
                    case 21012492LL : strd_412100101 = (21008400LL - 21012492LL); break;
                    case 25198604LL : strd_412100101 = (21008400LL - 25198604LL); break;
                    case 21008400LL : strd_412100101 = (21008404LL - 21008400LL); break;
                }
                addr_412100101 += strd_412100101;

                //Loop Indexed
                addr = 12611600LL + (4 * loop0);
                WRITE_4b(addr);

                //Dominant stride
                READ_4b(addr_413200101);
                addr_413200101 += 4LL;
                if(addr_413200101 >= 25202704LL) addr_413200101 = 21012496LL;

                //Loop Indexed
                addr = 8413200LL + (4 * loop0);
                WRITE_4b(addr);

                //Small tile
                READ_4b(addr_414100101);
                switch(addr_414100101) {
                    case 4796LL : strd_414100101 = (704LL - 4796LL); break;
                    case 704LL : strd_414100101 = (708LL - 704LL); break;
                }
                addr_414100101 += strd_414100101;

                //Dominant stride
                READ_4b(addr_414300101);
                addr_414300101 += 4LL;
                if(addr_414300101 >= 25202700LL) addr_414300101 = 21008400LL;

                //Loop Indexed
                addr = 4214800LL + (4 * loop0);
                WRITE_4b(addr);

                //Small tile
                READ_4b(addr_415200101);
                switch(addr_415200101) {
                    case 8912LL : strd_415200101 = (8916LL - 8912LL); break;
                    case 13004LL : strd_415200101 = (8912LL - 13004LL); break;
                }
                addr_415200101 += strd_415200101;

                //Dominant stride
                READ_4b(addr_415400101);
                addr_415400101 += 4LL;
                if(addr_415400101 >= 25202704LL) addr_415400101 = 21008404LL;

                //Loop Indexed
                addr = 16400LL + (4 * loop0);
                WRITE_4b(addr);

                //Loop Indexed
                addr = 12611600LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 12611600LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 8413200LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 8413200LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 4214800LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 4214800LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 16400LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 16400LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 12611600LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 8413200LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 4214800LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 16400LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 16810000LL + (4 * loop0);
                WRITE_4b(addr);

                //Loop Indexed
                addr = 16810000LL + (4 * loop0);
                READ_4b(addr);

                //Loop Indexed
                addr = 16810000LL + (4 * loop0);
                READ_4b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 1048576ULL; loop1++){
                //Loop Indexed
                addr = 16810000LL + (4 * loop1);
                READ_4b(addr);

                //Dominant stride
                READ_4b(addr_425900101);
                addr_425900101 += 4LL;
                if(addr_425900101 >= 21004304LL) addr_425900101 = 16814096LL;

                //Loop Indexed
                addr = 16810000LL + (4 * loop1);
                READ_4b(addr);

                //Small tile
                READ_4b(addr_426900101);
                switch(addr_426900101) {
                    case 8912LL : strd_426900101 = (8916LL - 8912LL); break;
                    case 13004LL : strd_426900101 = (8912LL - 13004LL); break;
                }
                addr_426900101 += strd_426900101;

                //Dominant stride
                READ_4b(addr_427100101);
                addr_427100101 += 4LL;
                if(addr_427100101 >= 21004304LL) addr_427100101 = 16810004LL;

                //Loop Indexed
                addr = 12611600LL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 8413200LL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 4214800LL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 16400LL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 21008400LL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 21008400LL + (4 * loop1);
                WRITE_4b(addr);

            }
        }
        goto block38;

block38:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
