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
    uint64_t allocSize = 134283264ULL;
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
        int64_t addr_374600101 = 4116LL, strd_374600101 = 0;
        int64_t addr_375200101 = 67149848LL;
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
            READ_4b(addr_374600101);
            switch(addr_374600101) {
                case 4116LL : strd_374600101 = (4120LL - 4116LL); break;
                case 20496LL : strd_374600101 = (4116LL - 20496LL); break;
            }
            addr_374600101 += strd_374600101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375200101);
            addr_375200101 += 4LL;
            if(addr_375200101 >= 83516456LL) addr_375200101 = 67149848LL;

        }
        goto block8;

block8:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_374600101 = 15500LL, strd_374600101 = 0;
        int64_t addr_375200101 = 83516456LL;
block9:
        goto block12;

block12:
        for(uint64_t loop3 = 0; loop3 < 6249428ULL; loop3++){
            //Small tile
            READ_4b(addr_374600101);
            switch(addr_374600101) {
                case 15500LL : strd_374600101 = (15504LL - 15500LL); break;
                case 20496LL : strd_374600101 = (4116LL - 20496LL); break;
                case 4116LL : strd_374600101 = (4120LL - 4116LL); break;
            }
            addr_374600101 += strd_374600101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375200101);
            addr_375200101 += 4LL;
            if(addr_375200101 >= 108520272LL) addr_375200101 = 83516456LL;

        }
        goto block13;

block13:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_374600101 = 11228LL, strd_374600101 = 0;
        int64_t addr_375200101 = 108520272LL;
block14:
        goto block17;

block17:
        for(uint64_t loop4 = 0; loop4 < 6249428ULL; loop4++){
            //Small tile
            READ_4b(addr_374600101);
            switch(addr_374600101) {
                case 11228LL : strd_374600101 = (11232LL - 11228LL); break;
                case 4116LL : strd_374600101 = (4120LL - 4116LL); break;
                case 20496LL : strd_374600101 = (4116LL - 20496LL); break;
            }
            addr_374600101 += strd_374600101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375200101);
            addr_375200101 += 4LL;
            if(addr_375200101 >= 133524088LL) addr_375200101 = 108520272LL;

        }
        goto block18;

block18:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_408000101 = 4112LL;
        int64_t addr_406400101 = 67149848LL;
        int64_t addr_409000101 = 134281860LL;
        int64_t addr_409400101 = 134281924LL;
        int64_t addr_409800101 = 134281856LL;
        int64_t addr_410100101 = 134280832LL, strd_410100101 = 0;
        int64_t addr_411900101 = 134281928LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 20504LL;
block19:
        goto block23;

block30:
        for(uint64_t loop5 = 0; loop5 < 256ULL; loop5++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 27273812LL) addr_413500101 = 20504LL;

        }
        goto block23;

block28:
        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
        }
        addr_410100101 += strd_410100101;

        //Few edges. Don't bother optimizing
        static uint64_t out_27 = 0;
        out_27++;
        if (out_27 <= 1392222LL) goto block28;
        else goto block31;


block23:
        for(uint64_t loop6 = 0; loop6 < 256ULL; loop6++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 94403156LL) addr_406400101 = 67149848LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop6);
            WRITE_4b(addr);

        }
        for(uint64_t loop7 = 0; loop7 < 289ULL; loop7++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 27273812LL) addr_408000101 = 4112LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop7);
            WRITE_4b(addr);

        }
        goto block27;

block31:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_408000101 = 5253584LL;
        int64_t addr_409000101 = 134282260LL;
        int64_t addr_409400101 = 134282324LL;
        int64_t addr_409800101 = 134282256LL;
        int64_t addr_410100101 = 134281212LL, strd_410100101 = 0;
        int64_t addr_411900101 = 134282324LL;
        int64_t addr_406400101 = 72399320LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 5532120LL;
block32:
        goto block33;

block33:
        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
            case 134281212LL : strd_410100101 = (134281216LL - 134281212LL); break;
        }
        addr_410100101 += strd_410100101;

        //Few edges. Don't bother optimizing
        static uint64_t out_37 = 0;
        out_37++;
        if (out_37 <= 1436431LL) goto block33;
        else goto block44;


block43:
        for(uint64_t loop9 = 0; loop9 < 256ULL; loop9++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 39073172LL) addr_413500101 = 27096LL;

        }
        for(uint64_t loop10 = 0; loop10 < 256ULL; loop10++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 106202516LL) addr_406400101 = 67156440LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop10);
            WRITE_4b(addr);

        }
        for(uint64_t loop8 = 0; loop8 < 289ULL; loop8++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 39073172LL) addr_408000101 = 10704LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop8);
            WRITE_4b(addr);

        }
        goto block37;

