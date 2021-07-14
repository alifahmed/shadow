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

    // Interval: 0 - 100000000
    {
block0:
        goto block1;

block1:
        for(uint64_t loop0 = 0; loop0 < 12495467ULL; loop0++){
            //Loop Indexed
            addr = 4112LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block2;

block2:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_374700101 = 4116LL, strd_374700101 = 0;
        int64_t addr_375300101 = 67149848LL;
block3:
        goto block7;

block7:
        for(uint64_t loop2 = 0; loop2 < 4289942ULL; loop2++){
            //Loop Indexed
            addr = 49985980LL + (4 * loop2);
            WRITE_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 4090654ULL; loop1++){
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
        goto block8;

block8:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_374700101 = 15500LL, strd_374700101 = 0;
        int64_t addr_375300101 = 83516456LL;
block9:
        goto block12;

block12:
        for(uint64_t loop3 = 0; loop3 < 6249428ULL; loop3++){
            //Small tile
            READ_4b(addr_374700101);
            switch(addr_374700101) {
                case 20496LL : strd_374700101 = (4116LL - 20496LL); break;
                case 4116LL : strd_374700101 = (4120LL - 4116LL); break;
                case 15500LL : strd_374700101 = (15504LL - 15500LL); break;
            }
            addr_374700101 += strd_374700101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375300101);
            addr_375300101 += 4LL;
            if(addr_375300101 >= 108520272LL) addr_375300101 = 83516456LL;

        }
        goto block13;

block13:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_374700101 = 11228LL, strd_374700101 = 0;
        int64_t addr_375300101 = 108520272LL;
block14:
        goto block17;

block17:
        for(uint64_t loop4 = 0; loop4 < 6249428ULL; loop4++){
            //Small tile
            READ_4b(addr_374700101);
            switch(addr_374700101) {
                case 11228LL : strd_374700101 = (11232LL - 11228LL); break;
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
            if(addr_375300101 >= 133524088LL) addr_375300101 = 108520272LL;

        }
        goto block18;

block18:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_408100101 = 4112LL;
        int64_t addr_406500101 = 67149848LL;
        int64_t addr_409100101 = 134059204LL;
        int64_t addr_409500101 = 134059268LL;
        int64_t addr_409900101 = 134059200LL;
        int64_t addr_410200101 = 134058176LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134059272LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 20504LL;
block19:
        goto block23;

block30:
        for(uint64_t loop5 = 0; loop5 < 256ULL; loop5++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 27273812LL) addr_413600101 = 20504LL;

        }
        goto block23;

block28:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_28 = 0;
        cov_28++;
        if(cov_28 <= 1386944ULL) {
            static uint64_t out_28 = 0;
            out_28 = (out_28 == 255LL) ? 1 : (out_28 + 1);
            if (out_28 <= 254LL) goto block27;
            else goto block30;
        }
        else goto block27;

block27:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
        }
        addr_410200101 += strd_410200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_27 = 0;
        out_27++;
        if (out_27 <= 1392222LL) goto block28;
        else goto block31;


block23:
        for(uint64_t loop6 = 0; loop6 < 256ULL; loop6++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 94403156LL) addr_406500101 = 67149848LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop6);
            WRITE_4b(addr);

        }
        for(uint64_t loop7 = 0; loop7 < 289ULL; loop7++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 27273812LL) addr_408100101 = 4112LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop7);
            WRITE_4b(addr);

        }
        goto block27;

block31:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_408100101 = 5253584LL;
        int64_t addr_409100101 = 134059604LL;
        int64_t addr_409500101 = 134059668LL;
        int64_t addr_409900101 = 134059600LL;
        int64_t addr_410200101 = 134058556LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134059668LL;
        int64_t addr_406500101 = 72399320LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 5532120LL;
block32:
        goto block33;

block33:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_33 = 0;
        cov_33++;
        if(cov_33 <= 1431059ULL) {
            static uint64_t out_33 = 0;
            out_33 = (out_33 == 255LL) ? 1 : (out_33 + 1);
            if (out_33 <= 254LL) goto block37;
            else goto block43;
        }
        else goto block37;

block37:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
            case 134058556LL : strd_410200101 = (134058560LL - 134058556LL); break;
        }
        addr_410200101 += strd_410200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_37 = 0;
        out_37++;
        if (out_37 <= 1436431LL) goto block33;
        else goto block44;


