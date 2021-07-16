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
    uint64_t allocSize = 127750144ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 500000000
    {
        int64_t addr_395600101 = 127746500LL, strd_395600101 = 0;
        int64_t addr_395700101 = 127746512LL, strd_395700101 = 0;
        int64_t addr_395800101 = 127746512LL, strd_395800101 = 0;
        int64_t addr_397000101 = 16LL;
block0:
        goto block2;

block4:
        //Small tile
        WRITE_4b(addr_395800101);
        switch(addr_395800101) {
            case 127746500LL : strd_395800101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395800101 = (127746500LL - 127746620LL); break;
            case 127746512LL : strd_395800101 = (127746516LL - 127746512LL); break;
        }
        addr_395800101 += strd_395800101;

        //Small tile
        WRITE_4b(addr_397000101);
        addr_397000101 += (20LL - 16LL);

        goto block2;

block2:
        //Small tile
        READ_4b(addr_395600101);
        switch(addr_395600101) {
            case 127746500LL : strd_395600101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395600101 = (127746500LL - 127746620LL); break;
        }
        addr_395600101 += strd_395600101;

        //Small tile
        READ_4b(addr_395700101);
        switch(addr_395700101) {
            case 127746500LL : strd_395700101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395700101 = (127746500LL - 127746620LL); break;
            case 127746512LL : strd_395700101 = (127746516LL - 127746512LL); break;
        }
        addr_395700101 += strd_395700101;

        //Few edges. Don't bother optimizing
        static uint64_t out_2 = 0;
        out_2++;
        if (out_2 <= 17856833LL) goto block4;
        else goto block5;


block5:
        int dummy;
    }

    // Interval: 500000000 - 894227715
    {
        int64_t addr_395800101 = 127746620LL, strd_395800101 = 0;
        int64_t addr_397000101 = 71427348LL;
        int64_t addr_395600101 = 127746612LL, strd_395600101 = 0;
        int64_t addr_395700101 = 127746500LL, strd_395700101 = 0;
block6:
        goto block8;

block10:
        //Small tile
        READ_4b(addr_395600101);
        switch(addr_395600101) {
            case 127746612LL : strd_395600101 = (127746616LL - 127746612LL); break;
            case 127746500LL : strd_395600101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395600101 = (127746500LL - 127746620LL); break;
        }
        addr_395600101 += strd_395600101;

        //Small tile
        READ_4b(addr_395700101);
        switch(addr_395700101) {
            case 127746500LL : strd_395700101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395700101 = (127746500LL - 127746620LL); break;
        }
        addr_395700101 += strd_395700101;

        goto block8;

block8:
        //Small tile
        WRITE_4b(addr_395800101);
        switch(addr_395800101) {
            case 127746500LL : strd_395800101 = (127746504LL - 127746500LL); break;
            case 127746620LL : strd_395800101 = (127746500LL - 127746620LL); break;
        }
        addr_395800101 += strd_395800101;

        //Small tile
        WRITE_4b(addr_397000101);
        addr_397000101 += (71427352LL - 71427348LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_8 = 0;
        out_8++;
        if (out_8 <= 14079523LL) goto block10;
        else goto block11;


block11:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