block44:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_408000101 = 32519440LL;
        int64_t addr_409000101 = 134282328LL;
        int64_t addr_411900101 = 134282392LL;
        int64_t addr_409400101 = 134282392LL;
        int64_t addr_409800101 = 134282324LL;
        int64_t addr_410100101 = 134281276LL, strd_410100101 = 0;
        int64_t addr_406400101 = 99665176LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 32797976LL;
block45:
        goto block46;

block56:
        for(uint64_t loop13 = 0; loop13 < 256ULL; loop13++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 47988244LL) addr_413500101 = 29976LL;

        }
        for(uint64_t loop12 = 0; loop12 < 256ULL; loop12++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 115117588LL) addr_406400101 = 67159320LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop12);
            WRITE_4b(addr);

        }
        for(uint64_t loop11 = 0; loop11 < 289ULL; loop11++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 47988244LL) addr_408000101 = 13584LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop11);
            WRITE_4b(addr);

        }
        goto block47;

block46:
        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_47 = 0;
        out_47++;
        if (out_47 <= 1436433LL) goto block50;
        else goto block57;


block50:
        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
            case 134281276LL : strd_410100101 = (134281280LL - 134281276LL); break;
        }
        addr_410100101 += strd_410100101;

        goto block46;

block57:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_408000101 = 45628816LL;
        int64_t addr_409400101 = 134282468LL;
        int64_t addr_409800101 = 134282400LL;
        int64_t addr_410100101 = 134281344LL, strd_410100101 = 0;
        int64_t addr_411900101 = 134282472LL;
        int64_t addr_409000101 = 134282408LL;
        int64_t addr_406400101 = 112774552LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 45907352LL;
block58:
        goto block62;

block62:
        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
            case 134281344LL : strd_410100101 = (134281348LL - 134281344LL); break;
        }
        addr_410100101 += strd_410100101;

        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        goto block62;

block69:
        for(uint64_t loop15 = 0; loop15 < 256ULL; loop15++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 55330068LL) addr_413500101 = 32152LL;

        }
        for(uint64_t loop16 = 0; loop16 < 256ULL; loop16++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 122459412LL) addr_406400101 = 67161496LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop16);
            WRITE_4b(addr);

        }
        for(uint64_t loop14 = 0; loop14 < 289ULL; loop14++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 55330068LL) addr_408000101 = 15760LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop14);
            WRITE_4b(addr);

        }
        goto block63;

block70:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_408000101 = 24396944LL;
        int64_t addr_409000101 = 134282484LL;
        int64_t addr_409400101 = 134282548LL;
        int64_t addr_409800101 = 134282480LL;
        int64_t addr_410100101 = 134281420LL, strd_410100101 = 0;
        int64_t addr_411900101 = 134282552LL;
        int64_t addr_406400101 = 91542680LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 24675480LL;
block71:
        goto block75;

block82:
        for(uint64_t loop19 = 0; loop19 < 256ULL; loop19++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 61885268LL) addr_413500101 = 33944LL;

        }
        for(uint64_t loop18 = 0; loop18 < 256ULL; loop18++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 129014612LL) addr_406400101 = 67163288LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop18);
            WRITE_4b(addr);

        }
        for(uint64_t loop17 = 0; loop17 < 289ULL; loop17++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 61885268LL) addr_408000101 = 17552LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop17);
            WRITE_4b(addr);

        }
        goto block75;

block76:
        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134281420LL : strd_410100101 = (134281424LL - 134281420LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
        }
        addr_410100101 += strd_410100101;

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
        int64_t addr_408000101 = 21514960LL;
        int64_t addr_413400101 = 134281928LL;
        int64_t addr_413500101 = 21793496LL;
        int64_t addr_411900101 = 134282632LL;
        int64_t addr_409000101 = 134282568LL;
        int64_t addr_409400101 = 134282632LL;
        int64_t addr_409800101 = 134282564LL;
        int64_t addr_410100101 = 134281500LL, strd_410100101 = 0;
        int64_t addr_406400101 = 88660696LL;
        int64_t addr_417900101 = 66867216LL;
block84:
        goto block85;