block43:
        for(uint64_t loop9 = 0; loop9 < 256ULL; loop9++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 39073172LL) addr_413600101 = 27096LL;

        }
        for(uint64_t loop10 = 0; loop10 < 256ULL; loop10++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 106202516LL) addr_406500101 = 67156440LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop10);
            WRITE_4b(addr);

        }
        for(uint64_t loop8 = 0; loop8 < 289ULL; loop8++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 39073172LL) addr_408100101 = 10704LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop8);
            WRITE_4b(addr);

        }
        goto block37;

block44:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_408100101 = 32519440LL;
        int64_t addr_409100101 = 134059672LL;
        int64_t addr_412000101 = 134059736LL;
        int64_t addr_409500101 = 134059736LL;
        int64_t addr_409900101 = 134059668LL;
        int64_t addr_410200101 = 134058620LL, strd_410200101 = 0;
        int64_t addr_406500101 = 99665176LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 32797976LL;
block45:
        goto block46;

block56:
        for(uint64_t loop13 = 0; loop13 < 256ULL; loop13++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 47988244LL) addr_413600101 = 29976LL;

        }
        for(uint64_t loop12 = 0; loop12 < 256ULL; loop12++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 115117588LL) addr_406500101 = 67159320LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop12);
            WRITE_4b(addr);

        }
        for(uint64_t loop11 = 0; loop11 < 289ULL; loop11++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 47988244LL) addr_408100101 = 13584LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop11);
            WRITE_4b(addr);

        }
        goto block47;

block46:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_46 = 0;
        cov_46++;
        if(cov_46 <= 1431059ULL) {
            static uint64_t out_46 = 0;
            out_46 = (out_46 == 255LL) ? 1 : (out_46 + 1);
            if (out_46 <= 254LL) goto block47;
            else goto block56;
        }
        else goto block47;

block47:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_47 = 0;
        out_47++;
        if (out_47 <= 1436433LL) goto block50;
        else goto block57;


block50:
        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
            case 134058620LL : strd_410200101 = (134058624LL - 134058620LL); break;
        }
        addr_410200101 += strd_410200101;

        goto block46;

block57:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_408100101 = 45628816LL;
        int64_t addr_409500101 = 134059812LL;
        int64_t addr_409900101 = 134059744LL;
        int64_t addr_410200101 = 134058688LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134059816LL;
        int64_t addr_409100101 = 134059752LL;
        int64_t addr_406500101 = 112774552LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 45907352LL;
block58:
        goto block62;

block62:
        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
            case 134058688LL : strd_410200101 = (134058692LL - 134058688LL); break;
        }
        addr_410200101 += strd_410200101;

        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Unordered
        static uint64_t out_62_63 = 1430823LL;
        static uint64_t out_62_69 = 5611LL;
        tmpRnd = out_62_63 + out_62_69;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_62_63)){
                out_62_63--;
                goto block63;
            }
            else {
                out_62_69--;
                goto block69;
            }
        }
        goto block70;


block63:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        goto block62;

block69:
        for(uint64_t loop15 = 0; loop15 < 256ULL; loop15++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 55330068LL) addr_413600101 = 32152LL;

        }
        for(uint64_t loop16 = 0; loop16 < 256ULL; loop16++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 122459412LL) addr_406500101 = 67161496LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop16);
            WRITE_4b(addr);

        }
        for(uint64_t loop14 = 0; loop14 < 289ULL; loop14++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 55330068LL) addr_408100101 = 15760LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop14);
            WRITE_4b(addr);

        }
        goto block63;

block70:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_408100101 = 24396944LL;
        int64_t addr_409100101 = 134059828LL;
        int64_t addr_409500101 = 134059892LL;
        int64_t addr_409900101 = 134059824LL;
        int64_t addr_410200101 = 134058764LL, strd_410200101 = 0;
        int64_t addr_412000101 = 134059896LL;
        int64_t addr_406500101 = 91542680LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 24675480LL;
block71:
        goto block75;

block82:
        for(uint64_t loop19 = 0; loop19 < 256ULL; loop19++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 61885268LL) addr_413600101 = 33944LL;

        }
        for(uint64_t loop18 = 0; loop18 < 256ULL; loop18++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 129014612LL) addr_406500101 = 67163288LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop18);
            WRITE_4b(addr);

        }
        for(uint64_t loop17 = 0; loop17 < 289ULL; loop17++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 61885268LL) addr_408100101 = 17552LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop17);
            WRITE_4b(addr);

        }
        goto block75;

block76:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_76 = 0;
        cov_76++;
        if(cov_76 <= 1431059ULL) {
            static uint64_t out_76 = 0;
            out_76 = (out_76 == 255LL) ? 1 : (out_76 + 1);
            if (out_76 <= 254LL) goto block75;
            else goto block82;
        }
        else goto block75;

