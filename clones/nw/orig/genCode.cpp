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
    uint64_t allocSize = 134287360ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1572285379
    {
        int64_t addr_374600101 = 4116LL, strd_374600101 = 0;
        int64_t addr_375200101 = 67149848LL;
        int64_t addr_408000101 = 4112LL;
        int64_t addr_417900101 = 66867216LL;
        int64_t addr_413500101 = 20504LL;
        int64_t addr_413400101 = 134282440LL;
        int64_t addr_406400101 = 67149848LL;
        int64_t addr_409000101 = 134282372LL;
        int64_t addr_409400101 = 134282436LL;
        int64_t addr_409800101 = 134282368LL;
        int64_t addr_411900101 = 134282440LL;
        int64_t addr_416300101 = 134012952LL;
        int64_t addr_418900101 = 134282372LL;
        int64_t addr_419300101 = 134282436LL;
        int64_t addr_419700101 = 134282368LL;
        int64_t addr_420300101 = 134282440LL;
block0:
        goto block24;

block24:
        for(uint64_t loop10 = 0; loop10 < 16785409ULL; loop10++){
            //Loop Indexed
            addr = 4112LL + (4 * loop10);
            WRITE_4b(addr);

        }
        for(uint64_t loop9 = 0; loop9 < 16777216ULL; loop9++){
            //Small tile
            READ_4b(addr_374600101);
            switch(addr_374600101) {
                case 4116LL : strd_374600101 = (4120LL - 4116LL); break;
                case 20496LL : strd_374600101 = (4116LL - 20496LL); break;
            }
            addr_374600101 += strd_374600101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375200101);
            addr_375200101 += 4LL;
            if(addr_375200101 >= 134275092LL) addr_375200101 = 67149848LL;

        }
        for(uint64_t loop8 = 0; loop8 < 32896ULL; loop8++){
            addr_413400101 = 134282440LL;
            addr_409000101 = 134282372LL;
            addr_409400101 = 134282436LL;
            addr_409800101 = 134282368LL;
            addr_411900101 = 134282440LL;
            for(uint64_t loop7 = 0; loop7 < 256ULL; loop7++){
                //Dominant stride
                READ_4b(addr_406400101);
                addr_406400101 += 4LL;
                if(addr_406400101 >= 134258772LL) addr_406400101 = 67149848LL;

                //Loop Indexed
                addr = 134281344LL + (4 * loop7);
                WRITE_4b(addr);

            }
            for(uint64_t loop6 = 0; loop6 < 289ULL; loop6++){
                //Dominant stride
                READ_4b(addr_408000101);
                addr_408000101 += 4LL;
                if(addr_408000101 >= 67129428LL) addr_408000101 = 4112LL;

                //Loop Indexed
                addr = 134282368LL + (4 * loop6);
                WRITE_4b(addr);

            }
            for(uint64_t loop5 = 0; loop5 < 256ULL; loop5++){
                //Dominant stride
                READ_4b(addr_409000101);
                addr_409000101 += 4LL;
                if(addr_409000101 >= 134283456LL) addr_409000101 = 134282372LL;

                //Dominant stride
                READ_4b(addr_409400101);
                addr_409400101 += 4LL;
                if(addr_409400101 >= 134283520LL) addr_409400101 = 134282436LL;

                //Dominant stride
                READ_4b(addr_409800101);
                addr_409800101 += 4LL;
                if(addr_409800101 >= 134283452LL) addr_409800101 = 134282368LL;

                //Loop Indexed
                addr = 134281344LL + (4 * loop5);
                READ_4b(addr);

                //Dominant stride
                WRITE_4b(addr_411900101);
                addr_411900101 += 4LL;
                if(addr_411900101 >= 134283524LL) addr_411900101 = 134282440LL;

            }
            for(uint64_t loop4 = 0; loop4 < 256ULL; loop4++){
                //Dominant stride
                READ_4b(addr_413400101);
                addr_413400101 += 4LL;
                if(addr_413400101 >= 134283524LL) addr_413400101 = 134282440LL;

                //Dominant stride
                WRITE_4b(addr_413500101);
                addr_413500101 += 4LL;
                if(addr_413500101 >= 67129428LL) addr_413500101 = 20504LL;

            }
        }
        for(uint64_t loop3 = 0; loop3 < 32640ULL; loop3++){
            addr_418900101 = 134282372LL;
            addr_419300101 = 134282436LL;
            addr_419700101 = 134282368LL;
            addr_420300101 = 134282440LL;
            for(uint64_t loop2 = 0; loop2 < 256ULL; loop2++){
                //Dominant stride
                READ_4b(addr_416300101);
                addr_416300101 += 4LL;
                if(addr_416300101 >= 134275092LL) addr_416300101 = 67428376LL;

                //Loop Indexed
                addr = 134281344LL + (4 * loop2);
                WRITE_4b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 289ULL; loop1++){
                //Dominant stride
                READ_4b(addr_417900101);
                addr_417900101 += 4LL;
                if(addr_417900101 >= 67145748LL) addr_417900101 = 282640LL;

                //Loop Indexed
                addr = 134282368LL + (4 * loop1);
                WRITE_4b(addr);

            }
            for(uint64_t loop0 = 0; loop0 < 256ULL; loop0++){
                //Dominant stride
                READ_4b(addr_418900101);
                addr_418900101 += 4LL;
                if(addr_418900101 >= 134283456LL) addr_418900101 = 134282372LL;

                //Dominant stride
                READ_4b(addr_419300101);
                addr_419300101 += 4LL;
                if(addr_419300101 >= 134283520LL) addr_419300101 = 134282436LL;

                //Dominant stride
                READ_4b(addr_419700101);
                addr_419700101 += 4LL;
                if(addr_419700101 >= 134283452LL) addr_419700101 = 134282368LL;

                //Loop Indexed
                addr = 134281344LL + (4 * loop0);
                READ_4b(addr);

                //Dominant stride
                WRITE_4b(addr_420300101);
                addr_420300101 += 4LL;
                if(addr_420300101 >= 134283524LL) addr_420300101 = 134282440LL;

            }
        }
        goto block25;

block25:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
