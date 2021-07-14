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
    uint64_t allocSize = 3067904ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 100000000
    {
        int64_t addr_541000101 = 90128LL;
        int64_t addr_541500101 = 90128LL;
        int64_t addr_543900101 = 2923760LL;
        int64_t addr_543700101 = 90128LL;
        int64_t addr_544800101 = 2923760LL;
        int64_t addr_544600101 = 90128LL;
block0:
        goto block4;

block17:
        //Random
        addr = (bounded_rnd(3054096LL - 3052088LL) + 3052088LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3054088LL - 3052080LL) + 3052080LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_17 = 0;
        cov_17++;
        if(cov_17 <= 566972ULL) {
            static uint64_t out_17 = 0;
            out_17 = (out_17 == 69LL) ? 1 : (out_17 + 1);
            if (out_17 <= 68LL) goto block10;
            else goto block8;
        }
        else goto block10;

block18:
        //Random
        addr = (bounded_rnd(3054096LL - 3052088LL) + 3052088LL) & ~7ULL;
        READ_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_18 = 0;
        out_18++;
        if (out_18 <= 516533LL) goto block19;
        else goto block20;


block19:
        //Random
        addr = (bounded_rnd(3054088LL - 3052080LL) + 3052080LL) & ~7ULL;
        READ_8b(addr);

        goto block12;

block15:
        //Random
        addr = (bounded_rnd(3064640LL - 3061048LL) + 3061048LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064624LL - 3061032LL) + 3061032LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064648LL - 3061056LL) + 3061056LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_15_17 = 567947LL;
        static uint64_t out_15_10 = 22434LL;
        static uint64_t out_15_8 = 401LL;
        tmpRnd = out_15_17 + out_15_10 + out_15_8;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_15_17)){
                out_15_17--;
                goto block17;
            }
            else if (tmpRnd < (out_15_17 + out_15_10)){
                out_15_10--;
                goto block10;
            }
            else {
                out_15_8--;
                goto block8;
            }
        }
        goto block17;


block12:
        //Small tile
        READ_4b(addr_544600101);
        addr_544600101 += (90132LL - 90128LL);

        //Dominant stride
        READ_4b(addr_544800101);
        addr_544800101 += 12LL;
        if(addr_544800101 >= 2983692LL) addr_544800101 = 2916080LL;

        //Unordered
        static uint64_t out_12_15 = 590778LL;
        static uint64_t out_12_10 = 33599LL;
        static uint64_t out_12_8 = 438LL;
        tmpRnd = out_12_15 + out_12_10 + out_12_8;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_12_15)){
                out_12_15--;
                goto block15;
            }
            else if (tmpRnd < (out_12_15 + out_12_10)){
                out_12_10--;
                goto block10;
            }
            else {
                out_12_8--;
                goto block8;
            }
        }
        goto block15;


block10:
        //Small tile
        READ_4b(addr_543700101);
        addr_543700101 += (90132LL - 90128LL);

        //Dominant stride
        READ_4b(addr_543900101);
        addr_543900101 += 12LL;
        if(addr_543900101 >= 2983692LL) addr_543900101 = 2916080LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_10 = 0;
        cov_10++;
        if(cov_10 <= 572621ULL) {
            static uint64_t out_10 = 0;
            out_10 = (out_10 == 7LL) ? 1 : (out_10 + 1);
            if (out_10 <= 1LL) goto block12;
            else goto block18;
        }
        else if (cov_10 <= 599138ULL) goto block12;
        else goto block18;

block8:
        for(uint64_t loop0 = 0; loop0 < 69ULL; loop0++){
            //Loop Indexed
            addr = 1112LL + (16 * loop0);
            READ_8b(addr);

            //Loop Indexed
            addr = 1104LL + (16 * loop0);
            READ_8b(addr);

            //Small tile
            WRITE_4b(addr_541000101);
            addr_541000101 += (90132LL - 90128LL);

            //Small tile
            READ_4b(addr_541500101);
            addr_541500101 += (90132LL - 90128LL);

        }
        goto block10;

