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
    uint64_t allocSize = 134062080ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 200000000
    {
        int64_t addr_375300101 = 67149848LL;
        int64_t addr_374700101 = 4116LL, strd_374700101 = 0;
block0:
        goto block4;

block4:
        for(uint64_t loop1 = 0; loop1 < 16785409ULL; loop1++){
            //Loop Indexed
            addr = 4112LL + (4 * loop1);
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 4090654ULL; loop0++){
            //Small tile
            READ_4b(addr_374700101);
            switch(addr_374700101) {
                case 4116LL : strd_374700101 = (4120LL - 4116LL); break;
                case 20496LL : strd_374700101 = (4116LL - 20496LL); break;
            }
            addr_374700101 += strd_374700101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375300101);
            addr_375300101 += 4LL;
            if(addr_375300101 >= 83516456LL) addr_375300101 = 67149848LL;

        }
        goto block5;

block5:
        int dummy;
    }

    // Interval: 200000000 - 400000000
    {
        int64_t addr_374700101 = 15500LL, strd_374700101 = 0;
        int64_t addr_375300101 = 83516456LL;
block6:
        goto block9;

block9:
        for(uint64_t loop2 = 0; loop2 < 12498856ULL; loop2++){
            //Small tile
            READ_4b(addr_374700101);
            switch(addr_374700101) {
                case 15500LL : strd_374700101 = (15504LL - 15500LL); break;
                case 20496LL : strd_374700101 = (4116LL - 20496LL); break;
                case 4116LL : strd_374700101 = (4120LL - 4116LL); break;
            }
            addr_374700101 += strd_374700101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375300101);
            addr_375300101 += 4LL;
            if(addr_375300101 >= 133524088LL) addr_375300101 = 83516456LL;

        }
        goto block10;

block10:
        int dummy;
    }

    // Interval: 400000000 - 600000000
    {
        int64_t addr_408100101 = 4112LL;
        int64_t addr_406500101 = 67149848LL;
        int64_t addr_409100101 = 134060676LL;
        int64_t addr_409500101 = 134060740LL;
        int64_t addr_409900101 = 134060672LL;
        int64_t addr_410200101 = 134059648LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134060744LL;
        int64_t addr_413500101 = 134060744LL;
        int64_t addr_413600101 = 20504LL;
block11:
        goto block15;

block22:
        for(uint64_t loop3 = 0; loop3 < 256ULL; loop3++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134061828LL) addr_413500101 = 134060744LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 39073172LL) addr_413600101 = 20504LL;

        }
        goto block15;

block20:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134061828LL) addr_412000101 = 134060744LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_20 = 0;
        cov_20++;
        if(cov_20 <= 2817749ULL) {
            static uint64_t out_20 = 0;
            out_20 = (out_20 == 255LL) ? 1 : (out_20 + 1);
            if (out_20 <= 254LL) goto block19;
            else goto block22;
        }
        else goto block19;

block19:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134061760LL) addr_409100101 = 134060676LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134061824LL) addr_409500101 = 134060740LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134061756LL) addr_409900101 = 134060672LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134060668LL : strd_410200101 = (134059648LL - 134060668LL); break;
            case 134059648LL : strd_410200101 = (134059652LL - 134059648LL); break;
        }
        addr_410200101 += strd_410200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_19 = 0;
        out_19++;
        if (out_19 <= 2828654LL) goto block20;
        else goto block23;


block15:
        for(uint64_t loop5 = 0; loop5 < 256ULL; loop5++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 106202516LL) addr_406500101 = 67149848LL;

            //Loop Indexed
            addr = 134059648LL + (4 * loop5);
            WRITE_4b(addr);

        }
        for(uint64_t loop4 = 0; loop4 < 289ULL; loop4++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 39073172LL) addr_408100101 = 4112LL;

            //Loop Indexed
            addr = 134060672LL + (4 * loop4);
            WRITE_4b(addr);

        }
        goto block19;

