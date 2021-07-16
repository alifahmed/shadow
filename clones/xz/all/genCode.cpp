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
    uint64_t allocSize = 22974464ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1534820466
    {
        int64_t addr_1013100101 = 22954496LL;
        int64_t addr_632600101 = 9760783LL;
        int64_t addr_659200101 = 24592LL;
        int64_t addr_1026600101 = 13221920LL;
        int64_t addr_1026700101 = 13221952LL;
        int64_t addr_1026800101 = 13221984LL;
        int64_t addr_1026900101 = 13222016LL;
        int64_t addr_459200201 = 22962560LL;
        int64_t addr_459100201 = 22962592LL;
        int64_t addr_459000201 = 22962624LL;
        int64_t addr_458500201 = 32736LL;
        int64_t addr_458900201 = 22962656LL;
        int64_t addr_458600201 = 32704LL;
        int64_t addr_458800201 = 32640LL;
        int64_t addr_458700201 = 32672LL;
        int64_t addr_405100201 = 24864LL;
        int64_t addr_405000201 = 24848LL;
        int64_t addr_458700101 = 9772960LL;
        int64_t addr_458800101 = 9772928LL;
block0:
        goto block4;

block48:
        static int64_t loop0_break = 2432703ULL;
        for(uint64_t loop0 = 0; loop0 < 1513ULL; loop0++){
            if(loop0_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_1013100101);
            addr_1013100101 += 4LL;
            if(addr_1013100101 >= 22962688LL) addr_1013100101 = 22954496LL;

            //Random
            addr = (bounded_rnd(9792LL - 7744LL) + 7744LL) & ~7ULL;
            READ_8b(addr);

            //Random
            addr = (bounded_rnd(7744LL - 5696LL) + 5696LL) & ~7ULL;
            READ_8b(addr);

            //Random
            addr = (bounded_rnd(5696LL - 3648LL) + 3648LL) & ~7ULL;
            READ_8b(addr);

            //Random
            addr = (bounded_rnd(3648LL - 1600LL) + 1600LL) & ~7ULL;
            READ_8b(addr);

        }
        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_48 = 0;
        cov_48++;
        if(cov_48 <= 1262ULL) {
            static uint64_t out_48 = 0;
            out_48 = (out_48 == 3LL) ? 1 : (out_48 + 1);
            if (out_48 <= 2LL) goto block56;
            else goto block4;
        }
        else goto block56;

block56:
        for(uint64_t loop1 = 0; loop1 < 63ULL; loop1++){
            //Loop Indexed
            addr = 22954496LL + (128 * loop1);
            READ_32b(addr);

            //Loop Indexed
            addr = 22954528LL + (128 * loop1);
            READ_32b(addr);

            //Loop Indexed
            addr = 22954560LL + (128 * loop1);
            READ_32b(addr);

            //Loop Indexed
            addr = 22954592LL + (128 * loop1);
            READ_32b(addr);

            //Dominant stride
            WRITE_32b(addr_1026600101);
            addr_1026600101 += 128LL;
            if(addr_1026600101 >= 22953792LL) addr_1026600101 = 13221920LL;

            //Dominant stride
            WRITE_32b(addr_1026700101);
            addr_1026700101 += 128LL;
            if(addr_1026700101 >= 22953824LL) addr_1026700101 = 13221952LL;

            //Dominant stride
            WRITE_32b(addr_1026800101);
            addr_1026800101 += 128LL;
            if(addr_1026800101 >= 22953856LL) addr_1026800101 = 13221984LL;

            //Dominant stride
            WRITE_32b(addr_1026900101);
            addr_1026900101 += 128LL;
            if(addr_1026900101 >= 22953888LL) addr_1026900101 = 13222016LL;

        }
        //Unordered
        static uint64_t out_56_31 = 108LL;
        static uint64_t out_56_35 = 170LL;
        static uint64_t out_56_5 = 903LL;
        static uint64_t out_56_4 = 1LL;
        tmpRnd = out_56_31 + out_56_35 + out_56_5 + out_56_4;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_56_31)){
                out_56_31--;
                goto block31;
            }
            else if (tmpRnd < (out_56_31 + out_56_35)){
                out_56_35--;
                goto block35;
            }
            else if (tmpRnd < (out_56_31 + out_56_35 + out_56_5)){
                out_56_5--;
                goto block5;
            }
            else {
                out_56_4--;
                goto block4;
            }
        }
        goto block5;


