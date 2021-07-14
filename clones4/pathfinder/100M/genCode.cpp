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

    // Interval: 0 - 100000000
    {
        int64_t addr_395700101 = 72245700LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245712LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245712LL, strd_395900101 = 0;
        int64_t addr_397100101 = 16LL;
block0:
        goto block3;

block4:
        //Small tile
        WRITE_4b(addr_397100101);
        addr_397100101 += (20LL - 16LL);

        goto block3;

block3:
        //Small tile
        READ_4b(addr_395700101);
        switch(addr_395700101) {
            case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
        }
        addr_395700101 += strd_395700101;

        //Small tile
        READ_4b(addr_395800101);
        switch(addr_395800101) {
            case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
            case 72245712LL : strd_395800101 = (72245716LL - 72245712LL); break;
        }
        addr_395800101 += strd_395800101;

        //Small tile
        WRITE_4b(addr_395900101);
        switch(addr_395900101) {
            case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
            case 72245712LL : strd_395900101 = (72245716LL - 72245712LL); break;
        }
        addr_395900101 += strd_395900101;

        //Few edges. Don't bother optimizing
        static uint64_t out_3 = 0;
        out_3++;
        if (out_3 <= 3571218LL) goto block4;
        else goto block5;


block5:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_397100101 = 14284888LL;
        int64_t addr_395700101 = 72245776LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245788LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245788LL, strd_395900101 = 0;
block6:
        goto block7;

block7:
        //Small tile
        WRITE_4b(addr_397100101);
        addr_397100101 += (14284892LL - 14284888LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_7 = 0;
        out_7++;
        if (out_7 <= 3571415LL) goto block10;
        else goto block11;


block10:
        //Small tile
        READ_4b(addr_395700101);
        switch(addr_395700101) {
            case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
            case 72245776LL : strd_395700101 = (72245780LL - 72245776LL); break;
        }
        addr_395700101 += strd_395700101;

        //Small tile
        READ_4b(addr_395800101);
        switch(addr_395800101) {
            case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
            case 72245788LL : strd_395800101 = (72245792LL - 72245788LL); break;
        }
        addr_395800101 += strd_395800101;

        //Small tile
        WRITE_4b(addr_395900101);
        switch(addr_395900101) {
            case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
            case 72245788LL : strd_395900101 = (72245792LL - 72245788LL); break;
        }
        addr_395900101 += strd_395900101;

        goto block7;

block11:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_395700101 = 72245768LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245780LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245780LL, strd_395900101 = 0;
block12:
        goto block16;

block16:
        for(uint64_t loop0 = 0; loop0 < 3571416ULL; loop0++){
            //Small tile
            READ_4b(addr_395700101);
            switch(addr_395700101) {
                case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
                case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
                case 72245768LL : strd_395700101 = (72245772LL - 72245768LL); break;
            }
            addr_395700101 += strd_395700101;

            //Small tile
            READ_4b(addr_395800101);
            switch(addr_395800101) {
                case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
                case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
                case 72245780LL : strd_395800101 = (72245784LL - 72245780LL); break;
            }
            addr_395800101 += strd_395800101;

            //Small tile
            WRITE_4b(addr_395900101);
            switch(addr_395900101) {
                case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
                case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
                case 72245780LL : strd_395900101 = (72245784LL - 72245780LL); break;
            }
            addr_395900101 += strd_395900101;

            //Loop Indexed
            addr = 28570552LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block17;

block17:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_395700101 = 72245764LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245776LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245776LL, strd_395900101 = 0;
block18:
        goto block22;

block22:
        for(uint64_t loop1 = 0; loop1 < 3571416ULL; loop1++){
            //Small tile
            READ_4b(addr_395700101);
            switch(addr_395700101) {
                case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
                case 72245764LL : strd_395700101 = (72245768LL - 72245764LL); break;
                case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
            }
            addr_395700101 += strd_395700101;

            //Small tile
            READ_4b(addr_395800101);
            switch(addr_395800101) {
                case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
                case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
                case 72245776LL : strd_395800101 = (72245780LL - 72245776LL); break;
            }
            addr_395800101 += strd_395800101;

            //Small tile
            WRITE_4b(addr_395900101);
            switch(addr_395900101) {
                case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
                case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
                case 72245776LL : strd_395900101 = (72245780LL - 72245776LL); break;
            }
            addr_395900101 += strd_395900101;

            //Loop Indexed
            addr = 42856216LL + (4 * loop1);
            WRITE_4b(addr);

        }
        goto block23;

block23:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_395700101 = 72245760LL, strd_395700101 = 0;
        int64_t addr_395800101 = 72245772LL, strd_395800101 = 0;
        int64_t addr_395900101 = 72245772LL, strd_395900101 = 0;
        int64_t addr_397100101 = 57141880LL;
block24:
        goto block27;

block28:
        //Small tile
        WRITE_4b(addr_397100101);
        addr_397100101 += (57141884LL - 57141880LL);

        goto block27;

block27:
        //Small tile
        READ_4b(addr_395700101);
        switch(addr_395700101) {
            case 72245700LL : strd_395700101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395700101 = (72245700LL - 72245820LL); break;
            case 72245760LL : strd_395700101 = (72245764LL - 72245760LL); break;
        }
        addr_395700101 += strd_395700101;

        //Small tile
        READ_4b(addr_395800101);
        switch(addr_395800101) {
            case 72245700LL : strd_395800101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395800101 = (72245700LL - 72245820LL); break;
            case 72245772LL : strd_395800101 = (72245776LL - 72245772LL); break;
        }
        addr_395800101 += strd_395800101;

        //Small tile
        WRITE_4b(addr_395900101);
        switch(addr_395900101) {
            case 72245700LL : strd_395900101 = (72245704LL - 72245700LL); break;
            case 72245820LL : strd_395900101 = (72245700LL - 72245820LL); break;
            case 72245772LL : strd_395900101 = (72245776LL - 72245772LL); break;
        }
        addr_395900101 += strd_395900101;

        //Few edges. Don't bother optimizing
        static uint64_t out_27 = 0;
        out_27++;
        if (out_27 <= 3571415LL) goto block28;
        else goto block29;


block29:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_401100101 = 72003600LL, strd_401100101 = 0;
        int64_t addr_402800101 = 240016LL;
        int64_t addr_403200101 = 72249360LL, strd_403200101 = 0;
        int64_t addr_401800101 = 72003604LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72003600LL, strd_403600101 = 0;
block30:
        goto block31;

block37:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder zero for all out blocks...
        static uint64_t out_37 = 0;
        out_37 = (out_37 == 43312LL) ? 1 : (out_37 + 1);
        if (out_37 <= 43311LL) goto block32;
        else goto block35;


block36:
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
        static uint64_t out_36_37 = 1342670LL;
        static uint64_t out_36_32 = 1589998LL;
        static uint64_t out_36_35 = 18LL;
        tmpRnd = out_36_37 + out_36_32 + out_36_35;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_36_37)){
                out_36_37--;
                goto block37;
            }
            else if (tmpRnd < (out_36_37 + out_36_32)){
                out_36_32--;
                goto block32;
            }
            else {
                out_36_35--;
                goto block35;
            }
        }
        goto block37;


