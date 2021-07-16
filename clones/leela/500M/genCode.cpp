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

    // Interval: 0 - 500000000
    {
        int64_t addr_735300101 = 47976LL, strd_735300101 = 0;
block0:
        goto block2;

block8:
        //Random
        addr = (bounded_rnd(42688LL - 4040LL) + 4040LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_8 = 0;
        cov_8++;
        if(cov_8 <= 777126ULL) {
            static uint64_t out_8 = 0;
            out_8 = (out_8 == 13LL) ? 1 : (out_8 + 1);
            if (out_8 <= 12LL) goto block7;
            else goto block2;
        }
        else if (cov_8 <= 777130ULL) goto block2;
        else goto block7;

block9:
        //Random
        addr = (bounded_rnd(42680LL - 4032LL) + 4032LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_9 = 0;
        cov_9++;
        if(cov_9 <= 602344ULL) {
            static uint64_t out_9 = 0;
            out_9 = (out_9 == 8LL) ? 1 : (out_9 + 1);
            if (out_9 <= 7LL) goto block7;
            else goto block2;
        }
        else if (cov_9 <= 612499ULL) goto block7;
        else goto block2;

block2:
        for(uint64_t loop0 = 0; loop0 < 8ULL; loop0++){
            //Loop Indexed
            addr = 50036LL + (-4 * loop0);
            READ_4b(addr);

            //Small tile
            WRITE_4b(addr_735300101);
            switch(addr_735300101) {
                case 47968LL : strd_735300101 = (47956LL - 47968LL); break;
                case 47976LL : strd_735300101 = (47972LL - 47976LL); break;
                case 47948LL : strd_735300101 = (47936LL - 47948LL); break;
                case 47956LL : strd_735300101 = (47948LL - 47956LL); break;
                case 47928LL : strd_735300101 = (47976LL - 47928LL); break;
                case 47936LL : strd_735300101 = (47932LL - 47936LL); break;
            }
            addr_735300101 += strd_735300101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_2 = 0;
        out_2++;
        if (out_2 <= 135091LL) goto block4;
        else goto block11;


block4:
        for(uint64_t loop1 = 0; loop1 < 8ULL; loop1++){
            //Loop Indexed
            addr = 45984LL + (4 * loop1);
            READ_4b(addr);

            //Loop Indexed
            addr = 45984LL + (4 * loop1);
            WRITE_4b(addr);

        }
        goto block5;

block5:
        //Random
        addr = (bounded_rnd(42692LL - 4048LL) + 4048LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_5 = 0;
        cov_5++;
        if(cov_5 <= 1155338ULL) {
            static uint64_t out_5 = 0;
            out_5 = (out_5 == 4LL) ? 1 : (out_5 + 1);
            if (out_5 <= 2LL) goto block6;
            else goto block10;
        }
        else if (cov_5 <= 1379027ULL) goto block10;
        else goto block6;

block10:
        //Random
        addr = (bounded_rnd(42688LL - 4040LL) + 4040LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_10 = 0;
        cov_10++;
        if(cov_10 <= 771433ULL) {
            static uint64_t out_10 = 0;
            out_10 = (out_10 == 13LL) ? 1 : (out_10 + 1);
            if (out_10 <= 1LL) goto block7;
            else goto block5;
        }
        else if (cov_10 <= 771434ULL) goto block7;
        else goto block5;

block6:
        //Random
        addr = (bounded_rnd(42680LL - 4032LL) + 4032LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_6 = 0;
        cov_6++;
        if(cov_6 <= 605856ULL) {
            static uint64_t out_6 = 0;
            out_6 = (out_6 == 8LL) ? 1 : (out_6 + 1);
            if (out_6 <= 7LL) goto block5;
            else goto block7;
        }
        else if (cov_6 <= 614006ULL) goto block5;
        else goto block7;

block7:
        //Random
        addr = (bounded_rnd(42692LL - 4048LL) + 4048LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_7 = 0;
        cov_7++;
        if(cov_7 <= 1149492ULL) {
            static uint64_t out_7 = 0;
            out_7 = (out_7 == 4LL) ? 1 : (out_7 + 1);
            if (out_7 <= 2LL) goto block8;
            else goto block9;
        }
        else if (cov_7 <= 1377426ULL) goto block8;
        else goto block9;

block11:
        int dummy;
    }

    // Interval: 500000000 - 1000000000
    {
        int64_t addr_734300101 = 50036LL, strd_734300101 = 0;
        int64_t addr_735300101 = 47976LL, strd_735300101 = 0;
block12:
        goto block14;

block15:
        //Random
        addr = (bounded_rnd(42452LL - 4144LL) + 4144LL) & ~3ULL;
        READ_4b(addr);

        //Unordered
        static uint64_t out_15_15 = 181963LL;
        static uint64_t out_15_17 = 34662LL;
        static uint64_t out_15_16 = 1169567LL;
        tmpRnd = out_15_15 + out_15_17 + out_15_16;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_15_15)){
                out_15_15--;
                goto block15;
            }
            else if (tmpRnd < (out_15_15 + out_15_17)){
                out_15_17--;
                goto block17;
            }
            else {
                out_15_16--;
                goto block16;
            }
        }
        goto block16;


block14:
        for(uint64_t loop2 = 0; loop2 < 8ULL; loop2++){
            //Loop Indexed
            addr = 45984LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 45984LL + (4 * loop2);
            WRITE_4b(addr);

        }
        goto block15;

block19:
        //Small tile
        READ_4b(addr_734300101);
        switch(addr_734300101) {
            case 50036LL : strd_734300101 = (50032LL - 50036LL); break;
            case 50008LL : strd_734300101 = (50036LL - 50008LL); break;
        }
        addr_734300101 += strd_734300101;

        //Few edges. Don't bother optimizing
        static uint64_t out_19 = 0;
        out_19++;
        if (out_19 <= 1111287LL) goto block20;
        else goto block21;


block18:
        //Random
        addr = (bounded_rnd(42448LL - 4136LL) + 4136LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_18 = 0;
        cov_18++;
        if(cov_18 <= 1141513ULL) {
            static uint64_t out_18 = 0;
            out_18 = (out_18 == 11LL) ? 1 : (out_18 + 1);
            if (out_18 <= 10LL) goto block17;
            else goto block19;
        }
        else goto block17;

block20:
        //Small tile
        WRITE_4b(addr_735300101);
        switch(addr_735300101) {
            case 47968LL : strd_735300101 = (47956LL - 47968LL); break;
            case 47976LL : strd_735300101 = (47972LL - 47976LL); break;
            case 47948LL : strd_735300101 = (47936LL - 47948LL); break;
            case 47956LL : strd_735300101 = (47948LL - 47956LL); break;
            case 47928LL : strd_735300101 = (47976LL - 47928LL); break;
            case 47936LL : strd_735300101 = (47932LL - 47936LL); break;
        }
        addr_735300101 += strd_735300101;

        //Ordered...
        //Remainder zero for all out blocks...
        static uint64_t out_20 = 0;
        out_20 = (out_20 == 8LL) ? 1 : (out_20 + 1);
        if (out_20 <= 7LL) goto block19;
        else goto block14;


block17:
        //Random
        addr = (bounded_rnd(42452LL - 4144LL) + 4144LL) & ~3ULL;
        READ_4b(addr);

        //Unordered
        static uint64_t out_17_19 = 35137LL;
        static uint64_t out_17_18 = 1168240LL;
        static uint64_t out_17_17 = 182981LL;
        tmpRnd = out_17_19 + out_17_18 + out_17_17;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_17_19)){
                out_17_19--;
                goto block19;
            }
            else if (tmpRnd < (out_17_19 + out_17_18)){
                out_17_18--;
                goto block18;
            }
            else {
                out_17_17--;
                goto block17;
            }
        }
        goto block19;


block16:
        //Random
        addr = (bounded_rnd(42448LL - 4136LL) + 4136LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_16 = 0;
        cov_16++;
        if(cov_16 <= 1146739ULL) {
            static uint64_t out_16 = 0;
            out_16 = (out_16 == 11LL) ? 1 : (out_16 + 1);
            if (out_16 <= 10LL) goto block15;
            else goto block17;
        }
        else goto block15;

block21:
        int dummy;
    }

    // Interval: 1000000000 - 1348403526
    {
        int64_t addr_735300101 = 47928LL, strd_735300101 = 0;
        int64_t addr_734300101 = 50036LL, strd_734300101 = 0;
block22:
        goto block23;

block26:
        //Random
        addr = (bounded_rnd(42452LL - 4144LL) + 4144LL) & ~3ULL;
        READ_4b(addr);

        //Unordered
        static uint64_t out_26_26 = 133927LL;
        static uint64_t out_26_27 = 423457LL;
        static uint64_t out_26_28 = 25551LL;
        tmpRnd = out_26_26 + out_26_27 + out_26_28;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_26_26)){
                out_26_26--;
                goto block26;
            }
            else if (tmpRnd < (out_26_26 + out_26_27)){
                out_26_27--;
                goto block27;
            }
            else {
                out_26_28--;
                goto block28;
            }
        }
        goto block27;


block23:
        //Small tile
        WRITE_4b(addr_735300101);
        switch(addr_735300101) {
            case 47968LL : strd_735300101 = (47956LL - 47968LL); break;
            case 47976LL : strd_735300101 = (47972LL - 47976LL); break;
            case 47948LL : strd_735300101 = (47936LL - 47948LL); break;
            case 47928LL : strd_735300101 = (47976LL - 47928LL); break;
            case 47956LL : strd_735300101 = (47948LL - 47956LL); break;
            case 47936LL : strd_735300101 = (47932LL - 47936LL); break;
        }
        addr_735300101 += strd_735300101;

        //Unordered
        static uint64_t out_23_25 = 96601LL;
        static uint64_t out_23_30 = 676207LL;
        tmpRnd = out_23_25 + out_23_30;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_23_25)){
                out_23_25--;
                goto block25;
            }
            else {
                out_23_30--;
                goto block30;
            }
        }
        goto block31;