block24:
        //Random
        addr = (bounded_rnd(17696LL - 13028LL) + 13028LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17696LL - 13028LL) + 13028LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17696LL - 13028LL) + 13028LL) & ~1ULL;
        WRITE_2b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_24 = 0;
        cov_24++;
        if(cov_24 <= 2508263ULL) {
            static uint64_t out_24 = 0;
            out_24 = (out_24 == 76008LL) ? 1 : (out_24 + 1);
            if (out_24 <= 76007LL) goto block17;
            else goto block43;
        }
        else goto block17;

block27:
        //Random
        addr = (bounded_rnd(17886LL - 13160LL) + 13160LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17886LL - 13160LL) + 13160LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17886LL - 13160LL) + 13160LL) & ~1ULL;
        WRITE_2b(addr);

        goto block21;

block31:
        //Random
        addr = (bounded_rnd(9757488LL - 24592LL) + 24592LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(9757488LL - 24592LL) + 24592LL) & ~15ULL;
        READ_16b(addr);

        //Dominant stride
        WRITE_16b(addr_405000201);
        addr_405000201 += 64LL;
        if(addr_405000201 >= 9757680LL) addr_405000201 = 24848LL;

        //Dominant stride
        WRITE_16b(addr_405100201);
        addr_405100201 += 64LL;
        if(addr_405100201 >= 9757680LL) addr_405100201 = 24864LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_31 = 0;
        cov_31++;
        if(cov_31 <= 141539ULL) {
            static uint64_t out_31 = 0;
            out_31 = (out_31 == 1011LL) ? 1 : (out_31 + 1);
            if (out_31 <= 1010LL) goto block5;
            else goto block43;
        }
        else goto block5;

block35:
        //Random
        addr = (bounded_rnd(9755800LL - 24592LL) + 24592LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(9755800LL - 24592LL) + 24592LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(9757696LL - 26184LL) + 26184LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(9757696LL - 26184LL) + 26184LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_35_48 = 5LL;
        static uint64_t out_35_43 = 179LL;
        static uint64_t out_35_5 = 140663LL;
        tmpRnd = out_35_48 + out_35_43 + out_35_5;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_35_48)){
                out_35_48--;
                goto block48;
            }
            else if (tmpRnd < (out_35_48 + out_35_43)){
                out_35_43--;
                goto block43;
            }
            else {
                out_35_5--;
                goto block5;
            }
        }
        goto block5;


block43:
        //Dominant stride
        READ_32b(addr_458500201);
        addr_458500201 += -128LL;
        if(addr_458500201 < 24800LL) addr_458500201 = 9756640LL;

        //Dominant stride
        READ_32b(addr_458600201);
        addr_458600201 += -128LL;
        if(addr_458600201 < 24768LL) addr_458600201 = 9756608LL;

        //Dominant stride
        READ_32b(addr_458700201);
        addr_458700201 += -128LL;
        if(addr_458700201 < 24736LL) addr_458700201 = 9756576LL;

        //Dominant stride
        READ_32b(addr_458800201);
        addr_458800201 += -128LL;
        if(addr_458800201 < 24704LL) addr_458800201 = 9756544LL;

        //Dominant stride
        WRITE_32b(addr_458900201);
        addr_458900201 += -128LL;
        if(addr_458900201 < 22954624LL) addr_458900201 = 22962656LL;

        //Dominant stride
        WRITE_32b(addr_459000201);
        addr_459000201 += -128LL;
        if(addr_459000201 < 22954592LL) addr_459000201 = 22962624LL;

        //Dominant stride
        WRITE_32b(addr_459100201);
        addr_459100201 += -128LL;
        if(addr_459100201 < 22954560LL) addr_459100201 = 22962592LL;

        //Dominant stride
        WRITE_32b(addr_459200201);
        addr_459200201 += -128LL;
        if(addr_459200201 < 22954528LL) addr_459200201 = 22962560LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_43 = 0;
        cov_43++;
        if(cov_43 <= 74542ULL) {
            static uint64_t out_43 = 0;
            out_43 = (out_43 == 47LL) ? 1 : (out_43 + 1);
            if (out_43 <= 46LL) goto block43;
            else goto block48;
        }
        else if (cov_43 <= 74710ULL) goto block43;
        else goto block48;