block98:
        for(uint64_t loop22 = 0; loop22 < 598ULL; loop22++){
            for(uint64_t loop21 = 0; loop21 < 256ULL; loop21++){
                //Loop Indexed
                addr = 134280832LL + (4 * loop21);
                WRITE_4b(addr);

            }
            for(uint64_t loop20 = 0; loop20 < 289ULL; loop20++){
                //Dominant stride
                READ_4b(addr_417900101);
                addr_417900101 += 4LL;
                if(addr_417900101 >= 67129620LL) addr_417900101 = 282640LL;

                //Loop Indexed
                addr = 134281856LL + (4 * loop20);
                WRITE_4b(addr);

            }
        }
        goto block99;

block85:
        //Dominant stride
        WRITE_4b(addr_411900101);
        addr_411900101 += 4LL;
        if(addr_411900101 >= 134283012LL) addr_411900101 = 134281928LL;

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
        READ_4b(addr_409000101);
        addr_409000101 += 4LL;
        if(addr_409000101 >= 134282944LL) addr_409000101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_409400101);
        addr_409400101 += 4LL;
        if(addr_409400101 >= 134283008LL) addr_409400101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_409800101);
        addr_409800101 += 4LL;
        if(addr_409800101 >= 134282940LL) addr_409800101 = 134281856LL;

        //Small tile
        READ_4b(addr_410100101);
        switch(addr_410100101) {
            case 134281852LL : strd_410100101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_410100101 = (134280836LL - 134280832LL); break;
            case 134281500LL : strd_410100101 = (134281504LL - 134281500LL); break;
        }
        addr_410100101 += strd_410100101;

        goto block85;

block95:
        for(uint64_t loop25 = 0; loop25 < 256ULL; loop25++){
            //Dominant stride
            READ_4b(addr_406400101);
            addr_406400101 += 4LL;
            if(addr_406400101 >= 134258772LL) addr_406400101 = 67164888LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop25);
            WRITE_4b(addr);

        }
        for(uint64_t loop23 = 0; loop23 < 289ULL; loop23++){
            //Dominant stride
            READ_4b(addr_408000101);
            addr_408000101 += 4LL;
            if(addr_408000101 >= 67129428LL) addr_408000101 = 19152LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop23);
            WRITE_4b(addr);

        }
        goto block89;

block91:
        for(uint64_t loop24 = 0; loop24 < 256ULL; loop24++){
            //Dominant stride
            READ_4b(addr_413400101);
            addr_413400101 += 4LL;
            if(addr_413400101 >= 134283012LL) addr_413400101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_413500101);
            addr_413500101 += 4LL;
            if(addr_413500101 >= 67129428LL) addr_413500101 = 35544LL;

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
        int64_t addr_417900101 = 43536528LL;
        int64_t addr_416300101 = 110682264LL;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_421900101 = 43815064LL;
        int64_t addr_419700101 = 134282544LL;
        int64_t addr_420000101 = 134281480LL, strd_420000101 = 0;
        int64_t addr_418900101 = 134282552LL;
        int64_t addr_419300101 = 134282616LL;
        int64_t addr_420300101 = 134282616LL;
block100:
        goto block102;

block102:
        //Dominant stride
        READ_4b(addr_419700101);
        addr_419700101 += 4LL;
        if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

        //Small tile
        READ_4b(addr_420000101);
        switch(addr_420000101) {
            case 134281480LL : strd_420000101 = (134281484LL - 134281480LL); break;
            case 134281852LL : strd_420000101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_420000101 = (134280836LL - 134280832LL); break;
        }
        addr_420000101 += strd_420000101;

        //Few edges. Don't bother optimizing
        static uint64_t out_102 = 0;
        out_102++;
        if (out_102 <= 1436255LL) goto block103;
        else goto block112;


block111:
        for(uint64_t loop28 = 0; loop28 < 256ULL; loop28++){
            //Dominant stride
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67131092LL) addr_421900101 = 823448LL;

        }
        for(uint64_t loop27 = 0; loop27 < 256ULL; loop27++){
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134260436LL) addr_416300101 = 67952792LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop27);
            WRITE_4b(addr);

        }
        for(uint64_t loop26 = 0; loop26 < 289ULL; loop26++){
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67131092LL) addr_417900101 = 807056LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop26);
            WRITE_4b(addr);

        }
        goto block105;

block103:
        //Dominant stride
        WRITE_4b(addr_420300101);
        addr_420300101 += 4LL;
        if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

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
        READ_4b(addr_418900101);
        addr_418900101 += 4LL;
        if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_419300101);
        addr_419300101 += 4LL;
        if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

        goto block102;