block31:
        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_31 = 0;
        cov_31++;
        if(cov_31 <= 2932699ULL) {
            static uint64_t out_31 = 0;
            out_31 = (out_31 == 59851LL) ? 1 : (out_31 + 1);
            if (out_31 <= 1LL) goto block32;
            else goto block36;
        }
        else goto block36;

block32:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        //Unordered
        static uint64_t out_32_33 = 896207LL;
        static uint64_t out_32_35 = 2036480LL;
        tmpRnd = out_32_33 + out_32_35;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_32_33)){
                out_32_33--;
                goto block33;
            }
            else {
                out_32_35--;
                goto block35;
            }
        }
        goto block38;


block33:
        //Random
        addr = (bounded_rnd(72489360LL - 72003604LL) + 72003604LL) & ~3ULL;
        READ_4b(addr);

        goto block35;

block35:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (240020LL - 240016LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        goto block31;

block38:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_401100101 = 72214544LL, strd_401100101 = 0;
        int64_t addr_402800101 = 11970956LL;
        int64_t addr_403200101 = 72460300LL, strd_403200101 = 0;
        int64_t addr_403600101 = 72214540LL, strd_403600101 = 0;
        int64_t addr_401800101 = 72214548LL, strd_401800101 = 0;
block39:
        goto block42;

block45:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72214548LL : strd_401800101 = (72214552LL - 72214548LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block42;

block44:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_44 = 0;
        cov_44++;
        if(cov_44 <= 1409274ULL) {
            static uint64_t out_44 = 0;
            out_44 = (out_44 == 40265LL) ? 1 : (out_44 + 1);
            if (out_44 <= 40264LL) goto block45;
            else goto block42;
        }
        else goto block45;

block43:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72214540LL : strd_403600101 = (72214544LL - 72214540LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_43_45 = 1664392LL;
        static uint64_t out_43_44 = 1409282LL;
        static uint64_t out_43_42 = 18LL;
        tmpRnd = out_43_45 + out_43_44 + out_43_42;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_43_45)){
                out_43_45--;
                goto block45;
            }
            else if (tmpRnd < (out_43_45 + out_43_44)){
                out_43_44--;
                goto block44;
            }
            else {
                out_43_42--;
                goto block42;
            }
        }
        goto block46;