block23:
        int dummy;
    }

    // Interval: 600000000 - 800000000
    {
        int64_t addr_408100101 = 32519440LL;
        int64_t addr_412000101 = 134061208LL;
        int64_t addr_409100101 = 134061144LL;
        int64_t addr_409500101 = 134061208LL;
        int64_t addr_409900101 = 134061140LL;
        int64_t addr_410200101 = 134060092LL, strd_410200101 = 0;
        int64_t addr_406500101 = 99665176LL;
        int64_t addr_413500101 = 134060744LL;
        int64_t addr_413600101 = 32797976LL;
block24:
        goto block25;

block25:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134061828LL) addr_412000101 = 134060744LL;

        //Unordered
        static uint64_t out_25_29 = 2861646LL;
        static uint64_t out_25_35 = 11222LL;
        tmpRnd = out_25_29 + out_25_35;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_25_29)){
                out_25_29--;
                goto block29;
            }
            else {
                out_25_35--;
                goto block35;
            }
        }
        goto block36;


block29:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134061760LL) addr_409100101 = 134060676LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134061824LL) addr_409500101 = 134060740LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134061756LL) addr_409900101 = 134060672LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134060668LL : strd_410200101 = (134059648LL - 134060668LL); break;
            case 134059648LL : strd_410200101 = (134059652LL - 134059648LL); break;
            case 134060092LL : strd_410200101 = (134060096LL - 134060092LL); break;
        }
        addr_410200101 += strd_410200101;

        goto block25;

block35:
        for(uint64_t loop8 = 0; loop8 < 256ULL; loop8++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134061828LL) addr_413500101 = 134060744LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 55330068LL) addr_413600101 = 29976LL;

        }
        for(uint64_t loop6 = 0; loop6 < 256ULL; loop6++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 122459412LL) addr_406500101 = 67159320LL;

            //Loop Indexed
            addr = 134059648LL + (4 * loop6);
            WRITE_4b(addr);

        }
        for(uint64_t loop7 = 0; loop7 < 289ULL; loop7++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 55330068LL) addr_408100101 = 13584LL;

            //Loop Indexed
            addr = 134060672LL + (4 * loop7);
            WRITE_4b(addr);

        }
        goto block29;

block36:
        int dummy;
    }

    // Interval: 800000000 - 1000000000
    {
        int64_t addr_408100101 = 24396944LL;
        int64_t addr_413500101 = 134060744LL;
        int64_t addr_413600101 = 24675480LL;
        int64_t addr_409100101 = 134061300LL;
        int64_t addr_409500101 = 134061364LL;
        int64_t addr_409900101 = 134061296LL;
        int64_t addr_410200101 = 134060236LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134061368LL;
        int64_t addr_406500101 = 91542680LL;
block37:
        goto block44;

block48:
        for(uint64_t loop10 = 0; loop10 < 256ULL; loop10++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 134049876LL) addr_406500101 = 67163288LL;

            //Loop Indexed
            addr = 134059648LL + (4 * loop10);
            WRITE_4b(addr);

        }
        for(uint64_t loop9 = 0; loop9 < 289ULL; loop9++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 67129428LL) addr_408100101 = 17552LL;

            //Loop Indexed
            addr = 134060672LL + (4 * loop9);
            WRITE_4b(addr);

        }
        goto block44;