block75:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058764LL : strd_410200101 = (134058768LL - 134058764LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
        }
        addr_410200101 += strd_410200101;

        //Few edges. Don't bother optimizing
        static uint64_t out_75 = 0;
        out_75++;
        if (out_75 <= 1436435LL) goto block76;
        else goto block83;


block83:
        int dummy;
    }

    // Interval: 900000000 - 1000000000
    {
        int64_t addr_408100101 = 21514960LL;
        int64_t addr_413500101 = 134059272LL;
        int64_t addr_413600101 = 21793496LL;
        int64_t addr_412000101 = 134059976LL;
        int64_t addr_409100101 = 134059912LL;
        int64_t addr_409500101 = 134059976LL;
        int64_t addr_409900101 = 134059908LL;
        int64_t addr_410200101 = 134058844LL, strd_410200101 = 0;
        int64_t addr_406500101 = 88660696LL;
        int64_t addr_418000101 = 66867216LL;
block84:
        goto block85;

block98:
        for(uint64_t loop22 = 0; loop22 < 598ULL; loop22++){
            for(uint64_t loop21 = 0; loop21 < 256ULL; loop21++){
                //Loop Indexed
                addr = 134058176LL + (4 * loop21);
                WRITE_4b(addr);

            }
            for(uint64_t loop20 = 0; loop20 < 289ULL; loop20++){
                //Dominant stride
                READ_4b(addr_418000101);
                addr_418000101 += 4LL;
                if(addr_418000101 >= 67129620LL) addr_418000101 = 282640LL;

                //Loop Indexed
                addr = 134059200LL + (4 * loop20);
                WRITE_4b(addr);

            }
        }
        goto block99;

block85:
        //Dominant stride
        WRITE_4b(addr_412000101);
        addr_412000101 += 4LL;
        if(addr_412000101 >= 134060356LL) addr_412000101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_85 = 0;
        cov_85++;
        if(cov_85 <= 1278570ULL) {
            static uint64_t out_85 = 0;
            out_85 = (out_85 == 255LL) ? 1 : (out_85 + 1);
            if (out_85 <= 254LL) goto block89;
            else goto block91;
        }
        else goto block89;

block89:
        //Dominant stride
        READ_4b(addr_409100101);
        addr_409100101 += 4LL;
        if(addr_409100101 >= 134060288LL) addr_409100101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_409500101);
        addr_409500101 += 4LL;
        if(addr_409500101 >= 134060352LL) addr_409500101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_409900101);
        addr_409900101 += 4LL;
        if(addr_409900101 >= 134060284LL) addr_409900101 = 134059200LL;

        //Small tile
        READ_4b(addr_410200101);
        switch(addr_410200101) {
            case 134059196LL : strd_410200101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_410200101 = (134058180LL - 134058176LL); break;
            case 134058844LL : strd_410200101 = (134058848LL - 134058844LL); break;
        }
        addr_410200101 += strd_410200101;

        goto block85;

block95:
        for(uint64_t loop25 = 0; loop25 < 256ULL; loop25++){
            //Dominant stride
            READ_4b(addr_406500101);
            addr_406500101 += 4LL;
            if(addr_406500101 >= 134049876LL) addr_406500101 = 67164888LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop25);
            WRITE_4b(addr);

        }
        for(uint64_t loop23 = 0; loop23 < 289ULL; loop23++){
            //Dominant stride
            READ_4b(addr_408100101);
            addr_408100101 += 4LL;
            if(addr_408100101 >= 67129428LL) addr_408100101 = 19152LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop23);
            WRITE_4b(addr);

        }
        goto block89;

block91:
        for(uint64_t loop24 = 0; loop24 < 256ULL; loop24++){
            //Dominant stride
            READ_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 134060356LL) addr_413500101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_413600101);
            addr_413600101 += 4LL;
            if(addr_413600101 >= 67129428LL) addr_413600101 = 35544LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_91 = 0;
        out_91++;
        if (out_91 <= 5013LL) goto block95;
        else goto block98;