block42:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (11970960LL - 11970956LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72460300LL : strd_403200101 = (72460304LL - 72460300LL); break;
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72214544LL : strd_401100101 = (72214548LL - 72214544LL); break;
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_42 = 0;
        cov_42++;
        if(cov_42 <= 3073734ULL) {
            static uint64_t out_42 = 0;
            out_42 = (out_42 == 57995LL) ? 1 : (out_42 + 1);
            if (out_42 <= 57994LL) goto block43;
            else goto block45;
        }
        else goto block43;

block46:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_402800101 = 24265936LL;
        int64_t addr_401100101 = 72029524LL, strd_401100101 = 0;
        int64_t addr_403200101 = 72275280LL, strd_403200101 = 0;
        int64_t addr_401800101 = 72029524LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72029520LL, strd_403600101 = 0;
block47:
        goto block48;

block53:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_53 = 0;
        cov_53++;
        if(cov_53 <= 1409075ULL) {
            static uint64_t out_53 = 0;
            out_53 = (out_53 == 52188LL) ? 1 : (out_53 + 1);
            if (out_53 <= 52187LL) goto block48;
            else goto block49;
        }
        else goto block48;

block52:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72029520LL : strd_403600101 = (72029524LL - 72029520LL); break;
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_52_53 = 1409089LL;
        static uint64_t out_52_48 = 1664534LL;
        static uint64_t out_52_49 = 25LL;
        tmpRnd = out_52_53 + out_52_48 + out_52_49;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_52_53)){
                out_52_53--;
                goto block53;
            }
            else if (tmpRnd < (out_52_53 + out_52_48)){
                out_52_48--;
                goto block48;
            }
            else {
                out_52_49--;
                goto block49;
            }
        }
        goto block53;