block25:
        for(uint64_t loop3 = 0; loop3 < 8ULL; loop3++){
            //Loop Indexed
            addr = 45984LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 45984LL + (4 * loop3);
            WRITE_4b(addr);

        }
        goto block26;

block27:
        //Random
        addr = (bounded_rnd(42448LL - 4136LL) + 4136LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_27 = 0;
        cov_27++;
        if(cov_27 <= 781550ULL) {
            static uint64_t out_27 = 0;
            out_27 = (out_27 == 11LL) ? 1 : (out_27 + 1);
            if (out_27 <= 10LL) goto block26;
            else goto block28;
        }
        else goto block26;

block28:
        //Random
        addr = (bounded_rnd(42452LL - 4144LL) + 4144LL) & ~3ULL;
        READ_4b(addr);

        //Unordered
        static uint64_t out_28_28 = 133977LL;
        static uint64_t out_28_29 = 423463LL;
        static uint64_t out_28_30 = 25515LL;
        tmpRnd = out_28_28 + out_28_29 + out_28_30;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_28_28)){
                out_28_28--;
                goto block28;
            }
            else if (tmpRnd < (out_28_28 + out_28_29)){
                out_28_29--;
                goto block29;
            }
            else {
                out_28_30--;
                goto block30;
            }
        }
        goto block29;


block29:
        //Random
        addr = (bounded_rnd(42448LL - 4136LL) + 4136LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_29 = 0;
        cov_29++;
        if(cov_29 <= 781946ULL) {
            static uint64_t out_29 = 0;
            out_29 = (out_29 == 11LL) ? 1 : (out_29 + 1);
            if (out_29 <= 10LL) goto block28;
            else goto block30;
        }
        else goto block28;

block30:
        //Small tile
        READ_4b(addr_734300101);
        switch(addr_734300101) {
            case 50036LL : strd_734300101 = (50032LL - 50036LL); break;
            case 50008LL : strd_734300101 = (50036LL - 50008LL); break;
        }
        addr_734300101 += strd_734300101;

        goto block23;

block31:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
