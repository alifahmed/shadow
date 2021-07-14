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
    uint64_t allocSize = 72491008ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1000000000
    {
        int64_t addr_395700101 = 72245700LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245712LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245712LL, strd_395900101 = 0;
        int64_t addr_401100101 = 72003600LL, strd_401100101 = 0;
        int64_t addr_402800101 = 240016LL;
        int64_t addr_403200101 = 72249360LL, strd_403200101 = 0;
        int64_t addr_401800101 = 72003604LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72003600LL, strd_403600101 = 0;
block0:
        goto block4;

block9:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_9_8 = 253LL;
        static uint64_t out_9_6 = 15227138LL;
        tmpRnd = out_9_8 + out_9_6;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_9_8)){
                out_9_8--;
                goto block8;
            }
            else {
                out_9_6--;
                goto block6;
            }
        }
        goto block10;


block8:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (240020LL - 240016LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
        }
        addr_403200101 += strd_403200101;

        goto block5;

block6:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block8;

block5:
        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_5 = 0;
        cov_5++;
        if(cov_5 <= 15227554ULL) {
            static uint64_t out_5 = 0;
            out_5 = (out_5 == 59951LL) ? 1 : (out_5 + 1);
            if (out_5 <= 1LL) goto block6;
            else goto block9;
        }
        else goto block9;

block4:
        for(uint64_t loop0 = 0; loop0 < 18000000ULL; loop0++){
            //Small tile
            READ_4b(addr_395700101);
            switch(addr_395700101) {
                case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
                case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
            }
            addr_395700101 += strd_395700101;

            //Small tile
            READ_4b(addr_395800101);
            switch(addr_395800101) {
                case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
                case 72245712LL : strd_395800101 = (72245716LL - 72245712LL); break;
                case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
            }
            addr_395800101 += strd_395800101;

            //Small tile
            WRITE_4b(addr_395900101);
            switch(addr_395900101) {
                case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
                case 72245712LL : strd_395900101 = (72245716LL - 72245712LL); break;
                case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
            }
            addr_395900101 += strd_395900101;

            //Loop Indexed
            addr = 16LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block5;

block10:
        int dummy;
    }

    // Interval: 1000000000 - 1088244838
    {
        int64_t addr_402800101 = 61150596LL;
        int64_t addr_403200101 = 72194180LL, strd_403200101 = 0;
        int64_t addr_401100101 = 72439944LL, strd_401100101 = 0;
        int64_t addr_401800101 = 72439944LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72439940LL, strd_403600101 = 0;
block11:
        goto block12;

block17:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_17 = 0;
        cov_17++;
        if(cov_17 <= 1243161ULL) {
            static uint64_t out_17 = 0;
            out_17 = (out_17 == 46043LL) ? 1 : (out_17 + 1);
            if (out_17 <= 46042LL) goto block12;
            else goto block14;
        }
        else goto block12;

block14:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (61150600LL - 61150596LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72194180LL : strd_403200101 = (72194184LL - 72194180LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
        }
        addr_403200101 += strd_403200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_14 = 0;
        out_14++;
        if (out_14 <= 2712354LL) goto block15;
        else goto block18;


block16:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72439940LL : strd_403600101 = (72439944LL - 72439940LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_16_17 = 1243174LL;
        static uint64_t out_16_14 = 19LL;
        static uint64_t out_16_12 = 1469115LL;
        tmpRnd = out_16_17 + out_16_14 + out_16_12;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_16_17)){
                out_16_17--;
                goto block17;
            }
            else if (tmpRnd < (out_16_17 + out_16_14)){
                out_16_14--;
                goto block14;
            }
            else {
                out_16_12--;
                goto block12;
            }
        }
        goto block17;


block12:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
            case 72439944LL : strd_401800101 = (72439948LL - 72439944LL); break;
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block14;

block15:
        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72439944LL : strd_401100101 = (72439948LL - 72439944LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_15 = 0;
        cov_15++;
        if(cov_15 <= 2712343ULL) {
            static uint64_t out_15 = 0;
            out_15 = (out_15 == 58964LL) ? 1 : (out_15 + 1);
            if (out_15 <= 58963LL) goto block16;
            else goto block12;
        }
        else goto block16;

block18:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