block4:
        for(uint64_t loop3 = 0; loop3 < 49152ULL; loop3++){
            //Loop Indexed
            addr = 2850832LL + (4 * loop3);
            READ_4b(addr);

        }
        for(uint64_t loop2 = 0; loop2 < 49152ULL; loop2++){
            //Loop Indexed
            addr = 2850832LL + (4 * loop2);
            READ_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 46004ULL; loop1++){
            //Random
            addr = (bounded_rnd(3056328LL - 3054288LL) + 3054288LL) & ~7ULL;
            READ_8b(addr);

            //Random
            addr = (bounded_rnd(3056336LL - 3054296LL) + 3054296LL) & ~7ULL;
            READ_8b(addr);

        }
        goto block8;

block20:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_572100101 = 7184LL;
block21:
        goto block22;

block22:
        for(uint64_t loop4 = 0; loop4 < 12833019ULL; loop4++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 49584LL) addr_572100101 = 7184LL;

        }
        goto block23;

block23:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_572100101 = 10432LL;
block24:
        goto block25;

block25:
        for(uint64_t loop5 = 0; loop5 < 14275748ULL; loop5++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 70352LL) addr_572100101 = 7184LL;

        }
        goto block26;

block26:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_572100101 = 58200LL;
block27:
        goto block28;

block28:
        for(uint64_t loop6 = 0; loop6 < 14278217ULL; loop6++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 84256LL) addr_572100101 = 7184LL;

        }
        goto block29;

block29:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_572100101 = 7608LL;
block30:
        goto block31;

block33:
        for(uint64_t loop7 = 0; loop7 < 69ULL; loop7++){
            //Loop Indexed
            addr = 1112LL + (16 * loop7);
            READ_8b(addr);

            //Loop Indexed
            addr = 1104LL + (16 * loop7);
            READ_8b(addr);

        }
        goto block36;

block31:
        for(uint64_t loop8 = 0; loop8 < 10023703ULL; loop8++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 86768LL) addr_572100101 = 7184LL;

        }
        goto block33;

block36:
        //Random
        addr = (bounded_rnd(3064640LL - 3061048LL) + 3061048LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064624LL - 3061032LL) + 3061032LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064648LL - 3061056LL) + 3061056LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_36_33 = 172LL;
        static uint64_t out_36_36 = 12563LL;
        static uint64_t out_36_38 = 175270LL;
        tmpRnd = out_36_33 + out_36_36 + out_36_38;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_36_33)){
                out_36_33--;
                goto block33;
            }
            else if (tmpRnd < (out_36_33 + out_36_36)){
                out_36_36--;
                goto block36;
            }
            else {
                out_36_38--;
                goto block38;
            }
        }
        goto block38;


block38:
        //Random
        addr = (bounded_rnd(3054096LL - 3052088LL) + 3052088LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3054088LL - 3052080LL) + 3052080LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_38_33 = 2662LL;
        static uint64_t out_38_36 = 172814LL;
        tmpRnd = out_38_33 + out_38_36;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_38_33)){
                out_38_33--;
                goto block33;
            }
            else {
                out_38_36--;
                goto block36;
            }
        }
        goto block39;


block39:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_572100101 = 7184LL;
        int64_t addr_544600101 = 872584LL;
        int64_t addr_544800101 = 2972940LL;
        int64_t addr_543900101 = 2951388LL;
        int64_t addr_543700101 = 872588LL;
block40:
        goto block42;

block47:
        //Random
        addr = (bounded_rnd(3054096LL - 3052088LL) + 3052088LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3054088LL - 3052080LL) + 3052080LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_47_49 = 6623LL;
        static uint64_t out_47_51 = 435573LL;
        tmpRnd = out_47_49 + out_47_51;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_47_49)){
                out_47_49--;
                goto block49;
            }
            else {
                out_47_51--;
                goto block51;
            }
        }
        goto block52;