block112:
        int dummy;
    }

    // Interval: 1100000000 - 1200000000
    {
        int64_t addr_417900101 = 31741520LL;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_421900101 = 32020056LL;
        int64_t addr_420300101 = 134281932LL;
        int64_t addr_418900101 = 134281868LL;
        int64_t addr_419300101 = 134281932LL;
        int64_t addr_419700101 = 134281864LL;
        int64_t addr_420000101 = 134280840LL, strd_420000101 = 0;
        int64_t addr_416300101 = 98887256LL;
        int64_t addr_416400101 = 134280832LL, strd_416400101 = 0;
block113:
        goto block114;

block124:
        for(uint64_t loop29 = 0; loop29 < 289ULL; loop29++){
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67132756LL) addr_417900101 = 6837840LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop29);
            WRITE_4b(addr);

        }
        goto block118;

block114:
        //Dominant stride
        WRITE_4b(addr_420300101);
        addr_420300101 += 4LL;
        if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

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
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67132756LL) addr_421900101 = 6854232LL;

        }
        static int64_t loop30_break = 1436299ULL;
        for(uint64_t loop30 = 0; loop30 < 256ULL; loop30++){
            if(loop30_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134262100LL) addr_416300101 = 73983576LL;

            //Small tile
            WRITE_4b(addr_416400101);
            switch(addr_416400101) {
                case 134281852LL : strd_416400101 = (134280832LL - 134281852LL); break;
                case 134280832LL : strd_416400101 = (134280836LL - 134280832LL); break;
            }
            addr_416400101 += strd_416400101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_122 = 0;
        out_122++;
        if (out_122 <= 5610LL) goto block124;
        else goto block125;


block118:
        //Dominant stride
        READ_4b(addr_418900101);
        addr_418900101 += 4LL;
        if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

        //Dominant stride
        READ_4b(addr_419300101);
        addr_419300101 += 4LL;
        if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_419700101);
        addr_419700101 += 4LL;
        if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

        //Small tile
        READ_4b(addr_420000101);
        switch(addr_420000101) {
            case 134281852LL : strd_420000101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_420000101 = (134280836LL - 134280832LL); break;
            case 134280840LL : strd_420000101 = (134280844LL - 134280840LL); break;
        }
        addr_420000101 += strd_420000101;

        goto block114;

block125:
        int dummy;
    }

    // Interval: 1200000000 - 1300000000
    {
        int64_t addr_417900101 = 43539664LL;
        int64_t addr_418900101 = 134281860LL;
        int64_t addr_419300101 = 134281924LL;
        int64_t addr_419700101 = 134281856LL;
        int64_t addr_420000101 = 134280832LL, strd_420000101 = 0;
        int64_t addr_420300101 = 134281928LL;
        int64_t addr_416300101 = 110816548LL;
        int64_t addr_416400101 = 134281388LL, strd_416400101 = 0;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_421900101 = 43556056LL;
block126:
        goto block130;

block137:
        for(uint64_t loop33 = 0; loop33 < 256ULL; loop33++){
            //Dominant stride
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67134676LL) addr_421900101 = 13671640LL;

        }
        goto block130;

block135:
        //Dominant stride
        READ_4b(addr_419300101);
        addr_419300101 += 4LL;
        if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_419700101);
        addr_419700101 += 4LL;
        if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

        //Small tile
        READ_4b(addr_420000101);
        switch(addr_420000101) {
            case 134281852LL : strd_420000101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_420000101 = (134280836LL - 134280832LL); break;
        }
        addr_420000101 += strd_420000101;

        //Dominant stride
        WRITE_4b(addr_420300101);
        addr_420300101 += 4LL;
        if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_135 = 0;
        cov_135++;
        if(cov_135 <= 1430804ULL) {
            static uint64_t out_135 = 0;
            out_135 = (out_135 == 255LL) ? 1 : (out_135 + 1);
            if (out_135 <= 254LL) goto block131;
            else goto block137;
        }
        else goto block131;

block130:
        static int64_t loop32_break = 1436277ULL;
        for(uint64_t loop32 = 0; loop32 < 256ULL; loop32++){
            if(loop32_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134264020LL) addr_416300101 = 80800984LL;

            //Small tile
            WRITE_4b(addr_416400101);
            switch(addr_416400101) {
                case 134281852LL : strd_416400101 = (134280832LL - 134281852LL); break;
                case 134280832LL : strd_416400101 = (134280836LL - 134280832LL); break;
                case 134281388LL : strd_416400101 = (134281392LL - 134281388LL); break;
            }
            addr_416400101 += strd_416400101;

        }
        for(uint64_t loop34 = 0; loop34 < 289ULL; loop34++){
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67134676LL) addr_417900101 = 13655248LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop34);
            WRITE_4b(addr);

        }
        goto block131;

