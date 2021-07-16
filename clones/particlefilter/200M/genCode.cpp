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
    uint64_t allocSize = 5455872ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 200000000
    {
        int64_t addr_542100101 = 167952LL;
        int64_t addr_542600101 = 167952LL;
        int64_t addr_544800101 = 167952LL;
        int64_t addr_545000101 = 5385156LL;
        int64_t addr_545700101 = 167952LL;
        int64_t addr_545900101 = 5385156LL;
block0:
        goto block4;

block15:
        //Random
        addr = (bounded_rnd(5446160LL - 5444152LL) + 5444152LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5446152LL - 5444144LL) + 5444144LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_15 = 0;
        cov_15++;
        if(cov_15 <= 1160924ULL) {
            static uint64_t out_15 = 0;
            out_15 = (out_15 == 69LL) ? 1 : (out_15 + 1);
            if (out_15 <= 68LL) goto block6;
            else goto block4;
        }
        else goto block6;

block13:
        //Random
        addr = (bounded_rnd(5452096LL - 5449016LL) + 5449016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5452080LL - 5449000LL) + 5449000LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5452104LL - 5449024LL) + 5449024LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_13_15 = 1173597LL;
        static uint64_t out_13_6 = 80962LL;
        static uint64_t out_13_4 = 1293LL;
        tmpRnd = out_13_15 + out_13_6 + out_13_4;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_13_15)){
                out_13_15--;
                goto block15;
            }
            else if (tmpRnd < (out_13_15 + out_13_6)){
                out_13_6--;
                goto block6;
            }
            else {
                out_13_4--;
                goto block4;
            }
        }
        goto block15;


block10:
        //Small tile
        READ_4b(addr_545700101);
        addr_545700101 += (167956LL - 167952LL);

        //Dominant stride
        READ_4b(addr_545900101);
        addr_545900101 += 16LL;
        if(addr_545900101 >= 5442520LL) addr_545900101 = 5342180LL;

        //Unordered
        static uint64_t out_10_13 = 1255829LL;
        static uint64_t out_10_6 = 35926LL;
        static uint64_t out_10_4 = 613LL;
        tmpRnd = out_10_13 + out_10_6 + out_10_4;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_10_13)){
                out_10_13--;
                goto block13;
            }
            else if (tmpRnd < (out_10_13 + out_10_6)){
                out_10_6--;
                goto block6;
            }
            else {
                out_10_4--;
                goto block4;
            }
        }
        goto block13;


block8:
        //Random
        addr = (bounded_rnd(5446160LL - 5444152LL) + 5444152LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(5446152LL - 5444144LL) + 5444144LL) & ~7ULL;
        READ_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_8 = 0;
        out_8++;
        if (out_8 <= 1084056LL) goto block10;
        else goto block16;


block6:
        //Small tile
        READ_4b(addr_544800101);
        addr_544800101 += (167956LL - 167952LL);

        //Dominant stride
        READ_4b(addr_545000101);
        addr_545000101 += 16LL;
        if(addr_545000101 >= 5442520LL) addr_545000101 = 5342180LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_6 = 0;
        cov_6++;
        if(cov_6 <= 1166934ULL) {
            static uint64_t out_6 = 0;
            out_6 = (out_6 == 7LL) ? 1 : (out_6 + 1);
            if (out_6 <= 6LL) goto block8;
            else goto block10;
        }
        else if (cov_6 <= 1208569ULL) goto block10;
        else goto block8;

block4:
        for(uint64_t loop0 = 0; loop0 < 69ULL; loop0++){
            //Loop Indexed
            addr = 152LL + (16 * loop0);
            READ_8b(addr);

            //Loop Indexed
            addr = 144LL + (16 * loop0);
            READ_8b(addr);

            //Small tile
            WRITE_4b(addr_542100101);
            addr_542100101 += (167956LL - 167952LL);

            //Small tile
            READ_4b(addr_542600101);
            addr_542600101 += (167956LL - 167952LL);

        }
        goto block6;

block16:
        int dummy;
    }

    // Interval: 200000000 - 400000000
    {
        int64_t addr_573300101 = 6992LL;
block17:
        goto block18;

block18:
        for(uint64_t loop1 = 0; loop1 < 26526067ULL; loop1++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 67136LL) addr_573300101 = 6992LL;

        }
        goto block19;

block19:
        int dummy;
    }

    // Interval: 400000000 - 600000000
    {
        int64_t addr_573300101 = 17240LL;
block20:
        goto block21;

block21:
        for(uint64_t loop2 = 0; loop2 < 28557330ULL; loop2++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 89496LL) addr_573300101 = 6992LL;

        }
        goto block22;

block22:
        int dummy;
    }

    // Interval: 600000000 - 800000000
    {
        int64_t addr_573300101 = 62608LL;
block23:
        goto block24;

block24:
        for(uint64_t loop3 = 0; loop3 < 28559799ULL; loop3++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 106136LL) addr_573300101 = 6992LL;

        }
        goto block25;

block25:
        int dummy;
    }

    // Interval: 800000000 - 1000000000
    {
        int64_t addr_573300101 = 26888LL;
block26:
        goto block27;

block27:
        for(uint64_t loop4 = 0; loop4 < 28561436ULL; loop4++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 119296LL) addr_573300101 = 6992LL;

        }
        goto block28;

block28:
        int dummy;
    }

    // Interval: 1000000000 - 1200000000
    {
        int64_t addr_573300101 = 41152LL;
block29:
        goto block30;

block30:
        for(uint64_t loop5 = 0; loop5 < 28563081ULL; loop5++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 139008LL) addr_573300101 = 6992LL;

        }
        goto block31;

block31:
        int dummy;
    }

    // Interval: 1200000000 - 1400000000
    {
        int64_t addr_573300101 = 76152LL;
block32:
        goto block33;

block33:
        for(uint64_t loop6 = 0; loop6 < 28563849ULL; loop6++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 152552LL) addr_573300101 = 6992LL;

        }
        goto block34;

block34:
        int dummy;
    }

    // Interval: 1400000000 - 1566694502
    {
        int64_t addr_573300101 = 113088LL;
block35:
        goto block36;

block36:
        for(uint64_t loop7 = 0; loop7 < 23807841ULL; loop7++){
            //Dominant stride
            READ_8b(addr_573300101);
            addr_573300101 += 8LL;
            if(addr_573300101 >= 166112LL) addr_573300101 = 6992LL;

        }
        goto block37;

block37:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