block48:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72029524LL : strd_401800101 = (72029528LL - 72029524LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block49;

block49:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (24265940LL - 24265936LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_49 = 0;
        out_49++;
        if (out_49 <= 3073700LL) goto block51;
        else goto block54;


block51:
        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72275280LL : strd_403200101 = (72275284LL - 72275280LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72029524LL : strd_401100101 = (72029528LL - 72029524LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_51 = 0;
        cov_51++;
        if(cov_51 <= 3073667ULL) {
            static uint64_t out_51 = 0;
            out_51 = (out_51 == 59109LL) ? 1 : (out_51 + 1);
            if (out_51 <= 59108LL) goto block52;
            else goto block48;
        }
        else goto block52;

block54:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_401100101 = 72330084LL, strd_401100101 = 0;
        int64_t addr_403200101 = 72084320LL, strd_403200101 = 0;
        int64_t addr_402800101 = 36560740LL;
        int64_t addr_401800101 = 72330088LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72330080LL, strd_403600101 = 0;
block55:
        goto block57;

block57:
        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72084320LL : strd_403200101 = (72084324LL - 72084320LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72330084LL : strd_401100101 = (72330088LL - 72330084LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_57 = 0;
        cov_57++;
        if(cov_57 <= 3073771ULL) {
            static uint64_t out_57 = 0;
            out_57 = (out_57 == 59111LL) ? 1 : (out_57 + 1);
            if (out_57 <= 59110LL) goto block58;
            else goto block60;
        }
        else goto block58;

block61:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (36560744LL - 36560740LL);

        goto block57;

block60:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72330088LL : strd_401800101 = (72330092LL - 72330088LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_60 = 0;
        out_60++;
        if (out_60 <= 3073742LL) goto block61;
        else goto block62;


block59:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_59 = 0;
        cov_59++;
        if(cov_59 <= 1408471ULL) {
            static uint64_t out_59 = 0;
            out_59 = (out_59 == 54172LL) ? 1 : (out_59 + 1);
            if (out_59 <= 54171LL) goto block60;
            else goto block61;
        }
        else goto block60;

block58:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72330080LL : strd_403600101 = (72330084LL - 72330080LL); break;
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_58_61 = 26LL;
        static uint64_t out_58_60 = 1665234LL;
        static uint64_t out_58_59 = 1408482LL;
        tmpRnd = out_58_61 + out_58_60 + out_58_59;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_58_61)){
                out_58_61--;
                goto block61;
            }
            else if (tmpRnd < (out_58_61 + out_58_60)){
                out_58_60--;
                goto block60;
            }
            else {
                out_58_59--;
                goto block59;
            }
        }
        goto block59;


block62:
        int dummy;
    }

    // Interval: 900000000 - 1000000000
    {
        int64_t addr_401100101 = 72139500LL, strd_401100101 = 0;
        int64_t addr_402800101 = 48855912LL;
        int64_t addr_403200101 = 72385256LL, strd_403200101 = 0;
        int64_t addr_403600101 = 72139496LL, strd_403600101 = 0;
        int64_t addr_401800101 = 72139504LL, strd_401800101 = 0;
block63:
        goto block66;

block69:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_69 = 0;
        cov_69++;
        if(cov_69 <= 1409407ULL) {
            static uint64_t out_69 = 0;
            out_69 = (out_69 == 44044LL) ? 1 : (out_69 + 1);
            if (out_69 <= 44043LL) goto block68;
            else goto block66;
        }
        else goto block68;

block68:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72139504LL : strd_401800101 = (72139508LL - 72139504LL); break;
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block66;

block66:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (48855916LL - 48855912LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72385256LL : strd_403200101 = (72385260LL - 72385256LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72139500LL : strd_401100101 = (72139504LL - 72139500LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_66 = 0;
        cov_66++;
        if(cov_66 <= 3073667ULL) {
            static uint64_t out_66 = 0;
            out_66 = (out_66 == 59109LL) ? 1 : (out_66 + 1);
            if (out_66 <= 59108LL) goto block67;
            else goto block68;
        }
        else goto block67;

block67:
        //Small tile
        READ_4b(addr_403600101);
        switch(addr_403600101) {
            case 72003600LL : strd_403600101 = (72003604LL - 72003600LL); break;
            case 72489352LL : strd_403600101 = (72003600LL - 72489352LL); break;
            case 72243592LL : strd_403600101 = (72249360LL - 72243592LL); break;
            case 72249360LL : strd_403600101 = (72249364LL - 72249360LL); break;
            case 72139496LL : strd_403600101 = (72139500LL - 72139496LL); break;
        }
        addr_403600101 += strd_403600101;

        //Unordered
        static uint64_t out_67_69 = 1409418LL;
        static uint64_t out_67_68 = 1664181LL;
        static uint64_t out_67_66 = 20LL;
        tmpRnd = out_67_69 + out_67_68 + out_67_66;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_67_69)){
                out_67_69--;
                goto block69;
            }
            else if (tmpRnd < (out_67_69 + out_67_68)){
                out_67_68--;
                goto block68;
            }
            else {
                out_67_66--;
                goto block66;
            }
        }
        goto block70;


block70:
        int dummy;
    }

    // Interval: 1000000000 - 1088244838
    {
        int64_t addr_402800101 = 61150596LL;
        int64_t addr_403200101 = 72194180LL, strd_403200101 = 0;
        int64_t addr_401100101 = 72439944LL, strd_401100101 = 0;
        int64_t addr_401800101 = 72439944LL, strd_401800101 = 0;
        int64_t addr_403600101 = 72439940LL, strd_403600101 = 0;
block71:
        goto block72;

block77:
        //Random
        addr = (bounded_rnd(72489356LL - 72003600LL) + 72003600LL) & ~3ULL;
        READ_4b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_77 = 0;
        cov_77++;
        if(cov_77 <= 1243161ULL) {
            static uint64_t out_77 = 0;
            out_77 = (out_77 == 46043LL) ? 1 : (out_77 + 1);
            if (out_77 <= 46042LL) goto block72;
            else goto block74;
        }
        else goto block72;

block74:
        //Small tile
        READ_4b(addr_402800101);
        addr_402800101 += (61150600LL - 61150596LL);

        //Small tile
        WRITE_4b(addr_403200101);
        switch(addr_403200101) {
            case 72003600LL : strd_403200101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_403200101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_403200101 = (72249364LL - 72249360LL); break;
            case 72194180LL : strd_403200101 = (72194184LL - 72194180LL); break;
            case 72489356LL : strd_403200101 = (72003600LL - 72489356LL); break;
        }
        addr_403200101 += strd_403200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_74 = 0;
        out_74++;
        if (out_74 <= 2712354LL) goto block75;
        else goto block78;


block76:
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
        static uint64_t out_76_77 = 1243174LL;
        static uint64_t out_76_74 = 19LL;
        static uint64_t out_76_72 = 1469115LL;
        tmpRnd = out_76_77 + out_76_74 + out_76_72;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_76_77)){
                out_76_77--;
                goto block77;
            }
            else if (tmpRnd < (out_76_77 + out_76_74)){
                out_76_74--;
                goto block74;
            }
            else {
                out_76_72--;
                goto block72;
            }
        }
        goto block77;


block72:
        //Small tile
        READ_4b(addr_401800101);
        switch(addr_401800101) {
            case 72439944LL : strd_401800101 = (72439948LL - 72439944LL); break;
            case 72243596LL : strd_401800101 = (72249364LL - 72243596LL); break;
            case 72249364LL : strd_401800101 = (72249368LL - 72249364LL); break;
            case 72003604LL : strd_401800101 = (72003608LL - 72003604LL); break;
            case 72489356LL : strd_401800101 = (72003604LL - 72489356LL); break;
        }
        addr_401800101 += strd_401800101;

        goto block74;

block75:
        //Small tile
        READ_4b(addr_401100101);
        switch(addr_401100101) {
            case 72439944LL : strd_401100101 = (72439948LL - 72439944LL); break;
            case 72003600LL : strd_401100101 = (72003604LL - 72003600LL); break;
            case 72243596LL : strd_401100101 = (72249360LL - 72243596LL); break;
            case 72249360LL : strd_401100101 = (72249364LL - 72249360LL); break;
            case 72489356LL : strd_401100101 = (72003600LL - 72489356LL); break;
        }
        addr_401100101 += strd_401100101;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_75 = 0;
        cov_75++;
        if(cov_75 <= 2712343ULL) {
            static uint64_t out_75 = 0;
            out_75 = (out_75 == 58964LL) ? 1 : (out_75 + 1);
            if (out_75 <= 58963LL) goto block76;
            else goto block72;
        }
        else goto block76;

block78:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