block99:
        int dummy;
    }

    // Interval: 1000000000 - 1100000000
    {
        int64_t addr_418000101 = 43536528LL;
        int64_t addr_416400101 = 110682264LL;
        int64_t addr_421900101 = 134059272LL;
        int64_t addr_422000101 = 43815064LL;
        int64_t addr_419800101 = 134059888LL;
        int64_t addr_420100101 = 134058824LL, strd_420100101 = 0;
        int64_t addr_419000101 = 134059896LL;
        int64_t addr_419400101 = 134059960LL;
        int64_t addr_420400101 = 134059960LL;
block100:
        goto block102;

block102:
        //Dominant stride
        READ_4b(addr_419800101);
        addr_419800101 += 4LL;
        if(addr_419800101 >= 134060284LL) addr_419800101 = 134059200LL;

        //Small tile
        READ_4b(addr_420100101);
        switch(addr_420100101) {
            case 134059196LL : strd_420100101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_420100101 = (134058180LL - 134058176LL); break;
            case 134058824LL : strd_420100101 = (134058828LL - 134058824LL); break;
        }
        addr_420100101 += strd_420100101;

        //Few edges. Don't bother optimizing
        static uint64_t out_102 = 0;
        out_102++;
        if (out_102 <= 1436255LL) goto block103;
        else goto block112;


block111:
        for(uint64_t loop28 = 0; loop28 < 256ULL; loop28++){
            //Dominant stride
            READ_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 134060356LL) addr_421900101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_422000101);
            addr_422000101 += 4LL;
            if(addr_422000101 >= 67131092LL) addr_422000101 = 823448LL;

        }
        for(uint64_t loop27 = 0; loop27 < 256ULL; loop27++){
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134051540LL) addr_416400101 = 67952792LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop27);
            WRITE_4b(addr);

        }
        for(uint64_t loop26 = 0; loop26 < 289ULL; loop26++){
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67131092LL) addr_418000101 = 807056LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop26);
            WRITE_4b(addr);

        }
        goto block105;

block103:
        //Dominant stride
        WRITE_4b(addr_420400101);
        addr_420400101 += 4LL;
        if(addr_420400101 >= 134060356LL) addr_420400101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_103 = 0;
        cov_103++;
        if(cov_103 <= 1431059ULL) {
            static uint64_t out_103 = 0;
            out_103 = (out_103 == 255LL) ? 1 : (out_103 + 1);
            if (out_103 <= 254LL) goto block105;
            else goto block111;
        }
        else goto block105;

block105:
        //Dominant stride
        READ_4b(addr_419000101);
        addr_419000101 += 4LL;
        if(addr_419000101 >= 134060288LL) addr_419000101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_419400101);
        addr_419400101 += 4LL;
        if(addr_419400101 >= 134060352LL) addr_419400101 = 134059268LL;

        goto block102;

block112:
        int dummy;
    }

    // Interval: 1100000000 - 1200000000
    {
        int64_t addr_418000101 = 31741520LL;
        int64_t addr_421900101 = 134059272LL;
        int64_t addr_422000101 = 32020056LL;
        int64_t addr_420400101 = 134059276LL;
        int64_t addr_419000101 = 134059212LL;
        int64_t addr_419400101 = 134059276LL;
        int64_t addr_419800101 = 134059208LL;
        int64_t addr_420100101 = 134058184LL, strd_420100101 = 0;
        int64_t addr_416400101 = 98887256LL;
        int64_t addr_416500101 = 134058176LL, strd_416500101 = 0;
block113:
        goto block114;

block124:
        for(uint64_t loop29 = 0; loop29 < 289ULL; loop29++){
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67132756LL) addr_418000101 = 6837840LL;

            //Loop Indexed
            addr = 134059200LL + (4 * loop29);
            WRITE_4b(addr);

        }
        goto block118;

block114:
        //Dominant stride
        WRITE_4b(addr_420400101);
        addr_420400101 += 4LL;
        if(addr_420400101 >= 134060356LL) addr_420400101 = 134059272LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_114 = 0;
        cov_114++;
        if(cov_114 <= 1430805ULL) {
            static uint64_t out_114 = 0;
            out_114 = (out_114 == 255LL) ? 1 : (out_114 + 1);
            if (out_114 <= 254LL) goto block118;
            else goto block122;
        }
        else goto block118;

