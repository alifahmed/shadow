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
    uint64_t allocSize = 29413376ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 100000000
    {
        int64_t addr_399600101 = 29405648LL, strd_399600101 = 0;
        int64_t addr_399500101 = 29405648LL, strd_399500101 = 0;
        int64_t addr_399400101 = 29405636LL, strd_399400101 = 0;
        int64_t addr_412500101 = 704LL, strd_412500101 = 0;
        int64_t addr_412700101 = 21008400LL;
        int64_t addr_413600101 = 8912LL, strd_413600101 = 0;
        int64_t addr_413800101 = 21008404LL;
        int64_t addr_410500101 = 21008400LL, strd_410500101 = 0;
block0:
        goto block30;

block30:
        for(uint64_t loop2 = 0; loop2 < 1048576ULL; loop2++){
            //Small tile
            READ_4b(addr_399400101);
            switch(addr_399400101) {
                case 29405636LL : strd_399400101 = (29405640LL - 29405636LL); break;
                case 29405756LL : strd_399400101 = (29405636LL - 29405756LL); break;
            }
            addr_399400101 += strd_399400101;

            //Small tile
            READ_4b(addr_399500101);
            switch(addr_399500101) {
                case 29405648LL : strd_399500101 = (29405652LL - 29405648LL); break;
                case 29405636LL : strd_399500101 = (29405640LL - 29405636LL); break;
                case 29405756LL : strd_399500101 = (29405636LL - 29405756LL); break;
            }
            addr_399500101 += strd_399500101;

            //Small tile
            WRITE_4b(addr_399600101);
            switch(addr_399600101) {
                case 29405648LL : strd_399600101 = (29405652LL - 29405648LL); break;
                case 29405636LL : strd_399600101 = (29405640LL - 29405636LL); break;
                case 29405756LL : strd_399600101 = (29405636LL - 29405756LL); break;
            }
            addr_399600101 += strd_399600101;

            //Loop Indexed
            addr = 25206800LL + (4 * loop2);
            WRITE_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 1048576ULL; loop1++){
            //Loop Indexed
            addr = 25206800LL + (4 * loop1);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(29410528LL - 29410272LL) + 29410272LL) & ~7ULL;
            READ_8b(addr);

            //Loop Indexed
            addr = 21008400LL + (4 * loop1);
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 358587ULL; loop0++){
            //Loop Indexed
            addr = 21008400LL + (4 * loop0);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_410500101);
            switch(addr_410500101) {
                case 21012492LL : strd_410500101 = (21008400LL - 21012492LL); break;
                case 21008400LL : strd_410500101 = (21008404LL - 21008400LL); break;
            }
            addr_410500101 += strd_410500101;

            //Loop Indexed
            addr = 12611600LL + (4 * loop0);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 21012496LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop0);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_412500101);
            switch(addr_412500101) {
                case 704LL : strd_412500101 = (708LL - 704LL); break;
                case 4796LL : strd_412500101 = (704LL - 4796LL); break;
            }
            addr_412500101 += strd_412500101;

            //Dominant stride
            READ_4b(addr_412700101);
            addr_412700101 += 4LL;
            if(addr_412700101 >= 22442744LL) addr_412700101 = 21008400LL;

            //Loop Indexed
            addr = 4214800LL + (4 * loop0);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_413600101);
            switch(addr_413600101) {
                case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
                case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
            }
            addr_413600101 += strd_413600101;

            //Dominant stride
            READ_4b(addr_413800101);
            addr_413800101 += 4LL;
            if(addr_413800101 >= 22442752LL) addr_413800101 = 21008404LL;

            //Loop Indexed
            addr = 16400LL + (4 * loop0);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 12611600LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 12611600LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 12611600LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop0);
            READ_4b(addr);

        }
        goto block31;

block31:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_421500101 = 18244344LL;
        int64_t addr_420900101 = 18244348LL;
        int64_t addr_420600101 = 18244348LL;
        int64_t addr_418000101 = 1450748LL;
        int64_t addr_417700101 = 5649148LL;
        int64_t addr_417400101 = 9847548LL;
        int64_t addr_417100101 = 14045948LL;
        int64_t addr_416600101 = 1450748LL;
        int64_t addr_416300101 = 1450748LL;
        int64_t addr_416000101 = 5649148LL;
        int64_t addr_415700101 = 5649148LL;
        int64_t addr_415400101 = 9847548LL;
        int64_t addr_415100101 = 9847548LL;
        int64_t addr_409700101 = 22442748LL;
        int64_t addr_410500101 = 22438652LL;
        int64_t addr_410900101 = 14045948LL;
        int64_t addr_411600101 = 22446844LL, strd_411600101 = 0;
        int64_t addr_412000101 = 9847548LL;
        int64_t addr_412500101 = 1452LL, strd_412500101 = 0;
        int64_t addr_412700101 = 22442744LL;
        int64_t addr_413100101 = 5649148LL;
        int64_t addr_413600101 = 9660LL, strd_413600101 = 0;
        int64_t addr_413800101 = 22442752LL;
        int64_t addr_414200101 = 1450748LL;
        int64_t addr_414500101 = 14045948LL;
        int64_t addr_414800101 = 14045948LL;