block20:
        //Random
        addr = (bounded_rnd(17886LL - 13162LL) + 13162LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17886LL - 13162LL) + 13162LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17886LL - 13162LL) + 13162LL) & ~1ULL;
        WRITE_2b(addr);

        goto block21;

block21:
        //Dominant stride
        WRITE_1b(addr_659200101);
        addr_659200101 += 1LL;
        if(addr_659200101 >= 9757714LL) addr_659200101 = 24592LL;

        //Unordered
        static uint64_t out_21_48 = 8LL;
        static uint64_t out_21_43 = 634LL;
        static uint64_t out_21_5 = 4749422LL;
        tmpRnd = out_21_48 + out_21_43 + out_21_5;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_21_48)){
                out_21_48--;
                goto block48;
            }
            else if (tmpRnd < (out_21_48 + out_21_43)){
                out_21_43--;
                goto block43;
            }
            else {
                out_21_5--;
                goto block5;
            }
        }
        goto block5;


block17:
        //Random
        addr = (bounded_rnd(17886LL - 13160LL) + 13160LL) & ~1ULL;
        READ_2b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_17 = 0;
        cov_17++;
        if(cov_17 <= 3342768ULL) {
            static uint64_t out_17 = 0;
            out_17 = (out_17 == 3LL) ? 1 : (out_17 + 1);
            if (out_17 <= 2LL) goto block20;
            else goto block27;
        }
        else if (cov_17 <= 3351417ULL) goto block20;
        else goto block27;

block16:
        //Random
        addr = (bounded_rnd(17694LL - 13028LL) + 13028LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17694LL - 13028LL) + 13028LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17694LL - 13028LL) + 13028LL) & ~1ULL;
        WRITE_2b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_16 = 0;
        cov_16++;
        if(cov_16 <= 1950749ULL) {
            static uint64_t out_16 = 0;
            out_16 = (out_16 == 65025LL) ? 1 : (out_16 + 1);
            if (out_16 <= 65024LL) goto block17;
            else goto block43;
        }
        else goto block17;

block13:
        //Random
        addr = (bounded_rnd(17696LL - 13028LL) + 13028LL) & ~1ULL;
        READ_2b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_13 = 0;
        cov_13++;
        if(cov_13 <= 3292804ULL) {
            static uint64_t out_13 = 0;
            out_13 = (out_13 == 3LL) ? 1 : (out_13 + 1);
            if (out_13 <= 1LL) goto block16;
            else goto block24;
        }
        else if (cov_13 <= 3605881ULL) goto block24;
        else goto block16;

block12:
        //Random
        addr = (bounded_rnd(17600LL - 12962LL) + 12962LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17600LL - 12962LL) + 12962LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(17600LL - 12962LL) + 12962LL) & ~1ULL;
        WRITE_2b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_12 = 0;
        cov_12++;
        if(cov_12 <= 2518999ULL) {
            static uint64_t out_12 = 0;
            out_12 = (out_12 == 100760LL) ? 1 : (out_12 + 1);
            if (out_12 <= 100759LL) goto block13;
            else goto block43;
        }
        else goto block13;

block9:
        //Random
        addr = (bounded_rnd(21448LL - 21088LL) + 21088LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(21448LL - 21088LL) + 21088LL) & ~1ULL;
        READ_2b(addr);

        //Random
        addr = (bounded_rnd(21448LL - 21088LL) + 21088LL) & ~1ULL;
        WRITE_2b(addr);

        //Dominant stride
        READ_1b(addr_632600101);
        addr_632600101 += 1LL;
        if(addr_632600101 >= 9760784LL) addr_632600101 = 24592LL;

        //Unordered
        static uint64_t out_9_48 = 3LL;
        static uint64_t out_9_43 = 162LL;
        static uint64_t out_9_21 = 295582LL;
        static uint64_t out_9_13 = 1939945LL;
        static uint64_t out_9_12 = 2518930LL;
        tmpRnd = out_9_48 + out_9_43 + out_9_21 + out_9_13 + out_9_12;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_9_48)){
                out_9_48--;
                goto block48;
            }
            else if (tmpRnd < (out_9_48 + out_9_43)){
                out_9_43--;
                goto block43;
            }
            else if (tmpRnd < (out_9_48 + out_9_43 + out_9_21)){
                out_9_21--;
                goto block21;
            }
            else if (tmpRnd < (out_9_48 + out_9_43 + out_9_21 + out_9_13)){
                out_9_13--;
                goto block13;
            }
            else {
                out_9_12--;
                goto block12;
            }
        }
        goto block57;


