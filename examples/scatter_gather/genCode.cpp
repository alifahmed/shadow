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
    uint64_t allocSize = 2523136ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 10039086
    {
        int64_t addr_298100101 = 2880LL;
        int64_t addr_299200101 = 2519492LL, strd_299200101 = 0;
        int64_t addr_299300101 = 2519504LL, strd_299300101 = 0;
        int64_t addr_299400101 = 2519504LL, strd_299400101 = 0;
        int64_t addr_300300101 = 841280LL;
        int64_t addr_299200201 = 2519496LL, strd_299200201 = 0;
        int64_t addr_299300201 = 2519508LL, strd_299300201 = 0;
        int64_t addr_299400201 = 2519508LL, strd_299400201 = 0;
        int64_t addr_300500101 = 1679680LL;
block0:
        goto block4;

block9:
        //Small tile
        WRITE_4b(addr_300300101);
        addr_300300101 += (841284LL - 841280LL);

        //Small tile
        READ_4b(addr_299200201);
        switch(addr_299200201) {
            case 2519612LL : strd_299200201 = (2519496LL - 2519612LL); break;
            case 2519496LL : strd_299200201 = (2519504LL - 2519496LL); break;
            case 2519608LL : strd_299200201 = (2519492LL - 2519608LL); break;
            case 2519492LL : strd_299200201 = (2519500LL - 2519492LL); break;
        }
        addr_299200201 += strd_299200201;

        //Small tile
        READ_4b(addr_299300201);
        switch(addr_299300201) {
            case 2519612LL : strd_299300201 = (2519496LL - 2519612LL); break;
            case 2519508LL : strd_299300201 = (2519516LL - 2519508LL); break;
            case 2519496LL : strd_299300201 = (2519504LL - 2519496LL); break;
            case 2519608LL : strd_299300201 = (2519492LL - 2519608LL); break;
            case 2519492LL : strd_299300201 = (2519500LL - 2519492LL); break;
        }
        addr_299300201 += strd_299300201;

        //Small tile
        WRITE_4b(addr_299400201);
        switch(addr_299400201) {
            case 2519612LL : strd_299400201 = (2519496LL - 2519612LL); break;
            case 2519508LL : strd_299400201 = (2519516LL - 2519508LL); break;
            case 2519496LL : strd_299400201 = (2519504LL - 2519496LL); break;
            case 2519608LL : strd_299400201 = (2519492LL - 2519608LL); break;
            case 2519492LL : strd_299400201 = (2519500LL - 2519492LL); break;
        }
        addr_299400201 += strd_299400201;

        //Small tile
        WRITE_4b(addr_300500101);
        addr_300500101 += (1679684LL - 1679680LL);

        goto block4;

block4:
        //Small tile
        WRITE_4b(addr_298100101);
        addr_298100101 += (2884LL - 2880LL);

        //Small tile
        READ_4b(addr_299200101);
        switch(addr_299200101) {
            case 2519612LL : strd_299200101 = (2519496LL - 2519612LL); break;
            case 2519496LL : strd_299200101 = (2519504LL - 2519496LL); break;
            case 2519608LL : strd_299200101 = (2519492LL - 2519608LL); break;
            case 2519492LL : strd_299200101 = (2519500LL - 2519492LL); break;
        }
        addr_299200101 += strd_299200101;

        //Small tile
        READ_4b(addr_299300101);
        switch(addr_299300101) {
            case 2519612LL : strd_299300101 = (2519496LL - 2519612LL); break;
            case 2519608LL : strd_299300101 = (2519492LL - 2519608LL); break;
            case 2519496LL : strd_299300101 = (2519504LL - 2519496LL); break;
            case 2519504LL : strd_299300101 = (2519512LL - 2519504LL); break;
            case 2519492LL : strd_299300101 = (2519500LL - 2519492LL); break;
        }
        addr_299300101 += strd_299300101;

        //Small tile
        WRITE_4b(addr_299400101);
        switch(addr_299400101) {
            case 2519612LL : strd_299400101 = (2519496LL - 2519612LL); break;
            case 2519608LL : strd_299400101 = (2519492LL - 2519608LL); break;
            case 2519496LL : strd_299400101 = (2519504LL - 2519496LL); break;
            case 2519504LL : strd_299400101 = (2519512LL - 2519504LL); break;
            case 2519492LL : strd_299400101 = (2519500LL - 2519492LL); break;
        }
        addr_299400101 += strd_299400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_4 = 0;
        out_4++;
        if (out_4 <= 209147LL) goto block9;
        else goto block10;


block10:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
