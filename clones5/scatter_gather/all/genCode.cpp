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
    uint64_t allocSize = 48005120ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 944112594
    {
        int64_t addr_298400101 = 12000064LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001476LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001488LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001488LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001480LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001492LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001492LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36000064LL, strd_300800101 = 0;
block0:
        goto block4;

block14:
        for(uint64_t loop1 = 0; loop1 < 3000000ULL; loop1++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop1);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop1);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000064LL - 12000064LL) + 12000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 64LL) + 64LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 3000000ULL; loop0++){
            //Loop Indexed
            addr = 64LL + (4 * loop0);
            READ_4b(addr);

        }
        goto block4;

block9:
        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001492LL : strd_299600201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001492LL : strd_299700201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_9 = 0;
        out_9++;
        if (out_9 <= 2999999LL) goto block4;
        else if (out_9 <= 3000000LL) goto block14;
        else if (out_9 <= 5999999LL) goto block4;
        else if (out_9 <= 6000000LL) goto block14;
        else if (out_9 <= 8999999LL) goto block4;
        else if (out_9 <= 9000000LL) goto block14;
        else if (out_9 <= 11999999LL) goto block4;
        else if (out_9 <= 12000000LL) goto block14;
        else if (out_9 <= 14999999LL) goto block4;
        else if (out_9 <= 15000000LL) goto block14;
        else goto block4;


block4:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299600101 = (48001496LL - 48001488LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299700101 = (48001496LL - 48001488LL); break;
        }
        addr_299700101 += strd_299700101;

        //Few edges. Don't bother optimizing
        static uint64_t out_4 = 0;
        out_4++;
        if (out_4 <= 15293656LL) goto block9;
        else goto block15;


block15:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
