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
    uint64_t allocSize = 53248ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1348403526
    {
        int64_t addr_735300101 = 48744LL, strd_735300101 = 0;
block0:
        goto block2;

block4:
        for(uint64_t loop0 = 0; loop0 < 8ULL; loop0++){
            //Loop Indexed
            addr = 46752LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 46752LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block5;

block2:
        for(uint64_t loop1 = 0; loop1 < 8ULL; loop1++){
            //Loop Indexed
            addr = 50804LL + (-4 * loop1);
            READ_4b(addr);

            //Small tile
            WRITE_4b(addr_735300101);
            switch(addr_735300101) {
                case 48736LL : strd_735300101 = (48724LL - 48736LL); break;
                case 48744LL : strd_735300101 = (48740LL - 48744LL); break;
                case 48716LL : strd_735300101 = (48704LL - 48716LL); break;
                case 48724LL : strd_735300101 = (48716LL - 48724LL); break;
                case 48696LL : strd_735300101 = (48744LL - 48696LL); break;
                case 48704LL : strd_735300101 = (48700LL - 48704LL); break;
            }
            addr_735300101 += strd_735300101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_2 = 0;
        out_2++;
        if (out_2 <= 370603LL) goto block4;
        else goto block10;


block5:
        //Random
        addr = (bounded_rnd(42692LL - 4048LL) + 4048LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_5 = 0;
        cov_5++;
        if(cov_5 <= 3245856ULL) {
            static uint64_t out_5 = 0;
            out_5 = (out_5 == 6LL) ? 1 : (out_5 + 1);
            if (out_5 <= 1LL) goto block6;
            else goto block9;
        }
        else if (cov_5 <= 3695006ULL) goto block6;
        else goto block9;

block6:
        //Random
        addr = (bounded_rnd(42680LL - 4032LL) + 4032LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_6 = 0;
        cov_6++;
        if(cov_6 <= 951565ULL) {
            static uint64_t out_6 = 0;
            out_6 = (out_6 == 7LL) ? 1 : (out_6 + 1);
            if (out_6 <= 6LL) goto block5;
            else goto block7;
        }
        else if (cov_6 <= 951590ULL) goto block7;
        else goto block5;

block7:
        //Random
        addr = (bounded_rnd(42692LL - 4048LL) + 4048LL) & ~3ULL;
        READ_4b(addr);

        //Unordered
        static uint64_t out_7_2 = 135962LL;
        static uint64_t out_7_7 = 854164LL;
        static uint64_t out_7_8 = 2394383LL;
        tmpRnd = out_7_2 + out_7_7 + out_7_8;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_7_2)){
                out_7_2--;
                goto block2;
            }
            else if (tmpRnd < (out_7_2 + out_7_7)){
                out_7_7--;
                goto block7;
            }
            else {
                out_7_8--;
                goto block8;
            }
        }
        goto block8;


block9:
        //Random
        addr = (bounded_rnd(42688LL - 4040LL) + 4040LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_9 = 0;
        cov_9++;
        if(cov_9 <= 2581030ULL) {
            static uint64_t out_9 = 0;
            out_9 = (out_9 == 11LL) ? 1 : (out_9 + 1);
            if (out_9 <= 1LL) goto block7;
            else goto block5;
        }
        else if (cov_9 <= 2780701ULL) goto block5;
        else goto block7;

block8:
        //Random
        addr = (bounded_rnd(42688LL - 4040LL) + 4040LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_8 = 0;
        cov_8++;
        if(cov_8 <= 2581007ULL) {
            static uint64_t out_8 = 0;
            out_8 = (out_8 == 11LL) ? 1 : (out_8 + 1);
            if (out_8 <= 10LL) goto block7;
            else goto block2;
        }
        else if (cov_8 <= 2780698ULL) goto block7;
        else goto block2;

block10:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