block44:
        static int64_t loop12_break = 2719853ULL;
        for(uint64_t loop12 = 0; loop12 < 256ULL; loop12++){
            if(loop12_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_409100101);
            addr_409100101 += 4LL;
            if(addr_409100101 >= 134061760LL) addr_409100101 = 134060676LL;

            //Dominant stride
            READ_4b(addr_409500101);
            addr_409500101 += 4LL;
            if(addr_409500101 >= 134061824LL) addr_409500101 = 134060740LL;

            //Dominant stride
            READ_4b(addr_409900101);
            addr_409900101 += 4LL;
            if(addr_409900101 >= 134061756LL) addr_409900101 = 134060672LL;

            //Small tile
            READ_4b(addr_410200101);
            switch(addr_410200101) {
                case 134060668LL : strd_410200101 = (134059648LL - 134060668LL); break;
                case 134060236LL : strd_410200101 = (134060240LL - 134060236LL); break;
                case 134059648LL : strd_410200101 = (134059652LL - 134059648LL); break;
            }
            addr_410200101 += strd_410200101;

            //Dominant stride
            WRITE_4b(addr_412000101);
            addr_412000101 += 4LL;
            if(addr_412000101 >= 134061828LL) addr_412000101 = 134060744LL;

        }
        for(uint64_t loop11 = 0; loop11 < 256ULL; loop11++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134061828LL) addr_413500101 = 134060744LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 67129428LL) addr_413600101 = 33944LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_44 = 0;
        out_44++;
        if (out_44 <= 10624LL) goto block48;
        else goto block49;


block49:
        int dummy;
    }

    // Interval: 1000000000 - 1200000000
    {
        int64_t addr_418000101 = 43536528LL;
        int64_t addr_421900101 = 134060744LL;
        int64_t addr_422000101 = 43815064LL;
        int64_t addr_416400101 = 110682264LL;
        int64_t addr_416500101 = 134059648LL, strd_416500101 = 0;
        int64_t addr_419800101 = 134061360LL;
        int64_t addr_420100101 = 134060296LL, strd_420100101 = 0;
        int64_t addr_420400101 = 134061432LL;
        int64_t addr_419000101 = 134061368LL;
        int64_t addr_419400101 = 134061432LL;
block50:
        goto block53;

block53:
        //Dominant stride
        READ_4b(addr_419800101);
        addr_419800101 += 4LL;
        if(addr_419800101 >= 134061756LL) addr_419800101 = 134060672LL;

        //Small tile
        READ_4b(addr_420100101);
        switch(addr_420100101) {
            case 134060668LL : strd_420100101 = (134059648LL - 134060668LL); break;
            case 134059648LL : strd_420100101 = (134059652LL - 134059648LL); break;
            case 134060296LL : strd_420100101 = (134060300LL - 134060296LL); break;
        }
        addr_420100101 += strd_420100101;

        //Dominant stride
        WRITE_4b(addr_420400101);
        addr_420400101 += 4LL;
        if(addr_420400101 >= 134061828LL) addr_420400101 = 134060744LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_53 = 0;
        cov_53++;
        if(cov_53 <= 2861610ULL) {
            static uint64_t out_53 = 0;
            out_53 = (out_53 == 255LL) ? 1 : (out_53 + 1);
            if (out_53 <= 254LL) goto block55;
            else goto block59;
        }
        else goto block55;

block55:
        //Dominant stride
        READ_4b(addr_419000101);
        addr_419000101 += 4LL;
        if(addr_419000101 >= 134061760LL) addr_419000101 = 134060676LL;

        //Dominant stride
        READ_4b(addr_419400101);
        addr_419400101 += 4LL;
        if(addr_419400101 >= 134061824LL) addr_419400101 = 134060740LL;

        goto block53;

block59:
        for(uint64_t loop15 = 0; loop15 < 256ULL; loop15++){
            //Dominant stride
            READ_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 134061828LL) addr_421900101 = 134060744LL;

            //Dominant stride
            WRITE_4b(addr_422000101);
            addr_422000101 += 4LL;
            if(addr_422000101 >= 67132756LL) addr_422000101 = 823448LL;

        }
        static int64_t loop13_break = 2872715ULL;
        for(uint64_t loop13 = 0; loop13 < 256ULL; loop13++){
            if(loop13_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134053204LL) addr_416400101 = 67952792LL;

            //Small tile
            WRITE_4b(addr_416500101);
            switch(addr_416500101) {
                case 134060668LL : strd_416500101 = (134059648LL - 134060668LL); break;
                case 134059648LL : strd_416500101 = (134059652LL - 134059648LL); break;
            }
            addr_416500101 += strd_416500101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_59 = 0;
        out_59++;
        if (out_59 <= 11221LL) goto block61;
        else goto block62;


block61:
        for(uint64_t loop14 = 0; loop14 < 289ULL; loop14++){
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67132756LL) addr_418000101 = 807056LL;

            //Loop Indexed
            addr = 134060672LL + (4 * loop14);
            WRITE_4b(addr);

        }
        goto block55;

