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
    uint64_t allocSize = 5804032ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 500000000
    {
        int64_t addr_573100101 = 6992LL;
        int64_t addr_545500101 = 167952LL;
        int64_t addr_545700101 = 5733316LL;
block0:
        goto block2;

block12:
        for(uint64_t loop0 = 0; loop0 < 40804247ULL; loop0++){
            //Dominant stride
            READ_8b(addr_573100101);
            addr_573100101 += 8LL;
            if(addr_573100101 >= 84064LL) addr_573100101 = 6992LL;

        }
        goto block13;

block11:
        //Random
        addr = (bounded_rnd(5794320LL - 5792312LL) + 5792312LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5794312LL - 5792304LL) + 5792304LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_11_6 = 211749LL;
        static uint64_t out_11_4 = 1023401LL;
        static uint64_t out_11_2 = 17993LL;
        tmpRnd = out_11_6 + out_11_4 + out_11_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_11_6)){
                out_11_6--;
                goto block6;
            }
            else if (tmpRnd < (out_11_6 + out_11_4)){
                out_11_4--;
                goto block4;
            }
            else {
                out_11_2--;
                goto block2;
            }
        }
        goto block12;


block9:
        //Random
        addr = (bounded_rnd(5800256LL - 5797176LL) + 5797176LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5800240LL - 5797160LL) + 5797160LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5800264LL - 5797184LL) + 5797184LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_9_11 = 1253129LL;
        static uint64_t out_9_6 = 4905LL;
        static uint64_t out_9_4 = 81568LL;
        static uint64_t out_9_2 = 1364LL;
        tmpRnd = out_9_11 + out_9_6 + out_9_4 + out_9_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_9_11)){
                out_9_11--;
                goto block11;
            }
            else if (tmpRnd < (out_9_11 + out_9_6)){
                out_9_6--;
                goto block6;
            }
            else if (tmpRnd < (out_9_11 + out_9_6 + out_9_4)){
                out_9_4--;
                goto block4;
            }
            else {
                out_9_2--;
                goto block2;
            }
        }
        goto block11;


block6:
        //Small tile
        READ_4b(addr_545500101);
        addr_545500101 += (167956LL - 167952LL);

        //Dominant stride
        READ_4b(addr_545700101);
        addr_545700101 += 16LL;
        if(addr_545700101 >= 5790680LL) addr_545700101 = 5690340LL;

        //Unordered
        static uint64_t out_6_9 = 1340959LL;
        static uint64_t out_6_6 = 1903LL;
        static uint64_t out_6_4 = 36474LL;
        static uint64_t out_6_2 = 642LL;
        tmpRnd = out_6_9 + out_6_6 + out_6_4 + out_6_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_6_9)){
                out_6_9--;
                goto block9;
            }
            else if (tmpRnd < (out_6_9 + out_6_6)){
                out_6_6--;
                goto block6;
            }
            else if (tmpRnd < (out_6_9 + out_6_6 + out_6_4)){
                out_6_4--;
                goto block4;
            }
            else {
                out_6_2--;
                goto block2;
            }
        }
        goto block9;


block4:
        //Random
        addr = (bounded_rnd(5794320LL - 5792312LL) + 5792312LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5794312LL - 5792304LL) + 5792304LL) & ~7ULL;
        READ_8b(addr);

        goto block6;

block2:
        for(uint64_t loop1 = 0; loop1 < 69ULL; loop1++){
            //Loop Indexed
            addr = 152LL + (16 * loop1);
            READ_8b(addr);

            //Loop Indexed
            addr = 144LL + (16 * loop1);
            READ_8b(addr);

        }
        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_2 = 0;
        cov_2++;
        if(cov_2 <= 19122ULL) {
            static uint64_t out_2 = 0;
            out_2 = (out_2 == 6LL) ? 1 : (out_2 + 1);
            if (out_2 <= 5LL) goto block4;
            else goto block6;
        }
        else if (cov_2 <= 19247ULL) goto block4;
        else goto block6;

block13:
        int dummy;
    }

    // Interval: 500000000 - 1000000000
    {
        int64_t addr_573100101 = 64632LL;
block14:
        goto block15;

block15:
        for(uint64_t loop2 = 0; loop2 < 71400384ULL; loop2++){
            //Dominant stride
            READ_8b(addr_573100101);
            addr_573100101 += 8LL;
            if(addr_573100101 >= 119296LL) addr_573100101 = 6992LL;

        }
        goto block16;

block16:
        int dummy;
    }

    // Interval: 1000000000 - 1500000000
    {
        int64_t addr_573100101 = 41144LL;
block17:
        goto block18;

block18:
        for(uint64_t loop3 = 0; loop3 < 71409193ULL; loop3++){
            //Dominant stride
            READ_8b(addr_573100101);
            addr_573100101 += 8LL;
            if(addr_573100101 >= 163528LL) addr_573100101 = 6992LL;

        }
        goto block19;

block19:
        int dummy;
    }

    // Interval: 1500000000 - 1566694500
    {
        int64_t addr_573100101 = 94304LL;
block20:
        goto block21;

block21:
        for(uint64_t loop4 = 0; loop4 < 9525578ULL; loop4++){
            //Dominant stride
            READ_8b(addr_573100101);
            addr_573100101 += 8LL;
            if(addr_573100101 >= 166112LL) addr_573100101 = 6992LL;

        }
        goto block22;

block22:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
