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
    uint64_t allocSize = 134287360ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 500000000
    {
        int64_t addr_375300101 = 67149848LL;
        int64_t addr_374700101 = 4116LL, strd_374700101 = 0;
        int64_t addr_408100101 = 4112LL;
        int64_t addr_406500101 = 67149848LL;
        int64_t addr_410200101 = 134281856LL, strd_410200101 = 0;
        int64_t addr_409900101 = 134282880LL;
        int64_t addr_409500101 = 134282948LL;
block0:
        goto block11;

block11:
        for(uint64_t loop5 = 0; loop5 < 16785409ULL; loop5++){
            //Loop Indexed
            addr = 4112LL + (4 * loop5);
            WRITE_4b(addr);

        }
        for(uint64_t loop4 = 0; loop4 < 16777216ULL; loop4++){
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
            if(addr_375300101 >= 134275092LL) addr_375300101 = 67149848LL;

        }
        for(uint64_t loop3 = 0; loop3 < 5439ULL; loop3++){
            for(uint64_t loop2 = 0; loop2 < 256ULL; loop2++){
                //Dominant stride
                READ_4b(addr_406500101);
                addr_406500101 += 4LL;
                if(addr_406500101 >= 94403156LL) addr_406500101 = 67149848LL;

                //Loop Indexed
                addr = 134281856LL + (4 * loop2);
                WRITE_4b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 289ULL; loop1++){
                //Dominant stride
                READ_4b(addr_408100101);
                addr_408100101 += 4LL;
                if(addr_408100101 >= 27273812LL) addr_408100101 = 4112LL;

                //Loop Indexed
                addr = 134282880LL + (4 * loop1);
                WRITE_4b(addr);

            }
            static int64_t loop0_break = 1392223ULL;
            for(uint64_t loop0 = 0; loop0 < 256ULL; loop0++){
                if(loop0_break-- <= 0) break;
                //Dominant stride
                READ_4b(addr_409500101);
                addr_409500101 += 4LL;
                if(addr_409500101 >= 134284032LL) addr_409500101 = 134282948LL;

                //Dominant stride
                READ_4b(addr_409900101);
                addr_409900101 += 4LL;
                if(addr_409900101 >= 134283964LL) addr_409900101 = 134282880LL;

                //Small tile
                READ_4b(addr_410200101);
                switch(addr_410200101) {
                    case 134282876LL : strd_410200101 = (134281856LL - 134282876LL); break;
                    case 134281856LL : strd_410200101 = (134281860LL - 134281856LL); break;
                }
                addr_410200101 += strd_410200101;

            }
        }
        goto block12;

block12:
        int dummy;
    }

    // Interval: 500000000 - 1000000000
    {
        int64_t addr_408100101 = 5253584LL;
        int64_t addr_413500101 = 134282952LL;
        int64_t addr_413600101 = 5532120LL;
        int64_t addr_412000101 = 134283348LL;
        int64_t addr_409100101 = 134283284LL;
        int64_t addr_409500101 = 134283348LL;
        int64_t addr_409900101 = 134283280LL;
        int64_t addr_410200101 = 134282236LL, strd_410200101 = 0;
        int64_t addr_406500101 = 72399320LL;
block13:
        goto block14;

block14:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134284036LL) addr_412000101 = 134282952LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_14 = 0;
        cov_14++;
        if(cov_14 <= 7001790ULL) {
            static uint64_t out_14 = 0;
            out_14 = (out_14 == 255LL) ? 1 : (out_14 + 1);
            if (out_14 <= 254LL) goto block18;
            else goto block20;
        }
        else goto block18;

block18:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134283968LL) addr_409100101 = 134282884LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134284032LL) addr_409500101 = 134282948LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134283964LL) addr_409900101 = 134282880LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134282876LL : strd_410200101 = (134281856LL - 134282876LL); break;
            case 134281856LL : strd_410200101 = (134281860LL - 134281856LL); break;
            case 134282236LL : strd_410200101 = (134282240LL - 134282236LL); break;
        }
        addr_410200101 += strd_410200101;

        goto block14;

block20:
        for(uint64_t loop6 = 0; loop6 < 256ULL; loop6++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134284036LL) addr_413500101 = 134282952LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 67129428LL) addr_413600101 = 27096LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_20 = 0;
        out_20++;
        if (out_20 <= 27457LL) goto block24;
        else goto block25;