block131:
        //Dominant stride
        READ_4b(addr_418900101);
        addr_418900101 += 4LL;
        if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_131 = 0;
        out_131++;
        if (out_131 <= 1436409LL) goto block135;
        else goto block138;


block138:
        int dummy;
    }

    // Interval: 1300000000 - 1400000000
    {
        int64_t addr_417900101 = 62940240LL;
        int64_t addr_416300101 = 130085976LL;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_421900101 = 63218776LL;
        int64_t addr_419300101 = 134282980LL;
        int64_t addr_419700101 = 134282912LL;
        int64_t addr_420000101 = 134281828LL, strd_420000101 = 0;
        int64_t addr_420300101 = 134282984LL;
        int64_t addr_418900101 = 134282920LL;
block139:
        goto block143;

block150:
        for(uint64_t loop37 = 0; loop37 < 256ULL; loop37++){
            //Dominant stride
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67136916LL) addr_421900101 = 21537880LL;

        }
        for(uint64_t loop36 = 0; loop36 < 256ULL; loop36++){
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134266260LL) addr_416300101 = 88667224LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop36);
            WRITE_4b(addr);

        }
        for(uint64_t loop35 = 0; loop35 < 289ULL; loop35++){
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67136916LL) addr_417900101 = 21521488LL;

            //Loop Indexed
            addr = 134281856LL + (4 * loop35);
            WRITE_4b(addr);

        }
        goto block144;

block143:
        //Dominant stride
        READ_4b(addr_419300101);
        addr_419300101 += 4LL;
        if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

        //Dominant stride
        READ_4b(addr_419700101);
        addr_419700101 += 4LL;
        if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

        //Small tile
        READ_4b(addr_420000101);
        switch(addr_420000101) {
            case 134281852LL : strd_420000101 = (134280832LL - 134281852LL); break;
            case 134280832LL : strd_420000101 = (134280836LL - 134280832LL); break;
            case 134281828LL : strd_420000101 = (134281832LL - 134281828LL); break;
        }
        addr_420000101 += strd_420000101;

        //Dominant stride
        WRITE_4b(addr_420300101);
        addr_420300101 += 4LL;
        if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

        //Unordered
        static uint64_t out_143_150 = 5611LL;
        static uint64_t out_143_144 = 1430641LL;
        tmpRnd = out_143_150 + out_143_144;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_143_150)){
                out_143_150--;
                goto block150;
            }
            else {
                out_143_144--;
                goto block144;
            }
        }
        goto block151;


block144:
        //Dominant stride
        READ_4b(addr_418900101);
        addr_418900101 += 4LL;
        if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

        goto block143;

