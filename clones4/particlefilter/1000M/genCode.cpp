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
    uint64_t allocSize = 102400ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 929120932
    {
        int64_t addr_572100101 = 7184LL;
block0:
        goto block2;

block7:
        for(uint64_t loop0 = 0; loop0 < 51321756ULL; loop0++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 86768LL) addr_572100101 = 7184LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_7 = 0;
        out_7++;
        if (out_7 <= 1LL) goto block2;
        else goto block8;


block6:
        //Random
        addr = (bounded_rnd(92680LL - 90672LL) + 90672LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_6_7 = 1LL;
        static uint64_t out_6_5 = 1226009LL;
        static uint64_t out_6_2 = 18884LL;
        tmpRnd = out_6_7 + out_6_5 + out_6_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_6_7)){
                out_6_7--;
                goto block7;
            }
            else if (tmpRnd < (out_6_7 + out_6_5)){
                out_6_5--;
                goto block5;
            }
            else {
                out_6_2--;
                goto block2;
            }
        }
        goto block7;


block5:
        //Random
        addr = (bounded_rnd(99136LL - 95544LL) + 95544LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(99120LL - 95528LL) + 95528LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(99144LL - 95552LL) + 95552LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_5_6 = 1244886LL;
        static uint64_t out_5_5 = 69616LL;
        static uint64_t out_5_2 = 1114LL;
        tmpRnd = out_5_6 + out_5_5 + out_5_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_5_6)){
                out_5_6--;
                goto block6;
            }
            else if (tmpRnd < (out_5_6 + out_5_5)){
                out_5_5--;
                goto block5;
            }
            else {
                out_5_2--;
                goto block2;
            }
        }
        goto block6;


block2:
        for(uint64_t loop1 = 0; loop1 < 69ULL; loop1++){
            //Loop Indexed
            addr = 1112LL + (16 * loop1);
            READ_8b(addr);

            //Loop Indexed
            addr = 1104LL + (16 * loop1);
            READ_8b(addr);

        }
        goto block5;

block8:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