block5:
        //Random
        addr = (bounded_rnd(21448LL - 21088LL) + 21088LL) & ~1ULL;
        READ_2b(addr);

        //Unordered
        static uint64_t out_5_48 = 5LL;
        static uint64_t out_5_31 = 141404LL;
        static uint64_t out_5_35 = 141286LL;
        static uint64_t out_5_43 = 388LL;
        static uint64_t out_5_9 = 4754611LL;
        static uint64_t out_5_5 = 63818LL;
        tmpRnd = out_5_48 + out_5_31 + out_5_35 + out_5_43 + out_5_9 + out_5_5;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_5_48)){
                out_5_48--;
                goto block48;
            }
            else if (tmpRnd < (out_5_48 + out_5_31)){
                out_5_31--;
                goto block31;
            }
            else if (tmpRnd < (out_5_48 + out_5_31 + out_5_35)){
                out_5_35--;
                goto block35;
            }
            else if (tmpRnd < (out_5_48 + out_5_31 + out_5_35 + out_5_43)){
                out_5_43--;
                goto block43;
            }
            else if (tmpRnd < (out_5_48 + out_5_31 + out_5_35 + out_5_43 + out_5_9)){
                out_5_9--;
                goto block9;
            }
            else {
                out_5_5--;
                goto block5;
            }
        }
        goto block9;


block4:
        for(uint64_t loop2 = 0; loop2 < 63ULL; loop2++){
            //Dominant stride
            READ_32b(addr_458700101);
            addr_458700101 += -128LL;
            if(addr_458700101 < 9765024LL) addr_458700101 = 13221792LL;

            //Dominant stride
            READ_32b(addr_458800101);
            addr_458800101 += -128LL;
            if(addr_458800101 < 9764992LL) addr_458800101 = 13221760LL;

            //Loop Indexed
            addr = 22970848LL + (-128 * loop2);
            WRITE_32b(addr);

            //Loop Indexed
            addr = 22970816LL + (-128 * loop2);
            WRITE_32b(addr);

        }
        //Unordered
        static uint64_t out_4_31 = 37LL;
        static uint64_t out_4_35 = 54LL;
        static uint64_t out_4_21 = 11LL;
        static uint64_t out_4_17 = 61LL;
        static uint64_t out_4_13 = 96LL;
        static uint64_t out_4_12 = 80LL;
        static uint64_t out_4_5 = 81LL;
        tmpRnd = out_4_31 + out_4_35 + out_4_21 + out_4_17 + out_4_13 + out_4_12 + out_4_5;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_4_31)){
                out_4_31--;
                goto block31;
            }
            else if (tmpRnd < (out_4_31 + out_4_35)){
                out_4_35--;
                goto block35;
            }
            else if (tmpRnd < (out_4_31 + out_4_35 + out_4_21)){
                out_4_21--;
                goto block21;
            }
            else if (tmpRnd < (out_4_31 + out_4_35 + out_4_21 + out_4_17)){
                out_4_17--;
                goto block17;
            }
            else if (tmpRnd < (out_4_31 + out_4_35 + out_4_21 + out_4_17 + out_4_13)){
                out_4_13--;
                goto block13;
            }
            else if (tmpRnd < (out_4_31 + out_4_35 + out_4_21 + out_4_17 + out_4_13 + out_4_12)){
                out_4_12--;
                goto block12;
            }
            else {
                out_4_5--;
                goto block5;
            }
        }
        goto block13;


block57:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