block32:
        goto block33;

block33:
        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (18244348LL - 18244344LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_33 = 0;
        out_33++;
        if (out_33 <= 689989LL) goto block58;
        else goto block63;


block58:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (22442752LL - 22442748LL);

        //Small tile
        READ_4b(addr_410500101);
        addr_410500101 += (22438656LL - 22438652LL);

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (14045952LL - 14045948LL);

        //Small tile
        READ_4b(addr_411600101);
        switch(addr_411600101) {
            case 25202700LL : strd_411600101 = (25198608LL - 25202700LL); break;
            case 22446844LL : strd_411600101 = (22446848LL - 22446844LL); break;
            case 25198608LL : strd_411600101 = (25198612LL - 25198608LL); break;
        }
        addr_411600101 += strd_411600101;

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (9847552LL - 9847548LL);

        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
            case 1452LL : strd_412500101 = (1456LL - 1452LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 25202700LL) addr_412700101 = 22442744LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (5649152LL - 5649148LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 9660LL : strd_413600101 = (9664LL - 9660LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 25202704LL) addr_413800101 = 22442752LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (1450752LL - 1450748LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (14045952LL - 14045948LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (14045952LL - 14045948LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (9847552LL - 9847548LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (9847552LL - 9847548LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (5649152LL - 5649148LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (5649152LL - 5649148LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (1450752LL - 1450748LL);

        //Small tile
        READ_4b(addr_416600101);
        addr_416600101 += (1450752LL - 1450748LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (14045952LL - 14045948LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (9847552LL - 9847548LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (5649152LL - 5649148LL);

        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (1450752LL - 1450748LL);

        //Small tile
        WRITE_4b(addr_420600101);
        addr_420600101 += (18244352LL - 18244348LL);

        //Small tile
        READ_4b(addr_420900101);
        addr_420900101 += (18244352LL - 18244348LL);

        goto block33;

block63:
        for(uint64_t loop3 = 0; loop3 < 223075ULL; loop3++){
            //Loop Indexed
            addr = 8413200LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 21008400LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 21008400LL + (4 * loop3);
            WRITE_4b(addr);

        }
        goto block64;

block64:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_424300101 = 17706396LL, strd_424300101 = 0;
        int64_t addr_425300101 = 12380LL, strd_425300101 = 0;
        int64_t addr_425500101 = 17702304LL;
        int64_t addr_417700101 = 4214800LL;
        int64_t addr_417400101 = 8413200LL;
        int64_t addr_417100101 = 12611600LL;
        int64_t addr_416600101 = 16400LL;
        int64_t addr_416300101 = 16400LL;
        int64_t addr_416000101 = 4214800LL;
        int64_t addr_409700101 = 21008400LL;
        int64_t addr_410500101 = 21008400LL, strd_410500101 = 0;
        int64_t addr_410900101 = 12611600LL;
        int64_t addr_411600101 = 21012496LL;
        int64_t addr_412000101 = 8413200LL;
        int64_t addr_412500101 = 704LL, strd_412500101 = 0;
        int64_t addr_412700101 = 21008400LL;
        int64_t addr_413100101 = 4214800LL;
        int64_t addr_413600101 = 8912LL, strd_413600101 = 0;
        int64_t addr_413800101 = 21008404LL;
        int64_t addr_414200101 = 16400LL;
        int64_t addr_414500101 = 12611600LL;
        int64_t addr_414800101 = 12611600LL;
        int64_t addr_415100101 = 8413200LL;
        int64_t addr_415400101 = 8413200LL;
        int64_t addr_415700101 = 4214800LL;
        int64_t addr_421500101 = 16810000LL;
block65:
        goto block76;

block76:
        for(uint64_t loop4 = 0; loop4 < 825501ULL; loop4++){
            //Loop Indexed
            addr = 17702300LL + (4 * loop4);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_424300101);
            switch(addr_424300101) {
                case 21004300LL : strd_424300101 = (21000208LL - 21004300LL); break;
                case 21000208LL : strd_424300101 = (21000212LL - 21000208LL); break;
                case 17706396LL : strd_424300101 = (17706400LL - 17706396LL); break;
            }
            addr_424300101 += strd_424300101;

            //Loop Indexed
            addr = 17702300LL + (4 * loop4);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_425300101);
            switch(addr_425300101) {
                case 12380LL : strd_425300101 = (12384LL - 12380LL); break;
                case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
                case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            }
            addr_425300101 += strd_425300101;

            //Dominant stride
            READ_4b(addr_425500101);
            addr_425500101 += 4LL;
            if(addr_425500101 >= 21004304LL) addr_425500101 = 17702304LL;

            //Loop Indexed
            addr = 13503900LL + (4 * loop4);
            READ_4b(addr);

            //Loop Indexed
            addr = 9305500LL + (4 * loop4);
            READ_4b(addr);

            //Loop Indexed
            addr = 5107100LL + (4 * loop4);
            READ_4b(addr);

            //Loop Indexed
            addr = 908700LL + (4 * loop4);
            READ_4b(addr);

            //Loop Indexed
            addr = 21900700LL + (4 * loop4);
            READ_4b(addr);

            //Loop Indexed
            addr = 21900700LL + (4 * loop4);
            WRITE_4b(addr);

        }
        goto block98;

block98:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (21008404LL - 21008400LL);

        //Small tile
        READ_4b(addr_410500101);
        switch(addr_410500101) {
            case 21012492LL : strd_410500101 = (21008400LL - 21012492LL); break;
            case 21008400LL : strd_410500101 = (21008404LL - 21008400LL); break;
        }
        addr_410500101 += strd_410500101;

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_411600101);
        addr_411600101 += (21012500LL - 21012496LL);

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 22676356LL) addr_412700101 = 21008400LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 22676364LL) addr_413800101 = 21008404LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_416600101);
        addr_416600101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (4214804LL - 4214800LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_98 = 0;
        out_98++;
        if (out_98 <= 416989LL) goto block99;
        else goto block100;


block99:
        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (16810004LL - 16810000LL);

        goto block98;

block100:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_421500101 = 18477956LL;
        int64_t addr_420900101 = 18477956LL;
        int64_t addr_420600101 = 18477956LL;
        int64_t addr_418000101 = 1684356LL;
        int64_t addr_417700101 = 5882760LL;
        int64_t addr_417400101 = 10081160LL;
        int64_t addr_417100101 = 14279560LL;
        int64_t addr_416600101 = 1684360LL;
        int64_t addr_416300101 = 1684360LL;
        int64_t addr_416000101 = 5882760LL;
        int64_t addr_415700101 = 5882760LL;
        int64_t addr_415400101 = 10081160LL;
        int64_t addr_415100101 = 10081160LL;
        int64_t addr_409700101 = 22676360LL;
        int64_t addr_410500101 = 22672264LL;
        int64_t addr_410900101 = 14279560LL;
        int64_t addr_411600101 = 22680456LL, strd_411600101 = 0;
        int64_t addr_412000101 = 10081160LL;
        int64_t addr_412500101 = 1592LL, strd_412500101 = 0;
        int64_t addr_412700101 = 22676356LL;
        int64_t addr_413100101 = 5882760LL;
        int64_t addr_413600101 = 9800LL, strd_413600101 = 0;
        int64_t addr_413800101 = 22676364LL;
        int64_t addr_414200101 = 1684360LL;
        int64_t addr_414500101 = 14279560LL;
        int64_t addr_414800101 = 14279560LL;
        int64_t addr_425500101 = 16810004LL;
        int64_t addr_425300101 = 8912LL, strd_425300101 = 0;
block101:
        goto block105;

block105:
        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (1684360LL - 1684356LL);

        //Small tile
        WRITE_4b(addr_420600101);
        addr_420600101 += (18477960LL - 18477956LL);

        //Small tile
        READ_4b(addr_420900101);
        addr_420900101 += (18477960LL - 18477956LL);

        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (18477960LL - 18477956LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_105 = 0;
        out_105++;
        if (out_105 <= 631586LL) goto block127;
        else goto block134;


block127:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (22676364LL - 22676360LL);

        //Small tile
        READ_4b(addr_410500101);
        addr_410500101 += (22672268LL - 22672264LL);

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (14279564LL - 14279560LL);

        //Small tile
        READ_4b(addr_411600101);
        switch(addr_411600101) {
            case 25202700LL : strd_411600101 = (25198608LL - 25202700LL); break;
            case 22680456LL : strd_411600101 = (22680460LL - 22680456LL); break;
            case 25198608LL : strd_411600101 = (25198612LL - 25198608LL); break;
        }
        addr_411600101 += strd_411600101;

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (10081164LL - 10081160LL);

        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
            case 1592LL : strd_412500101 = (1596LL - 1592LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 25202700LL) addr_412700101 = 22676356LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (5882764LL - 5882760LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 9800LL : strd_413600101 = (9804LL - 9800LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 25202704LL) addr_413800101 = 22676364LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (1684364LL - 1684360LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (14279564LL - 14279560LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (14279564LL - 14279560LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (10081164LL - 10081160LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (10081164LL - 10081160LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (5882764LL - 5882760LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (5882764LL - 5882760LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (1684364LL - 1684360LL);

        //Small tile
        READ_4b(addr_416600101);
        addr_416600101 += (1684364LL - 1684360LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (14279564LL - 14279560LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (10081164LL - 10081160LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (5882764LL - 5882760LL);

        goto block105;

block134:
        for(uint64_t loop5 = 0; loop5 < 349277ULL; loop5++){
            //Loop Indexed
            addr = 16810000LL + (4 * loop5);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_425300101);
            switch(addr_425300101) {
                case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
                case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            }
            addr_425300101 += strd_425300101;

            //Dominant stride
            READ_4b(addr_425500101);
            addr_425500101 += 4LL;
            if(addr_425500101 >= 18207112LL) addr_425500101 = 16810004LL;

            //Loop Indexed
            addr = 12611600LL + (4 * loop5);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop5);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop5);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop5);
            READ_4b(addr);

        }
        goto block135;

block135:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_428200101 = 22405504LL;
        int64_t addr_427600101 = 22405504LL;
        int64_t addr_423500101 = 18207108LL;
        int64_t addr_424300101 = 18211204LL, strd_424300101 = 0;
        int64_t addr_424700101 = 18207108LL;
        int64_t addr_425300101 = 9284LL, strd_425300101 = 0;
        int64_t addr_425500101 = 18207112LL;
        int64_t addr_425900101 = 14008708LL;
        int64_t addr_426300101 = 9810308LL;
        int64_t addr_426700101 = 5611908LL;
        int64_t addr_427100101 = 1413508LL;
        int64_t addr_412000101 = 8413200LL;
        int64_t addr_411600101 = 21012496LL;
        int64_t addr_410900101 = 12611600LL;
        int64_t addr_410500101 = 21008400LL, strd_410500101 = 0;
        int64_t addr_409700101 = 21008400LL;
        int64_t addr_421500101 = 16810000LL;
        int64_t addr_420900101 = 16810000LL;
        int64_t addr_420600101 = 16810000LL;
        int64_t addr_418000101 = 16400LL;
        int64_t addr_417700101 = 4214800LL;
        int64_t addr_412500101 = 704LL, strd_412500101 = 0;
        int64_t addr_412700101 = 21008400LL;
        int64_t addr_413100101 = 4214800LL;
        int64_t addr_413600101 = 8912LL, strd_413600101 = 0;
        int64_t addr_413800101 = 21008404LL;
        int64_t addr_414200101 = 16400LL;
        int64_t addr_414500101 = 12611600LL;
        int64_t addr_414800101 = 12611600LL;
        int64_t addr_415100101 = 8413200LL;
        int64_t addr_415400101 = 8413200LL;
        int64_t addr_415700101 = 4214800LL;
        int64_t addr_416000101 = 4214800LL;
        int64_t addr_416300101 = 16400LL;
block136:
        goto block138;

block152:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (21008404LL - 21008400LL);

        //Small tile
        READ_4b(addr_410500101);
        switch(addr_410500101) {
            case 21012492LL : strd_410500101 = (21008400LL - 21012492LL); break;
            case 21008400LL : strd_410500101 = (21008404LL - 21008400LL); break;
        }
        addr_410500101 += strd_410500101;

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_411600101);
        addr_411600101 += (21012500LL - 21012496LL);

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (8413204LL - 8413200LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_152 = 0;
        out_152++;
        if (out_152 <= 472516LL) goto block170;
        else goto block171;


block138:
        //Small tile
        READ_4b(addr_427600101);
        addr_427600101 += (22405508LL - 22405504LL);

        //Small tile
        WRITE_4b(addr_428200101);
        addr_428200101 += (22405508LL - 22405504LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_138 = 0;
        out_138++;
        if (out_138 <= 699299LL) goto block147;
        else goto block152;


block147:
        //Small tile
        READ_4b(addr_423500101);
        addr_423500101 += (18207112LL - 18207108LL);

        //Small tile
        READ_4b(addr_424300101);
        switch(addr_424300101) {
            case 21004300LL : strd_424300101 = (21000208LL - 21004300LL); break;
            case 18211204LL : strd_424300101 = (18211208LL - 18211204LL); break;
            case 21000208LL : strd_424300101 = (21000212LL - 21000208LL); break;
        }
        addr_424300101 += strd_424300101;

        //Small tile
        READ_4b(addr_424700101);
        addr_424700101 += (18207112LL - 18207108LL);

        //Small tile
        READ_4b(addr_425300101);
        switch(addr_425300101) {
            case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
            case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            case 9284LL : strd_425300101 = (9288LL - 9284LL); break;
        }
        addr_425300101 += strd_425300101;

        //Dominant stride
        READ_4b(addr_425500101);
        addr_425500101 += 4LL;
        if(addr_425500101 >= 21004304LL) addr_425500101 = 18207112LL;

        //Small tile
        READ_4b(addr_425900101);
        addr_425900101 += (14008712LL - 14008708LL);

        //Small tile
        READ_4b(addr_426300101);
        addr_426300101 += (9810312LL - 9810308LL);

        //Small tile
        READ_4b(addr_426700101);
        addr_426700101 += (5611912LL - 5611908LL);

        //Small tile
        READ_4b(addr_427100101);
        addr_427100101 += (1413512LL - 1413508LL);

        goto block138;

block170:
        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 22898460LL) addr_412700101 = 21008400LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 22898468LL) addr_413800101 = 21008404LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (16404LL - 16400LL);

        //Small tile
        WRITE_4b(addr_420600101);
        addr_420600101 += (16810004LL - 16810000LL);

        //Small tile
        READ_4b(addr_420900101);
        addr_420900101 += (16810004LL - 16810000LL);

        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (16810004LL - 16810000LL);

        goto block152;

block171:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_417400101 = 10303264LL;
        int64_t addr_417100101 = 14501664LL;
        int64_t addr_416600101 = 1906464LL;
        int64_t addr_416300101 = 1906464LL;
        int64_t addr_416000101 = 6104864LL;
        int64_t addr_415700101 = 6104864LL;
        int64_t addr_415400101 = 10303264LL;
        int64_t addr_415100101 = 10303264LL;
        int64_t addr_414800101 = 14501664LL;
        int64_t addr_414500101 = 14501664LL;
        int64_t addr_414200101 = 1906464LL;
        int64_t addr_413800101 = 22898468LL;
        int64_t addr_413600101 = 10720LL, strd_413600101 = 0;
        int64_t addr_413100101 = 6104864LL;
        int64_t addr_412700101 = 22898460LL;
        int64_t addr_412500101 = 2512LL, strd_412500101 = 0;
        int64_t addr_417700101 = 6104864LL;
        int64_t addr_418000101 = 1906464LL;
        int64_t addr_420600101 = 18700064LL;
        int64_t addr_420900101 = 18700064LL;
        int64_t addr_421500101 = 18700064LL;
        int64_t addr_412000101 = 10303268LL;
        int64_t addr_411600101 = 22902564LL, strd_411600101 = 0;
        int64_t addr_410900101 = 14501668LL;
        int64_t addr_410500101 = 22894372LL;
        int64_t addr_409700101 = 22898468LL;
        int64_t addr_425500101 = 16810004LL;
        int64_t addr_425300101 = 8912LL, strd_425300101 = 0;
block172:
        goto block193;

block193:
        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 2512LL : strd_412500101 = (2516LL - 2512LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 25202700LL) addr_412700101 = 22898460LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (6104868LL - 6104864LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
            case 10720LL : strd_413600101 = (10724LL - 10720LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 25202704LL) addr_413800101 = 22898468LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (1906468LL - 1906464LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (14501668LL - 14501664LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (14501668LL - 14501664LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (10303268LL - 10303264LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (10303268LL - 10303264LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (6104868LL - 6104864LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (6104868LL - 6104864LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (1906468LL - 1906464LL);

        //Small tile
        READ_4b(addr_416600101);
        addr_416600101 += (1906468LL - 1906464LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (14501668LL - 14501664LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (10303268LL - 10303264LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (6104868LL - 6104864LL);

        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (1906468LL - 1906464LL);

        //Small tile
        WRITE_4b(addr_420600101);
        addr_420600101 += (18700068LL - 18700064LL);

        //Small tile
        READ_4b(addr_420900101);
        addr_420900101 += (18700068LL - 18700064LL);

        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (18700068LL - 18700064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_193 = 0;
        out_193++;
        if (out_193 <= 576059LL) goto block198;
        else goto block206;


block198:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (22898472LL - 22898468LL);

        //Small tile
        READ_4b(addr_410500101);
        addr_410500101 += (22894376LL - 22894372LL);

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (14501672LL - 14501668LL);

        //Small tile
        READ_4b(addr_411600101);
        switch(addr_411600101) {
            case 25202700LL : strd_411600101 = (25198608LL - 25202700LL); break;
            case 22902564LL : strd_411600101 = (22902568LL - 22902564LL); break;
            case 25198608LL : strd_411600101 = (25198612LL - 25198608LL); break;
        }
        addr_411600101 += strd_411600101;

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (10303272LL - 10303268LL);

        goto block193;

block206:
        for(uint64_t loop6 = 0; loop6 < 469458ULL; loop6++){
            //Loop Indexed
            addr = 16814096LL + (4 * loop6);
            READ_4b(addr);

            //Loop Indexed
            addr = 16810000LL + (4 * loop6);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_425300101);
            switch(addr_425300101) {
                case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
                case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            }
            addr_425300101 += strd_425300101;

            //Dominant stride
            READ_4b(addr_425500101);
            addr_425500101 += 4LL;
            if(addr_425500101 >= 18687836LL) addr_425500101 = 16810004LL;

            //Loop Indexed
            addr = 12611600LL + (4 * loop6);
            READ_4b(addr);

            //Loop Indexed
            addr = 8413200LL + (4 * loop6);
            READ_4b(addr);

            //Loop Indexed
            addr = 4214800LL + (4 * loop6);
            READ_4b(addr);

            //Loop Indexed
            addr = 16400LL + (4 * loop6);
            READ_4b(addr);

        }
        goto block207;

block207:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_428200101 = 22886228LL;
        int64_t addr_427600101 = 22886228LL;
        int64_t addr_423500101 = 18687832LL;
        int64_t addr_424300101 = 18691928LL, strd_424300101 = 0;
        int64_t addr_424700101 = 18687832LL;
        int64_t addr_425300101 = 10776LL, strd_425300101 = 0;
        int64_t addr_425500101 = 18687836LL;
        int64_t addr_425900101 = 14489432LL;
        int64_t addr_426300101 = 10291032LL;
        int64_t addr_426700101 = 6092632LL;
        int64_t addr_427100101 = 1894232LL;
        int64_t addr_418000101 = 16400LL;
        int64_t addr_417700101 = 4214800LL;
        int64_t addr_417400101 = 8413200LL;
        int64_t addr_417100101 = 12611600LL;
        int64_t addr_416600101 = 16400LL;
        int64_t addr_416300101 = 16400LL;
        int64_t addr_409700101 = 21008400LL;
        int64_t addr_410500101 = 21008400LL, strd_410500101 = 0;
        int64_t addr_410900101 = 12611600LL;
        int64_t addr_411600101 = 21012496LL;
        int64_t addr_412000101 = 8413200LL;
        int64_t addr_412500101 = 704LL, strd_412500101 = 0;
        int64_t addr_412700101 = 21008400LL;
        int64_t addr_413100101 = 4214800LL;
        int64_t addr_413600101 = 8912LL, strd_413600101 = 0;
        int64_t addr_413800101 = 21008404LL;
        int64_t addr_414200101 = 16400LL;
        int64_t addr_414500101 = 12611600LL;
        int64_t addr_414800101 = 12611600LL;
        int64_t addr_415100101 = 8413200LL;
        int64_t addr_415400101 = 8413200LL;
        int64_t addr_415700101 = 4214800LL;
        int64_t addr_416000101 = 4214800LL;
        int64_t addr_421500101 = 16810000LL;
block208:
        goto block210;

block219:
        //Small tile
        READ_4b(addr_423500101);
        addr_423500101 += (18687836LL - 18687832LL);

        //Small tile
        READ_4b(addr_424300101);
        switch(addr_424300101) {
            case 21004300LL : strd_424300101 = (21000208LL - 21004300LL); break;
            case 18691928LL : strd_424300101 = (18691932LL - 18691928LL); break;
            case 21000208LL : strd_424300101 = (21000212LL - 21000208LL); break;
        }
        addr_424300101 += strd_424300101;

        //Small tile
        READ_4b(addr_424700101);
        addr_424700101 += (18687836LL - 18687832LL);

        //Small tile
        READ_4b(addr_425300101);
        switch(addr_425300101) {
            case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
            case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            case 10776LL : strd_425300101 = (10780LL - 10776LL); break;
        }
        addr_425300101 += strd_425300101;

        //Dominant stride
        READ_4b(addr_425500101);
        addr_425500101 += 4LL;
        if(addr_425500101 >= 21004304LL) addr_425500101 = 18687836LL;

        //Small tile
        READ_4b(addr_425900101);
        addr_425900101 += (14489436LL - 14489432LL);

        //Small tile
        READ_4b(addr_426300101);
        addr_426300101 += (10291036LL - 10291032LL);

        //Small tile
        READ_4b(addr_426700101);
        addr_426700101 += (6092636LL - 6092632LL);

        //Small tile
        READ_4b(addr_427100101);
        addr_427100101 += (1894236LL - 1894232LL);

        goto block210;

block210:
        //Small tile
        READ_4b(addr_427600101);
        addr_427600101 += (22886232LL - 22886228LL);

        //Small tile
        WRITE_4b(addr_428200101);
        addr_428200101 += (22886232LL - 22886228LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_210 = 0;
        out_210++;
        if (out_210 <= 579118LL) goto block219;
        else goto block242;


block242:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (21008404LL - 21008400LL);

        //Small tile
        READ_4b(addr_410500101);
        switch(addr_410500101) {
            case 21012492LL : strd_410500101 = (21008400LL - 21012492LL); break;
            case 21008400LL : strd_410500101 = (21008404LL - 21008400LL); break;
        }
        addr_410500101 += strd_410500101;

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_411600101);
        addr_411600101 += (21012500LL - 21012496LL);

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 23108612LL) addr_412700101 = 21008400LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 23108620LL) addr_413800101 = 21008404LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_416300101);
        addr_416300101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_416600101);
        addr_416600101 += (16404LL - 16400LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (16404LL - 16400LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_242 = 0;
        out_242++;
        if (out_242 <= 525053LL) goto block243;
        else goto block244;


block243:
        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (16810004LL - 16810000LL);

        goto block242;

block244:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_423500101 = 16810000LL;
        int64_t addr_424300101 = 16814096LL;
        int64_t addr_427100101 = 16400LL;
        int64_t addr_426700101 = 4214800LL;
        int64_t addr_426300101 = 8413200LL;
        int64_t addr_425900101 = 12611600LL;
        int64_t addr_425500101 = 16810004LL;
        int64_t addr_425300101 = 8912LL, strd_425300101 = 0;
        int64_t addr_424700101 = 16810000LL;
        int64_t addr_427600101 = 21008400LL;
        int64_t addr_428200101 = 21008400LL;
        int64_t addr_421500101 = 18910212LL;
        int64_t addr_420900101 = 18910212LL;
        int64_t addr_420600101 = 18910212LL;
        int64_t addr_418000101 = 2116616LL;
        int64_t addr_417700101 = 6315016LL;
        int64_t addr_417400101 = 10513416LL;
        int64_t addr_417100101 = 14711816LL;
        int64_t addr_409700101 = 23108616LL;
        int64_t addr_410500101 = 23104520LL;
        int64_t addr_410900101 = 14711816LL;
        int64_t addr_411600101 = 23112712LL, strd_411600101 = 0;
        int64_t addr_412000101 = 10513416LL;
        int64_t addr_412500101 = 3768LL, strd_412500101 = 0;
        int64_t addr_412700101 = 23108612LL;
        int64_t addr_413100101 = 6315016LL;
        int64_t addr_413600101 = 11976LL, strd_413600101 = 0;
        int64_t addr_413800101 = 23108620LL;
        int64_t addr_414200101 = 2116616LL;
        int64_t addr_414500101 = 14711816LL;
        int64_t addr_414800101 = 14711816LL;
        int64_t addr_415100101 = 10513416LL;
        int64_t addr_415400101 = 10513416LL;
        int64_t addr_415700101 = 6315016LL;
        int64_t addr_416000101 = 6315016LL;
block245:
        goto block248;

block269:
        //Small tile
        READ_4b(addr_409700101);
        addr_409700101 += (23108620LL - 23108616LL);

        //Small tile
        READ_4b(addr_410500101);
        addr_410500101 += (23104524LL - 23104520LL);

        //Small tile
        WRITE_4b(addr_410900101);
        addr_410900101 += (14711820LL - 14711816LL);

        //Small tile
        READ_4b(addr_411600101);
        switch(addr_411600101) {
            case 25202700LL : strd_411600101 = (25198608LL - 25202700LL); break;
            case 23112712LL : strd_411600101 = (23112716LL - 23112712LL); break;
            case 25198608LL : strd_411600101 = (25198612LL - 25198608LL); break;
        }
        addr_411600101 += strd_411600101;

        //Small tile
        WRITE_4b(addr_412000101);
        addr_412000101 += (10513420LL - 10513416LL);

        //Small tile
        READ_4b(addr_412500101);
        switch(addr_412500101) {
            case 704LL : strd_412500101 = (708LL - 704LL); break;
            case 4796LL : strd_412500101 = (704LL - 4796LL); break;
            case 3768LL : strd_412500101 = (3772LL - 3768LL); break;
        }
        addr_412500101 += strd_412500101;

        //Dominant stride
        READ_4b(addr_412700101);
        addr_412700101 += 4LL;
        if(addr_412700101 >= 25202700LL) addr_412700101 = 23108612LL;

        //Small tile
        WRITE_4b(addr_413100101);
        addr_413100101 += (6315020LL - 6315016LL);

        //Small tile
        READ_4b(addr_413600101);
        switch(addr_413600101) {
            case 13004LL : strd_413600101 = (8912LL - 13004LL); break;
            case 11976LL : strd_413600101 = (11980LL - 11976LL); break;
            case 8912LL : strd_413600101 = (8916LL - 8912LL); break;
        }
        addr_413600101 += strd_413600101;

        //Dominant stride
        READ_4b(addr_413800101);
        addr_413800101 += 4LL;
        if(addr_413800101 >= 25202704LL) addr_413800101 = 23108620LL;

        //Small tile
        WRITE_4b(addr_414200101);
        addr_414200101 += (2116620LL - 2116616LL);

        //Small tile
        READ_4b(addr_414500101);
        addr_414500101 += (14711820LL - 14711816LL);

        //Small tile
        READ_4b(addr_414800101);
        addr_414800101 += (14711820LL - 14711816LL);

        //Small tile
        READ_4b(addr_415100101);
        addr_415100101 += (10513420LL - 10513416LL);

        //Small tile
        READ_4b(addr_415400101);
        addr_415400101 += (10513420LL - 10513416LL);

        //Small tile
        READ_4b(addr_415700101);
        addr_415700101 += (6315020LL - 6315016LL);

        //Small tile
        READ_4b(addr_416000101);
        addr_416000101 += (6315020LL - 6315016LL);

        //Small tile
        READ_4b(addr_417100101);
        addr_417100101 += (14711820LL - 14711816LL);

        //Small tile
        READ_4b(addr_417400101);
        addr_417400101 += (10513420LL - 10513416LL);

        //Small tile
        READ_4b(addr_417700101);
        addr_417700101 += (6315020LL - 6315016LL);

        //Small tile
        READ_4b(addr_418000101);
        addr_418000101 += (2116620LL - 2116616LL);

        goto block248;

block278:
        //Small tile
        READ_4b(addr_423500101);
        addr_423500101 += (16810004LL - 16810000LL);

        //Small tile
        READ_4b(addr_424300101);
        addr_424300101 += (16814100LL - 16814096LL);

        //Small tile
        READ_4b(addr_424700101);
        addr_424700101 += (16810004LL - 16810000LL);

        //Small tile
        READ_4b(addr_425300101);
        switch(addr_425300101) {
            case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
            case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
        }
        addr_425300101 += strd_425300101;

        //Dominant stride
        READ_4b(addr_425500101);
        addr_425500101 += 4LL;
        if(addr_425500101 >= 19144584LL) addr_425500101 = 16810004LL;

        //Small tile
        READ_4b(addr_425900101);
        addr_425900101 += (12611604LL - 12611600LL);

        //Small tile
        READ_4b(addr_426300101);
        addr_426300101 += (8413204LL - 8413200LL);

        //Small tile
        READ_4b(addr_426700101);
        addr_426700101 += (4214804LL - 4214800LL);

        //Small tile
        READ_4b(addr_427100101);
        addr_427100101 += (16404LL - 16400LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_278 = 0;
        out_278++;
        if (out_278 <= 583644LL) goto block280;
        else goto block281;


block280:
        //Small tile
        READ_4b(addr_427600101);
        addr_427600101 += (21008404LL - 21008400LL);

        //Small tile
        WRITE_4b(addr_428200101);
        addr_428200101 += (21008404LL - 21008400LL);

        goto block278;

block248:
        //Small tile
        WRITE_4b(addr_420600101);
        addr_420600101 += (18910216LL - 18910212LL);

        //Small tile
        READ_4b(addr_420900101);
        addr_420900101 += (18910216LL - 18910212LL);

        //Small tile
        READ_4b(addr_421500101);
        addr_421500101 += (18910216LL - 18910212LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_248 = 0;
        out_248++;
        if (out_248 <= 523522LL) goto block269;
        else goto block278;


block281:
        int dummy;
    }

    // Interval: 800000000 - 826504310
    {
        int64_t addr_427600101 = 23342976LL;
        int64_t addr_428200101 = 23342976LL;
        int64_t addr_423500101 = 19144580LL;
        int64_t addr_424300101 = 19148676LL, strd_424300101 = 0;
        int64_t addr_424700101 = 19144580LL;
        int64_t addr_425300101 = 12868LL, strd_425300101 = 0;
        int64_t addr_425500101 = 19144584LL;
        int64_t addr_425900101 = 14946180LL;
        int64_t addr_426300101 = 10747780LL;
        int64_t addr_426700101 = 6549380LL;
        int64_t addr_427100101 = 2350980LL;
block282:
        goto block284;

block293:
        //Small tile
        READ_4b(addr_423500101);
        addr_423500101 += (19144584LL - 19144580LL);

        //Small tile
        READ_4b(addr_424300101);
        switch(addr_424300101) {
            case 21004300LL : strd_424300101 = (21000208LL - 21004300LL); break;
            case 21000208LL : strd_424300101 = (21000212LL - 21000208LL); break;
            case 19148676LL : strd_424300101 = (19148680LL - 19148676LL); break;
        }
        addr_424300101 += strd_424300101;

        //Small tile
        READ_4b(addr_424700101);
        addr_424700101 += (19144584LL - 19144580LL);

        //Small tile
        READ_4b(addr_425300101);
        switch(addr_425300101) {
            case 13004LL : strd_425300101 = (8912LL - 13004LL); break;
            case 8912LL : strd_425300101 = (8916LL - 8912LL); break;
            case 12868LL : strd_425300101 = (12872LL - 12868LL); break;
        }
        addr_425300101 += strd_425300101;

        //Dominant stride
        READ_4b(addr_425500101);
        addr_425500101 += 4LL;
        if(addr_425500101 >= 21004304LL) addr_425500101 = 19144584LL;

        //Small tile
        READ_4b(addr_425900101);
        addr_425900101 += (14946184LL - 14946180LL);

        //Small tile
        READ_4b(addr_426300101);
        addr_426300101 += (10747784LL - 10747780LL);

        //Small tile
        READ_4b(addr_426700101);
        addr_426700101 += (6549384LL - 6549380LL);

        //Small tile
        READ_4b(addr_427100101);
        addr_427100101 += (2350984LL - 2350980LL);

        goto block284;

block284:
        //Small tile
        READ_4b(addr_427600101);
        addr_427600101 += (23342980LL - 23342976LL);

        //Small tile
        WRITE_4b(addr_428200101);
        addr_428200101 += (23342980LL - 23342976LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_284 = 0;
        out_284++;
        if (out_284 <= 464931LL) goto block293;
        else goto block294;


block294:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
