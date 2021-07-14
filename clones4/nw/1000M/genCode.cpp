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

    // Interval: 0 - 1000000000
    {
        int64_t addr_375200101 = 67149848LL;
        int64_t addr_374600101 = 4116LL, strd_374600101 = 0;
        int64_t addr_408000101 = 4112LL;
        int64_t addr_409400101 = 134284036LL;
        int64_t addr_409000101 = 134283972LL;
        int64_t addr_406400101 = 67149848LL;
        int64_t addr_409800101 = 134283968LL;
        int64_t addr_411900101 = 134284040LL;
        int64_t addr_413400101 = 134284040LL;
block0:
        goto block14;

block14:
        for(uint64_t loop6 = 0; loop6 < 16785409ULL; loop6++){
            //Loop Indexed
            addr = 4112LL + (4 * loop6);
            WRITE_4b(addr);

        }
        for(uint64_t loop5 = 0; loop5 < 16777216ULL; loop5++){
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
            if(addr_375200101 >= 134275092LL) addr_375200101 = 67149848LL;

        }
        for(uint64_t loop4 = 0; loop4 < 32896ULL; loop4++){
            addr_409400101 = 134284036LL;
            addr_409000101 = 134283972LL;
            addr_409800101 = 134283968LL;
            addr_411900101 = 134284040LL;
            addr_413400101 = 134284040LL;
            for(uint64_t loop3 = 0; loop3 < 256ULL; loop3++){
                //Dominant stride
                READ_4b(addr_406400101);
                addr_406400101 += 4LL;
                if(addr_406400101 >= 134258772LL) addr_406400101 = 67149848LL;

                //Loop Indexed
                addr = 134282944LL + (4 * loop3);
                WRITE_4b(addr);

            }
            for(uint64_t loop2 = 0; loop2 < 289ULL; loop2++){
                //Dominant stride
                READ_4b(addr_408000101);
                addr_408000101 += 4LL;
                if(addr_408000101 >= 67129428LL) addr_408000101 = 4112LL;

                //Loop Indexed
                addr = 134283968LL + (4 * loop2);
                WRITE_4b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 256ULL; loop1++){
                //Dominant stride
                READ_4b(addr_409000101);
                addr_409000101 += 4LL;
                if(addr_409000101 >= 134285056LL) addr_409000101 = 134283972LL;

                //Dominant stride
                READ_4b(addr_409400101);
                addr_409400101 += 4LL;
                if(addr_409400101 >= 134285120LL) addr_409400101 = 134284036LL;

                //Dominant stride
                READ_4b(addr_409800101);
                addr_409800101 += 4LL;
                if(addr_409800101 >= 134285052LL) addr_409800101 = 134283968LL;

                //Loop Indexed
                addr = 134282944LL + (4 * loop1);
                READ_4b(addr);

                //Dominant stride
                WRITE_4b(addr_411900101);
                addr_411900101 += 4LL;
                if(addr_411900101 >= 134285124LL) addr_411900101 = 134284040LL;

            }
            for(uint64_t loop0 = 0; loop0 < 256ULL; loop0++){
                //Dominant stride
                READ_4b(addr_413400101);
                addr_413400101 += 4LL;
                if(addr_413400101 >= 134285124LL) addr_413400101 = 134284040LL;

            }
        }
        goto block15;

block15:
        int dummy;
    }

    // Interval: 1000000000 - 1572285377
    {
        int64_t addr_417900101 = 43536528LL;
        int64_t addr_421900101 = 43815064LL;
        int64_t addr_421800101 = 134284040LL;
        int64_t addr_419700101 = 134284656LL;
        int64_t addr_420000101 = 134283592LL, strd_420000101 = 0;
        int64_t addr_420300101 = 134284728LL;
        int64_t addr_418900101 = 134284664LL;
        int64_t addr_419300101 = 134284728LL;
        int64_t addr_416300101 = 110682264LL;
block16:
        goto block19;

block19:
        //Dominant stride
        READ_4b(addr_419700101);
        addr_419700101 += 4LL;
        if(addr_419700101 >= 134285052LL) addr_419700101 = 134283968LL;

        //Small tile
        READ_4b(addr_420000101);
        switch(addr_420000101) {
            case 134283592LL : strd_420000101 = (134283596LL - 134283592LL); break;
            case 134283964LL : strd_420000101 = (134282944LL - 134283964LL); break;
            case 134282944LL : strd_420000101 = (134282948LL - 134282944LL); break;
        }
        addr_420000101 += strd_420000101;

        //Dominant stride
        WRITE_4b(addr_420300101);
        addr_420300101 += 4LL;
        if(addr_420300101 >= 134285124LL) addr_420300101 = 134284040LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_19 = 0;
        cov_19++;
        if(cov_19 <= 8170965ULL) {
            static uint64_t out_19 = 0;
            out_19 = (out_19 == 255LL) ? 1 : (out_19 + 1);
            if (out_19 <= 254LL) goto block21;
            else goto block23;
        }
        else goto block21;

block21:
        //Dominant stride
        READ_4b(addr_418900101);
        addr_418900101 += 4LL;
        if(addr_418900101 >= 134285056LL) addr_418900101 = 134283972LL;

        //Dominant stride
        READ_4b(addr_419300101);
        addr_419300101 += 4LL;
        if(addr_419300101 >= 134285120LL) addr_419300101 = 134284036LL;

        goto block19;

block23:
        for(uint64_t loop7 = 0; loop7 < 256ULL; loop7++){
            //Dominant stride
            READ_4b(addr_421800101);
            addr_421800101 += 4LL;
            if(addr_421800101 >= 134285124LL) addr_421800101 = 134284040LL;

            //Dominant stride
            WRITE_4b(addr_421900101);
            addr_421900101 += 4LL;
            if(addr_421900101 >= 67145748LL) addr_421900101 = 823448LL;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_23 = 0;
        out_23++;
        if (out_23 <= 32042LL) goto block27;
        else goto block28;


block27:
        for(uint64_t loop8 = 0; loop8 < 256ULL; loop8++){
            //Dominant stride
            READ_4b(addr_416300101);
            addr_416300101 += 4LL;
            if(addr_416300101 >= 134275092LL) addr_416300101 = 67952792LL;

            //Loop Indexed
            addr = 134282944LL + (4 * loop8);
            WRITE_4b(addr);

        }
        for(uint64_t loop9 = 0; loop9 < 289ULL; loop9++){
            //Dominant stride
            READ_4b(addr_417900101);
            addr_417900101 += 4LL;
            if(addr_417900101 >= 67145748LL) addr_417900101 = 807056LL;

            //Loop Indexed
            addr = 134283968LL + (4 * loop9);
            WRITE_4b(addr);

        }
        goto block21;

block28:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