block24:
        for(uint64_t loop7 = 0; loop7 < 256ULL; loop7++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 134258772LL) addr_406500101 = 67156440LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop7);
            WRITE_4b(addr);

        }
        for(uint64_t loop8 = 0; loop8 < 289ULL; loop8++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 67129428LL) addr_408100101 = 10704LL;

            //Loop Indexed
            addr = 134282880LL + (4 * loop8);
            WRITE_4b(addr);

        }
        goto block18;

block25:
        int dummy;
    }

    // Interval: 1000000000 - 1270866269
    {
        int64_t addr_418000101 = 43536528LL;
        int64_t addr_418100101 = 134282880LL, strd_418100101 = 0;
        int64_t addr_416400101 = 110682264LL;
        int64_t addr_421900101 = 134282952LL;
        int64_t addr_422000101 = 43815064LL;
        int64_t addr_419000101 = 134283572LL;
        int64_t addr_419400101 = 134283636LL;
        int64_t addr_419800101 = 134283568LL;
        int64_t addr_420100101 = 134282504LL, strd_420100101 = 0;
        int64_t addr_420400101 = 134283640LL;
block26:
        goto block37;

block37:
        for(uint64_t loop13 = 0; loop13 < 15198ULL; loop13++){
            addr_421900101 = 134282952LL;
            static int64_t loop12_break = 3890526ULL;
            for(uint64_t loop12 = 0; loop12 < 256ULL; loop12++){
                if(loop12_break-- <= 0) break;
                //Dominant stride
                READ_4b(addr_419000101);
                addr_419000101 += 4LL;
                if(addr_419000101 >= 134283968LL) addr_419000101 = 134282884LL;

                //Dominant stride
                READ_4b(addr_419400101);
                addr_419400101 += 4LL;
                if(addr_419400101 >= 134284032LL) addr_419400101 = 134282948LL;

                //Dominant stride
                READ_4b(addr_419800101);
                addr_419800101 += 4LL;
                if(addr_419800101 >= 134283964LL) addr_419800101 = 134282880LL;

                //Small tile
                READ_4b(addr_420100101);
                switch(addr_420100101) {
                    case 134282504LL : strd_420100101 = (134282508LL - 134282504LL); break;
                    case 134282876LL : strd_420100101 = (134281856LL - 134282876LL); break;
                    case 134281856LL : strd_420100101 = (134281860LL - 134281856LL); break;
                }
                addr_420100101 += strd_420100101;

                //Dominant stride
                WRITE_4b(addr_420400101);
                addr_420400101 += 4LL;
                if(addr_420400101 >= 134284036LL) addr_420400101 = 134282952LL;

            }
            for(uint64_t loop11 = 0; loop11 < 256ULL; loop11++){
                //Dominant stride
                READ_4b(addr_421900101);
                addr_421900101 += 4LL;
                if(addr_421900101 >= 134284036LL) addr_421900101 = 134282952LL;

                //Dominant stride
                WRITE_4b(addr_422000101);
                addr_422000101 += 4LL;
                if(addr_422000101 >= 67134036LL) addr_422000101 = 823448LL;

            }
            for(uint64_t loop10 = 0; loop10 < 256ULL; loop10++){
                //Dominant stride
                READ_4b(addr_416400101);
                addr_416400101 += 4LL;
                if(addr_416400101 >= 134263380LL) addr_416400101 = 67952792LL;

                //Loop Indexed
                addr = 134281856LL + (4 * loop10);
                WRITE_4b(addr);

            }
            static int64_t loop9_break = 4391968ULL;
            for(uint64_t loop9 = 0; loop9 < 289ULL; loop9++){
                if(loop9_break-- <= 0) break;
                //Dominant stride
                READ_4b(addr_418000101);
                addr_418000101 += 4LL;
                if(addr_418000101 >= 67134036LL) addr_418000101 = 807056LL;

                //Small tile
                WRITE_4b(addr_418100101);
                switch(addr_418100101) {
                    case 134284032LL : strd_418100101 = (134282880LL - 134284032LL); break;
                    case 134282880LL : strd_418100101 = (134282884LL - 134282880LL); break;
                }
                addr_418100101 += strd_418100101;

            }
        }
        goto block38;

block38:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
