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
    uint64_t allocSize = 117501952ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 500000000
    {
        int64_t addr_399500101 = 117494224LL, strd_399500101 = 0;
        int64_t addr_399300101 = 117494212LL, strd_399300101 = 0;
        int64_t addr_399400101 = 117494224LL, strd_399400101 = 0;
        int64_t addr_410800101 = 50368528LL;
        int64_t addr_410400101 = 83931152LL, strd_410400101 = 0;
        int64_t addr_409600101 = 83931152LL;
        int64_t addr_411900101 = 33587216LL;
        int64_t addr_412400101 = 704LL, strd_412400101 = 0;
        int64_t addr_412600101 = 83931152LL;
        int64_t addr_413000101 = 16805904LL;
        int64_t addr_413500101 = 13008LL, strd_413500101 = 0;
        int64_t addr_413700101 = 83931156LL;
        int64_t addr_414100101 = 24592LL;
        int64_t addr_414400101 = 50368528LL;
        int64_t addr_414700101 = 50368528LL;
        int64_t addr_415000101 = 33587216LL;
        int64_t addr_415300101 = 33587216LL;
        int64_t addr_415600101 = 16805904LL;
        int64_t addr_411500101 = 83939344LL;
        int64_t addr_415900101 = 16805904LL;
        int64_t addr_416200101 = 24592LL;
        int64_t addr_416500101 = 24592LL;
        int64_t addr_417000101 = 50368528LL;
        int64_t addr_417300101 = 33587216LL;
        int64_t addr_417600101 = 16805904LL;
        int64_t addr_417900101 = 24592LL;
block0:
        goto block7;

block30:
        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (83939348LL - 83939344LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (33587220LL - 33587216LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 92840976LL) addr_412600101 = 83931152LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (16805908LL - 16805904LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 92840984LL) addr_413700101 = 83931156LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (24596LL - 24592LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (50368532LL - 50368528LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (50368532LL - 50368528LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (33587220LL - 33587216LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (33587220LL - 33587216LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (16805908LL - 16805904LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (16805908LL - 16805904LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (24596LL - 24592LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (24596LL - 24592LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (50368532LL - 50368528LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (33587220LL - 33587216LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (16805908LL - 16805904LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (24596LL - 24592LL);

        goto block10;

block10:
        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (83931156LL - 83931152LL);

        //Small tile
        READ_4b(addr_410400101);
        switch(addr_410400101) {
            case 83931152LL : strd_410400101 = (83931156LL - 83931152LL); break;
            case 83939340LL : strd_410400101 = (83931152LL - 83939340LL); break;
        }
        addr_410400101 += strd_410400101;

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (50368532LL - 50368528LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_10 = 0;
        out_10++;
        if (out_10 <= 2227457LL) goto block30;
        else goto block31;


block7:
        for(uint64_t loop1 = 0; loop1 < 4194304ULL; loop1++){
            //Small tile
            READ_4b(addr_399300101);
            switch(addr_399300101) {
                case 117494212LL : strd_399300101 = (117494216LL - 117494212LL); break;
                case 117494332LL : strd_399300101 = (117494212LL - 117494332LL); break;
            }
            addr_399300101 += strd_399300101;

            //Small tile
            READ_4b(addr_399400101);
            switch(addr_399400101) {
                case 117494224LL : strd_399400101 = (117494228LL - 117494224LL); break;
                case 117494212LL : strd_399400101 = (117494216LL - 117494212LL); break;
                case 117494332LL : strd_399400101 = (117494212LL - 117494332LL); break;
            }
            addr_399400101 += strd_399400101;

            //Small tile
            WRITE_4b(addr_399500101);
            switch(addr_399500101) {
                case 117494224LL : strd_399500101 = (117494228LL - 117494224LL); break;
                case 117494212LL : strd_399500101 = (117494216LL - 117494212LL); break;
                case 117494332LL : strd_399500101 = (117494212LL - 117494332LL); break;
            }
            addr_399500101 += strd_399500101;

            //Loop Indexed
            addr = 100712464LL + (4 * loop1);
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 4194304ULL; loop0++){
            //Loop Indexed
            addr = 100712464LL + (4 * loop0);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(117499104LL - 117498848LL) + 117498848LL) & ~7ULL;
            READ_8b(addr);

            //Loop Indexed
            addr = 83931152LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block10;

block31:
        int dummy;
    }

    // Interval: 500000000 - 1000000000
    {
        int64_t addr_424200101 = 67158032LL, strd_424200101 = 0;
        int64_t addr_425200101 = 13008LL, strd_425200101 = 0;
        int64_t addr_425400101 = 67149844LL;
        int64_t addr_415600101 = 25715732LL, strd_415600101 = 0;
        int64_t addr_415300101 = 42497044LL, strd_415300101 = 0;
        int64_t addr_415000101 = 42497044LL, strd_415000101 = 0;
        int64_t addr_414700101 = 59278356LL, strd_414700101 = 0;
        int64_t addr_414400101 = 59278356LL, strd_414400101 = 0;
        int64_t addr_414100101 = 8934420LL, strd_414100101 = 0;
        int64_t addr_413700101 = 92840984LL;
        int64_t addr_413500101 = 18132LL, strd_413500101 = 0;
        int64_t addr_413000101 = 25715732LL, strd_413000101 = 0;
        int64_t addr_412600101 = 92840976LL;
        int64_t addr_412400101 = 5828LL, strd_412400101 = 0;
        int64_t addr_411900101 = 42497044LL, strd_411900101 = 0;
        int64_t addr_411500101 = 92849172LL;
        int64_t addr_421400101 = 76059668LL, strd_421400101 = 0;
        int64_t addr_420800101 = 76059668LL, strd_420800101 = 0;
        int64_t addr_420500101 = 76059668LL, strd_420500101 = 0;
        int64_t addr_417900101 = 8934420LL, strd_417900101 = 0;
        int64_t addr_417600101 = 25715732LL, strd_417600101 = 0;
        int64_t addr_417300101 = 42497044LL, strd_417300101 = 0;
        int64_t addr_417000101 = 59278356LL, strd_417000101 = 0;
        int64_t addr_416500101 = 8934420LL, strd_416500101 = 0;
        int64_t addr_416200101 = 8934420LL, strd_416200101 = 0;
        int64_t addr_415900101 = 25715732LL, strd_415900101 = 0;
block32:
        goto block45;

block45:
        //Dominant stride
        READ_4b(addr_411500101);
        addr_411500101 += 4LL;
        if(addr_411500101 >= 100708368LL) addr_411500101 = 83939344LL;

        //Small tile
        WRITE_4b(addr_411900101);
        switch(addr_411900101) {
            case 33587216LL : strd_411900101 = (33587220LL - 33587216LL); break;
            case 42497044LL : strd_411900101 = (42497048LL - 42497044LL); break;
            case 50364428LL : strd_411900101 = (33587216LL - 50364428LL); break;
        }
        addr_411900101 += strd_411900101;

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 5828LL : strd_412400101 = (5832LL - 5828LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 100708364LL) addr_412600101 = 83931152LL;

        //Small tile
        WRITE_4b(addr_413000101);
        switch(addr_413000101) {
            case 25715732LL : strd_413000101 = (25715736LL - 25715732LL); break;
            case 33583116LL : strd_413000101 = (16805904LL - 33583116LL); break;
            case 16805904LL : strd_413000101 = (16805908LL - 16805904LL); break;
        }
        addr_413000101 += strd_413000101;

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 18132LL : strd_413500101 = (18136LL - 18132LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 100708368LL) addr_413700101 = 83931156LL;

        //Small tile
        WRITE_4b(addr_414100101);
        switch(addr_414100101) {
            case 8934420LL : strd_414100101 = (8934424LL - 8934420LL); break;
            case 16801804LL : strd_414100101 = (24592LL - 16801804LL); break;
            case 24592LL : strd_414100101 = (24596LL - 24592LL); break;
        }
        addr_414100101 += strd_414100101;

        //Small tile
        READ_4b(addr_414400101);
        switch(addr_414400101) {
            case 59278356LL : strd_414400101 = (59278360LL - 59278356LL); break;
            case 67145740LL : strd_414400101 = (50368528LL - 67145740LL); break;
            case 50368528LL : strd_414400101 = (50368532LL - 50368528LL); break;
        }
        addr_414400101 += strd_414400101;

        //Small tile
        READ_4b(addr_414700101);
        switch(addr_414700101) {
            case 59278356LL : strd_414700101 = (59278360LL - 59278356LL); break;
            case 67145740LL : strd_414700101 = (50368528LL - 67145740LL); break;
            case 50368528LL : strd_414700101 = (50368532LL - 50368528LL); break;
        }
        addr_414700101 += strd_414700101;

        //Small tile
        READ_4b(addr_415000101);
        switch(addr_415000101) {
            case 33587216LL : strd_415000101 = (33587220LL - 33587216LL); break;
            case 42497044LL : strd_415000101 = (42497048LL - 42497044LL); break;
            case 50364428LL : strd_415000101 = (33587216LL - 50364428LL); break;
        }
        addr_415000101 += strd_415000101;

        //Small tile
        READ_4b(addr_415300101);
        switch(addr_415300101) {
            case 33587216LL : strd_415300101 = (33587220LL - 33587216LL); break;
            case 42497044LL : strd_415300101 = (42497048LL - 42497044LL); break;
            case 50364428LL : strd_415300101 = (33587216LL - 50364428LL); break;
        }
        addr_415300101 += strd_415300101;

        //Small tile
        READ_4b(addr_415600101);
        switch(addr_415600101) {
            case 25715732LL : strd_415600101 = (25715736LL - 25715732LL); break;
            case 33583116LL : strd_415600101 = (16805904LL - 33583116LL); break;
            case 16805904LL : strd_415600101 = (16805908LL - 16805904LL); break;
        }
        addr_415600101 += strd_415600101;

        //Few edges. Don't bother optimizing
        static uint64_t out_45 = 0;
        out_45++;
        if (out_45 <= 2061955LL) goto block55;
        else goto block67;


block55:
        //Small tile
        READ_4b(addr_415900101);
        switch(addr_415900101) {
            case 25715732LL : strd_415900101 = (25715736LL - 25715732LL); break;
            case 33583116LL : strd_415900101 = (16805904LL - 33583116LL); break;
            case 16805904LL : strd_415900101 = (16805908LL - 16805904LL); break;
        }
        addr_415900101 += strd_415900101;

        //Small tile
        READ_4b(addr_416200101);
        switch(addr_416200101) {
            case 8934420LL : strd_416200101 = (8934424LL - 8934420LL); break;
            case 16801804LL : strd_416200101 = (24592LL - 16801804LL); break;
            case 24592LL : strd_416200101 = (24596LL - 24592LL); break;
        }
        addr_416200101 += strd_416200101;

        //Small tile
        READ_4b(addr_416500101);
        switch(addr_416500101) {
            case 8934420LL : strd_416500101 = (8934424LL - 8934420LL); break;
            case 16801804LL : strd_416500101 = (24592LL - 16801804LL); break;
            case 24592LL : strd_416500101 = (24596LL - 24592LL); break;
        }
        addr_416500101 += strd_416500101;

        //Small tile
        READ_4b(addr_417000101);
        switch(addr_417000101) {
            case 59278356LL : strd_417000101 = (59278360LL - 59278356LL); break;
            case 67145740LL : strd_417000101 = (50368528LL - 67145740LL); break;
            case 50368528LL : strd_417000101 = (50368532LL - 50368528LL); break;
        }
        addr_417000101 += strd_417000101;

        //Small tile
        READ_4b(addr_417300101);
        switch(addr_417300101) {
            case 33587216LL : strd_417300101 = (33587220LL - 33587216LL); break;
            case 42497044LL : strd_417300101 = (42497048LL - 42497044LL); break;
            case 50364428LL : strd_417300101 = (33587216LL - 50364428LL); break;
        }
        addr_417300101 += strd_417300101;

        //Small tile
        READ_4b(addr_417600101);
        switch(addr_417600101) {
            case 25715732LL : strd_417600101 = (25715736LL - 25715732LL); break;
            case 33583116LL : strd_417600101 = (16805904LL - 33583116LL); break;
            case 16805904LL : strd_417600101 = (16805908LL - 16805904LL); break;
        }
        addr_417600101 += strd_417600101;

        //Small tile
        READ_4b(addr_417900101);
        switch(addr_417900101) {
            case 8934420LL : strd_417900101 = (8934424LL - 8934420LL); break;
            case 16801804LL : strd_417900101 = (24592LL - 16801804LL); break;
            case 24592LL : strd_417900101 = (24596LL - 24592LL); break;
        }
        addr_417900101 += strd_417900101;

        //Small tile
        WRITE_4b(addr_420500101);
        switch(addr_420500101) {
            case 76059668LL : strd_420500101 = (76059672LL - 76059668LL); break;
            case 83927052LL : strd_420500101 = (67149840LL - 83927052LL); break;
            case 67149840LL : strd_420500101 = (67149844LL - 67149840LL); break;
        }
        addr_420500101 += strd_420500101;

        //Small tile
        READ_4b(addr_420800101);
        switch(addr_420800101) {
            case 76059668LL : strd_420800101 = (76059672LL - 76059668LL); break;
            case 83927052LL : strd_420800101 = (67149840LL - 83927052LL); break;
            case 67149840LL : strd_420800101 = (67149844LL - 67149840LL); break;
        }
        addr_420800101 += strd_420800101;

        //Small tile
        READ_4b(addr_421400101);
        switch(addr_421400101) {
            case 76059668LL : strd_421400101 = (76059672LL - 76059668LL); break;
            case 83927052LL : strd_421400101 = (67149840LL - 83927052LL); break;
            case 67149840LL : strd_421400101 = (67149844LL - 67149840LL); break;
        }
        addr_421400101 += strd_421400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_55 = 0;
        out_55++;
        if (out_55 <= 1966846LL) goto block45;
        else if (out_55 <= 1966847LL) goto block66;
        else goto block45;


block66:
        for(uint64_t loop2 = 0; loop2 < 4194304ULL; loop2++){
            //Loop Indexed
            addr = 67149840LL + (4 * loop2);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_424200101);
            switch(addr_424200101) {
                case 67158032LL : strd_424200101 = (67158036LL - 67158032LL); break;
                case 83927052LL : strd_424200101 = (83918864LL - 83927052LL); break;
                case 83918864LL : strd_424200101 = (83918868LL - 83918864LL); break;
            }
            addr_424200101 += strd_424200101;

            //Loop Indexed
            addr = 67149840LL + (4 * loop2);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_425200101);
            switch(addr_425200101) {
                case 21196LL : strd_425200101 = (13008LL - 21196LL); break;
                case 13008LL : strd_425200101 = (13012LL - 13008LL); break;
            }
            addr_425200101 += strd_425200101;

            //Dominant stride
            READ_4b(addr_425400101);
            addr_425400101 += 4LL;
            if(addr_425400101 >= 83927056LL) addr_425400101 = 67149844LL;

            //Loop Indexed
            addr = 50368528LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 33587216LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 16805904LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 24592LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 83931152LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 83931152LL + (4 * loop2);
            WRITE_4b(addr);

        }
        goto block45;

block67:
        int dummy;
    }

    // Interval: 1000000000 - 1402892999
    {
        int64_t addr_416200101 = 405024LL;
        int64_t addr_415900101 = 17186336LL;
        int64_t addr_416500101 = 405024LL;
        int64_t addr_417000101 = 50748960LL;
        int64_t addr_417300101 = 33967648LL;
        int64_t addr_417600101 = 17186336LL;
        int64_t addr_417900101 = 405024LL;
        int64_t addr_420500101 = 67530272LL;
        int64_t addr_420800101 = 67530272LL;
        int64_t addr_421400101 = 67530272LL;
        int64_t addr_413000101 = 17186340LL;
        int64_t addr_412600101 = 84311584LL;
        int64_t addr_412400101 = 4308LL, strd_412400101 = 0;
        int64_t addr_411900101 = 33967652LL;
        int64_t addr_411500101 = 84319780LL;
        int64_t addr_410800101 = 50748964LL;
        int64_t addr_410400101 = 84303396LL;
        int64_t addr_409600101 = 84311588LL;
        int64_t addr_415600101 = 17186340LL;
        int64_t addr_415300101 = 33967652LL;
        int64_t addr_415000101 = 33967652LL;
        int64_t addr_414700101 = 50748964LL;
        int64_t addr_414400101 = 50748964LL;
        int64_t addr_414100101 = 405028LL;
        int64_t addr_413700101 = 84311592LL;
block68:
        goto block86;

block86:
        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (17186340LL - 17186336LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (405028LL - 405024LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (405028LL - 405024LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (50748964LL - 50748960LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (33967652LL - 33967648LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (17186340LL - 17186336LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (405028LL - 405024LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (67530276LL - 67530272LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (67530276LL - 67530272LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (67530276LL - 67530272LL);

        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (84311592LL - 84311588LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (84303400LL - 84303396LL);

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (50748968LL - 50748964LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (84319784LL - 84319780LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (33967656LL - 33967652LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 4308LL : strd_412400101 = (4312LL - 4308LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 97021744LL) addr_412600101 = 84311584LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (17186344LL - 17186340LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_86 = 0;
        out_86++;
        if (out_86 <= 3177539LL) goto block93;
        else goto block94;


block93:
        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 97021748LL) addr_413700101 = 84311592LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (405032LL - 405028LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (50748968LL - 50748964LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (50748968LL - 50748964LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (33967656LL - 33967652LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (33967656LL - 33967652LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (17186344LL - 17186340LL);

        goto block86;

block94:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