block62:
        int dummy;
    }

    // Interval: 1200000000 - 1270866252
    {
        int64_t addr_418000101 = 43539664LL;
        int64_t addr_418100101 = 134060672LL, strd_418100101 = 0;
        int64_t addr_416400101 = 110816548LL;
        int64_t addr_416500101 = 134060204LL, strd_416500101 = 0;
        int64_t addr_419000101 = 134060676LL;
        int64_t addr_419400101 = 134060740LL;
        int64_t addr_419800101 = 134060672LL;
        int64_t addr_420400101 = 134060744LL;
        int64_t addr_421900101 = 134060744LL;
        int64_t addr_422000101 = 43556056LL;
block63:
        goto block67;

block74:
        for(uint64_t loop17 = 0; loop17 < 256ULL; loop17++){
            //Dominant stride
            READ_4b(addr_419000101);
            addr_419000101 += 4LL;
            if(addr_419000101 >= 134061760LL) addr_419000101 = 134060676LL;

            //Dominant stride
            READ_4b(addr_419400101);
            addr_419400101 += 4LL;
            if(addr_419400101 >= 134061824LL) addr_419400101 = 134060740LL;

            //Dominant stride
            READ_4b(addr_419800101);
            addr_419800101 += 4LL;
            if(addr_419800101 >= 134061756LL) addr_419800101 = 134060672LL;

            //Loop Indexed
            addr = 134059648LL + (4 * loop17);
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_420400101);
            addr_420400101 += 4LL;
            if(addr_420400101 >= 134061828LL) addr_420400101 = 134060744LL;

        }
        for(uint64_t loop16 = 0; loop16 < 256ULL; loop16++){
            //Dominant stride
            READ_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 134061828LL) addr_421900101 = 134060744LL;

            //Dominant stride
            WRITE_4b(addr_422000101);
            addr_422000101 += 4LL;
            if(addr_422000101 >= 67134036LL) addr_422000101 = 13671640LL;

        }
        goto block67;

block67:
        static int64_t loop19_break = 1017973ULL;
        for(uint64_t loop19 = 0; loop19 < 256ULL; loop19++){
            if(loop19_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134054484LL) addr_416400101 = 80800984LL;

            //Small tile
            WRITE_4b(addr_416500101);
            switch(addr_416500101) {
                case 134060668LL : strd_416500101 = (134059648LL - 134060668LL); break;
                case 134059648LL : strd_416500101 = (134059652LL - 134059648LL); break;
                case 134060204LL : strd_416500101 = (134060208LL - 134060204LL); break;
            }
            addr_416500101 += strd_416500101;

        }
        static int64_t loop18_break = 1149098ULL;
        for(uint64_t loop18 = 0; loop18 < 289ULL; loop18++){
            if(loop18_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67134036LL) addr_418000101 = 13655248LL;

            //Small tile
            WRITE_4b(addr_418100101);
            switch(addr_418100101) {
                case 134061824LL : strd_418100101 = (134060672LL - 134061824LL); break;
                case 134060672LL : strd_418100101 = (134060676LL - 134060672LL); break;
            }
            addr_418100101 += strd_418100101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_67 = 0;
        out_67++;
        if (out_67 <= 3976LL) goto block74;
        else goto block75;


block75:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