block122:
        for(uint64_t loop31 = 0; loop31 < 256ULL; loop31++){
            //Dominant stride
            READ_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 134060356LL) addr_421900101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_422000101);
            addr_422000101 += 4LL;
            if(addr_422000101 >= 67132756LL) addr_422000101 = 6854232LL;

        }
        static int64_t loop30_break = 1436299ULL;
        for(uint64_t loop30 = 0; loop30 < 256ULL; loop30++){
            if(loop30_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134053204LL) addr_416400101 = 73983576LL;

            //Small tile
            WRITE_4b(addr_416500101);
            switch(addr_416500101) {
                case 134059196LL : strd_416500101 = (134058176LL - 134059196LL); break;
                case 134058176LL : strd_416500101 = (134058180LL - 134058176LL); break;
            }
            addr_416500101 += strd_416500101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_122 = 0;
        out_122++;
        if (out_122 <= 5610LL) goto block124;
        else goto block125;


block118:
        //Dominant stride
        READ_4b(addr_419000101);
        addr_419000101 += 4LL;
        if(addr_419000101 >= 134060288LL) addr_419000101 = 134059204LL;

        //Dominant stride
        READ_4b(addr_419400101);
        addr_419400101 += 4LL;
        if(addr_419400101 >= 134060352LL) addr_419400101 = 134059268LL;

        //Dominant stride
        READ_4b(addr_419800101);
        addr_419800101 += 4LL;
        if(addr_419800101 >= 134060284LL) addr_419800101 = 134059200LL;

        //Small tile
        READ_4b(addr_420100101);
        switch(addr_420100101) {
            case 134059196LL : strd_420100101 = (134058176LL - 134059196LL); break;
            case 134058176LL : strd_420100101 = (134058180LL - 134058176LL); break;
            case 134058184LL : strd_420100101 = (134058188LL - 134058184LL); break;
        }
        addr_420100101 += strd_420100101;

        goto block114;

block125:
        int dummy;
    }

    // Interval: 1200000000 - 1270866273
    {
        int64_t addr_418000101 = 43539664LL;
        int64_t addr_418100101 = 134059200LL, strd_418100101 = 0;
        int64_t addr_416400101 = 110816548LL;
        int64_t addr_416500101 = 134058732LL, strd_416500101 = 0;
        int64_t addr_419000101 = 134059204LL;
        int64_t addr_419400101 = 134059268LL;
        int64_t addr_419800101 = 134059200LL;
        int64_t addr_420400101 = 134059272LL;
        int64_t addr_421900101 = 134059272LL;
        int64_t addr_422000101 = 43556056LL;
block126:
        goto block130;

block137:
        for(uint64_t loop34 = 0; loop34 < 256ULL; loop34++){
            //Dominant stride
            READ_4b(addr_419000101);
            addr_419000101 += 4LL;
            if(addr_419000101 >= 134060288LL) addr_419000101 = 134059204LL;

            //Dominant stride
            READ_4b(addr_419400101);
            addr_419400101 += 4LL;
            if(addr_419400101 >= 134060352LL) addr_419400101 = 134059268LL;

            //Dominant stride
            READ_4b(addr_419800101);
            addr_419800101 += 4LL;
            if(addr_419800101 >= 134060284LL) addr_419800101 = 134059200LL;

            //Loop Indexed
            addr = 134058176LL + (4 * loop34);
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_420400101);
            addr_420400101 += 4LL;
            if(addr_420400101 >= 134060356LL) addr_420400101 = 134059272LL;

        }
        for(uint64_t loop33 = 0; loop33 < 256ULL; loop33++){
            //Dominant stride
            READ_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 134060356LL) addr_421900101 = 134059272LL;

            //Dominant stride
            WRITE_4b(addr_422000101);
            addr_422000101 += 4LL;
            if(addr_422000101 >= 67134036LL) addr_422000101 = 13671640LL;

        }
        goto block130;

block130:
        static int64_t loop32_break = 1017973ULL;
        for(uint64_t loop32 = 0; loop32 < 256ULL; loop32++){
            if(loop32_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134054484LL) addr_416400101 = 80800984LL;

            //Small tile
            WRITE_4b(addr_416500101);
            switch(addr_416500101) {
                case 134059196LL : strd_416500101 = (134058176LL - 134059196LL); break;
                case 134058176LL : strd_416500101 = (134058180LL - 134058176LL); break;
                case 134058732LL : strd_416500101 = (134058736LL - 134058732LL); break;
            }
            addr_416500101 += strd_416500101;

        }
        static int64_t loop35_break = 1149100ULL;
        for(uint64_t loop35 = 0; loop35 < 289ULL; loop35++){
            if(loop35_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67134036LL) addr_418000101 = 13655248LL;

            //Small tile
            WRITE_4b(addr_418100101);
            switch(addr_418100101) {
                case 134060352LL : strd_418100101 = (134059200LL - 134060352LL); break;
                case 134059200LL : strd_418100101 = (134059204LL - 134059200LL); break;
            }
            addr_418100101 += strd_418100101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_130 = 0;
        out_130++;
        if (out_130 <= 3976LL) goto block137;
        else goto block138;


block138:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