block49:
        for(uint64_t loop9 = 0; loop9 < 69ULL; loop9++){
            //Loop Indexed
            addr = 1112LL + (16 * loop9);
            READ_8b(addr);

            //Loop Indexed
            addr = 1104LL + (16 * loop9);
            READ_8b(addr);

        }
        goto block51;

block45:
        //Random
        addr = (bounded_rnd(3064640LL - 3061048LL) + 3061048LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064624LL - 3061032LL) + 3061032LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(3064648LL - 3061056LL) + 3061056LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_45_47 = 442188LL;
        static uint64_t out_45_49 = 380LL;
        static uint64_t out_45_51 = 32394LL;
        tmpRnd = out_45_47 + out_45_49 + out_45_51;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_45_47)){
                out_45_47--;
                goto block47;
            }
            else if (tmpRnd < (out_45_47 + out_45_49)){
                out_45_49--;
                goto block49;
            }
            else {
                out_45_51--;
                goto block51;
            }
        }
        goto block47;


block42:
        //Small tile
        READ_4b(addr_544600101);
        addr_544600101 += (872588LL - 872584LL);

        //Dominant stride
        READ_4b(addr_544800101);
        addr_544800101 += 12LL;
        if(addr_544800101 >= 2989840LL) addr_544800101 = 2917584LL;

        //Unordered
        static uint64_t out_42_49 = 162LL;
        static uint64_t out_42_45 = 474964LL;
        static uint64_t out_42_51 = 19253LL;
        tmpRnd = out_42_49 + out_42_45 + out_42_51;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_42_49)){
                out_42_49--;
                goto block49;
            }
            else if (tmpRnd < (out_42_49 + out_42_45)){
                out_42_45--;
                goto block45;
            }
            else {
                out_42_51--;
                goto block51;
            }
        }
        goto block45;


block51:
        //Small tile
        READ_4b(addr_543700101);
        addr_543700101 += (872592LL - 872588LL);

        //Dominant stride
        READ_4b(addr_543900101);
        addr_543900101 += 12LL;
        if(addr_543900101 >= 2989840LL) addr_543900101 = 2917584LL;

        goto block42;

block52:
        for(uint64_t loop10 = 0; loop10 < 4278894ULL; loop10++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 28656LL) addr_572100101 = 7184LL;

        }
        goto block53;

block53:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_572100101 = 16080LL;
block54:
        goto block55;

block55:
        for(uint64_t loop11 = 0; loop11 < 14270702ULL; loop11++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 56920LL) addr_572100101 = 7184LL;

        }
        goto block56;

block56:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_572100101 = 17624LL;
block57:
        goto block58;

block58:
        for(uint64_t loop12 = 0; loop12 < 14276265ULL; loop12++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 69528LL) addr_572100101 = 7184LL;

        }
        goto block59;

block59:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_572100101 = 59320LL;
block60:
        goto block61;

block61:
        for(uint64_t loop13 = 0; loop13 < 14278208ULL; loop13++){
            //Dominant stride
            READ_8b(addr_572100101);
            addr_572100101 += 8LL;
            if(addr_572100101 >= 79936LL) addr_572100101 = 7184LL;

        }
        goto block62;

block62:
        int dummy;
    }

    // Interval: 900000000 - 929120958
    {
        int64_t addr_572100101 = 71712LL, strd_572100101 = 0;
block63:
        goto block64;

block64:
        for(uint64_t loop14 = 0; loop14 < 4128756ULL; loop14++){
            //Small tile
            READ_8b(addr_572100101);
            switch(addr_572100101) {
                case 79928LL : strd_572100101 = (7184LL - 79928LL); break;
                case 7184LL : strd_572100101 = (7192LL - 7184LL); break;
                case 71712LL : strd_572100101 = (71720LL - 71712LL); break;
                case 82256LL : strd_572100101 = (7184LL - 82256LL); break;
            }
            addr_572100101 += strd_572100101;

        }
        goto block65;

block65:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