block151:
        int dummy;
    }

    // Interval: 1400000000 - 1500000000
    {
        int64_t addr_417900101 = 32533776LL;
        int64_t addr_418000101 = 134281856LL, strd_418000101 = 0;
        int64_t addr_416300101 = 99679512LL;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_421900101 = 32812312LL;
        int64_t addr_418900101 = 134282224LL;
        int64_t addr_419300101 = 134282288LL;
        int64_t addr_419700101 = 134282220LL;
        int64_t addr_420000101 = 134281176LL, strd_420000101 = 0;
        int64_t addr_420300101 = 134282292LL;
block152:
        goto block163;

block163:
        for(uint64_t loop42 = 0; loop42 < 5611ULL; loop42++){
            addr_421800101 = 134281928LL;
            static int64_t loop40_break = 1436330ULL;
            for(uint64_t loop40 = 0; loop40 < 256ULL; loop40++){
                if(loop40_break-- <= 0) break;
                //Dominant stride
                READ_4b(addr_418900101);
                addr_418900101 += 4LL;
                if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

                //Dominant stride
                READ_4b(addr_419300101);
                addr_419300101 += 4LL;
                if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

                //Dominant stride
                READ_4b(addr_419700101);
                addr_419700101 += 4LL;
                if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

                //Small tile
                READ_4b(addr_420000101);
                switch(addr_420000101) {
                    case 134281852LL : strd_420000101 = (134280832LL - 134281852LL); break;
                    case 134280832LL : strd_420000101 = (134280836LL - 134280832LL); break;
                    case 134281176LL : strd_420000101 = (134281180LL - 134281176LL); break;
                }
                addr_420000101 += strd_420000101;

                //Dominant stride
                WRITE_4b(addr_420300101);
                addr_420300101 += 4LL;
                if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

            }
            for(uint64_t loop41 = 0; loop41 < 256ULL; loop41++){
                //Dominant stride
                READ_4b(addr_421800101);
                addr_421800101 += 4LL;
                if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

                //Dominant stride
                WRITE_4b(addr_421900101);
                addr_421900101 += 4LL;
                if(addr_421900101 >= 67140116LL) addr_421900101 = 30715160LL;

            }
            for(uint64_t loop39 = 0; loop39 < 256ULL; loop39++){
                //Dominant stride
                READ_4b(addr_416300101);
                addr_416300101 += 4LL;
                if(addr_416300101 >= 134269460LL) addr_416300101 = 97844504LL;

                //Loop Indexed
                addr = 134280832LL + (4 * loop39);
                WRITE_4b(addr);

            }
            static int64_t loop38_break = 1621373ULL;
            for(uint64_t loop38 = 0; loop38 < 289ULL; loop38++){
                if(loop38_break-- <= 0) break;
                //Dominant stride
                READ_4b(addr_417900101);
                addr_417900101 += 4LL;
                if(addr_417900101 >= 67140116LL) addr_417900101 = 30698768LL;

                //Small tile
                WRITE_4b(addr_418000101);
                switch(addr_418000101) {
                    case 134283008LL : strd_418000101 = (134281856LL - 134283008LL); break;
                    case 134281856LL : strd_418000101 = (134281860LL - 134281856LL); break;
                }
                addr_418000101 += strd_418000101;

            }
        }
        goto block164;

block164:
        int dummy;
    }

    // Interval: 1500000000 - 1572285372
    {
        int64_t addr_417900101 = 62749148LL;
        int64_t addr_418000101 = 134282188LL, strd_418000101 = 0;
        int64_t addr_421900101 = 62699928LL;
        int64_t addr_421800101 = 134281928LL;
        int64_t addr_418900101 = 134281860LL;
        int64_t addr_419300101 = 134281924LL;
        int64_t addr_419700101 = 134281856LL;
        int64_t addr_420300101 = 134281928LL;
        int64_t addr_416300101 = 129567128LL;
block165:
        goto block174;

block176:
        for(uint64_t loop43 = 0; loop43 < 256ULL; loop43++){
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134275092LL) addr_416300101 = 110954904LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop43);
            WRITE_4b(addr);

        }
        goto block174;

block174:
        static int64_t loop44_break = 1152738ULL;
        for(uint64_t loop44 = 0; loop44 < 289ULL; loop44++){
            if(loop44_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67145748LL) addr_417900101 = 43809168LL;

            //Small tile
            WRITE_4b(addr_418000101);
            switch(addr_418000101) {
                case 134282188LL : strd_418000101 = (134282192LL - 134282188LL); break;
                case 134283008LL : strd_418000101 = (134281856LL - 134283008LL); break;
                case 134281856LL : strd_418000101 = (134281860LL - 134281856LL); break;
            }
            addr_418000101 += strd_418000101;

        }
        for(uint64_t loop46 = 0; loop46 < 256ULL; loop46++){
            //Dominant stride
            READ_4b(addr_418900101);
            addr_418900101 += 4LL;
            if(addr_418900101 >= 134282944LL) addr_418900101 = 134281860LL;

            //Dominant stride
            READ_4b(addr_419300101);
            addr_419300101 += 4LL;
            if(addr_419300101 >= 134283008LL) addr_419300101 = 134281924LL;

            //Dominant stride
            READ_4b(addr_419700101);
            addr_419700101 += 4LL;
            if(addr_419700101 >= 134282940LL) addr_419700101 = 134281856LL;

            //Loop Indexed
            addr = 134280832LL + (4 * loop46);
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_420300101);
            addr_420300101 += 4LL;
            if(addr_420300101 >= 134283012LL) addr_420300101 = 134281928LL;

        }
        for(uint64_t loop45 = 0; loop45 < 256ULL; loop45++){
            //Dominant stride
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134283012LL) addr_421800101 = 134281928LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67145748LL) addr_421900101 = 43825560LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_174 = 0;
        out_174++;
        if (out_174 <= 3988LL) goto block176;
        else goto block177;


block177:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
