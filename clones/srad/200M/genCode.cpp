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

    // Interval: 0 - 200000000
    {
        int64_t addr_399500101 = 117494224LL, strd_399500101 = 0;
        int64_t addr_399400101 = 117494224LL, strd_399400101 = 0;
        int64_t addr_399300101 = 117494212LL, strd_399300101 = 0;
        int64_t addr_401700101 = 100712464LL;
        int64_t addr_403400101 = 83931152LL;
block0:
        goto block4;

block7:
        //Random
        addr = (bounded_rnd(117499104LL - 117498848LL) + 117498848LL) & ~7ULL;
        READ_8b(addr);

        //Small tile
        WRITE_4b(addr_403400101);
        addr_403400101 += (83931156LL - 83931152LL);

        goto block5;

block5:
        //Small tile
        READ_4b(addr_401700101);
        addr_401700101 += (100712468LL - 100712464LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_5 = 0;
        out_5++;
        if (out_5 <= 3403834LL) goto block7;
        else goto block8;


block4:
        for(uint64_t loop0 = 0; loop0 < 4194304ULL; loop0++){
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
            addr = 100712464LL + (4 * loop0);
            WRITE_4b(addr);

        }
        goto block5;

block8:
        int dummy;
    }

    // Interval: 200000000 - 400000000
    {
        int64_t addr_409600101 = 83931152LL;
        int64_t addr_410400101 = 83931152LL, strd_410400101 = 0;
        int64_t addr_420500101 = 67149840LL;
        int64_t addr_417900101 = 24592LL;
        int64_t addr_417600101 = 16805904LL;
        int64_t addr_417300101 = 33587216LL;
        int64_t addr_417000101 = 50368528LL;
        int64_t addr_416500101 = 24592LL;
        int64_t addr_416200101 = 24592LL;
        int64_t addr_415900101 = 16805904LL;
        int64_t addr_415600101 = 16805904LL;
        int64_t addr_415300101 = 33587216LL;
        int64_t addr_415000101 = 33587216LL;
        int64_t addr_414700101 = 50368528LL;
        int64_t addr_414400101 = 50368528LL;
        int64_t addr_414100101 = 24592LL;
        int64_t addr_413700101 = 83931156LL;
        int64_t addr_413500101 = 13008LL, strd_413500101 = 0;
        int64_t addr_413000101 = 16805904LL;
        int64_t addr_412600101 = 83931152LL;
        int64_t addr_412400101 = 704LL, strd_412400101 = 0;
        int64_t addr_411900101 = 33587216LL;
        int64_t addr_411500101 = 83939344LL;
        int64_t addr_410800101 = 50368528LL;
        int64_t addr_420800101 = 67149840LL;
block9:
        goto block10;

block35:
        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (50368532LL - 50368528LL);

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
        if(addr_412600101 >= 89678760LL) addr_412600101 = 83931152LL;

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
        if(addr_413700101 >= 89678768LL) addr_413700101 = 83931156LL;

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

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (67149844LL - 67149840LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (67149844LL - 67149840LL);

        goto block12;

block10:
        for(uint64_t loop1 = 0; loop1 < 790470ULL; loop1++){
            //Random
            addr = (bounded_rnd(117499104LL - 117498848LL) + 117498848LL) & ~7ULL;
            READ_8b(addr);

        }
        goto block12;

block12:
        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (83931156LL - 83931152LL);

        //Small tile
        READ_4b(addr_410400101);
        switch(addr_410400101) {
            case 83939340LL : strd_410400101 = (83931152LL - 83939340LL); break;
            case 83931152LL : strd_410400101 = (83931156LL - 83931152LL); break;
        }
        addr_410400101 += strd_410400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_12 = 0;
        out_12++;
        if (out_12 <= 1436903LL) goto block35;
        else goto block36;


block36:
        int dummy;
    }

    // Interval: 400000000 - 600000000
    {
        int64_t addr_416500101 = 5772204LL;
        int64_t addr_416200101 = 5772204LL;
        int64_t addr_415900101 = 22553516LL;
        int64_t addr_415600101 = 22553516LL;
        int64_t addr_415300101 = 39334828LL;
        int64_t addr_415000101 = 39334828LL;
        int64_t addr_414700101 = 56116140LL;
        int64_t addr_414400101 = 56116140LL;
        int64_t addr_414100101 = 5772204LL;
        int64_t addr_413700101 = 89678768LL;
        int64_t addr_413500101 = 18028LL, strd_413500101 = 0;
        int64_t addr_413000101 = 22553516LL;
        int64_t addr_412600101 = 89678760LL;
        int64_t addr_412400101 = 5724LL, strd_412400101 = 0;
        int64_t addr_411900101 = 39334828LL;
        int64_t addr_411500101 = 89686956LL;
        int64_t addr_410800101 = 56116140LL;
        int64_t addr_420500101 = 72897452LL;
        int64_t addr_417900101 = 5772204LL;
        int64_t addr_420800101 = 72897452LL;
        int64_t addr_421400101 = 72897452LL;
        int64_t addr_417600101 = 22553516LL;
        int64_t addr_417300101 = 39334828LL;
        int64_t addr_417000101 = 56116140LL;
        int64_t addr_410400101 = 89670576LL;
block37:
        goto block54;

block54:
        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (56116144LL - 56116140LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (89686960LL - 89686956LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (39334832LL - 39334828LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
            case 5724LL : strd_412400101 = (5728LL - 5724LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 96003204LL) addr_412600101 = 89678760LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (22553520LL - 22553516LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
            case 18028LL : strd_413500101 = (18032LL - 18028LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 96003212LL) addr_413700101 = 89678768LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (5772208LL - 5772204LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (56116144LL - 56116140LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (56116144LL - 56116140LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (39334832LL - 39334828LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (39334832LL - 39334828LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (22553520LL - 22553516LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (22553520LL - 22553516LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (5772208LL - 5772204LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (5772208LL - 5772204LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_54 = 0;
        out_54++;
        if (out_54 <= 1581110LL) goto block62;
        else goto block63;


block62:
        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (56116144LL - 56116140LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (39334832LL - 39334828LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (22553520LL - 22553516LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (5772208LL - 5772204LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (72897456LL - 72897452LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (72897456LL - 72897452LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (72897456LL - 72897452LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (89670580LL - 89670576LL);

        goto block54;

block63:
        int dummy;
    }

    // Interval: 600000000 - 800000000
    {
        int64_t addr_421400101 = 79221892LL;
        int64_t addr_420800101 = 79221892LL;
        int64_t addr_420500101 = 79221892LL;
        int64_t addr_417900101 = 12096644LL;
        int64_t addr_417600101 = 28877956LL;
        int64_t addr_417300101 = 45659268LL;
        int64_t addr_417000101 = 62440580LL;
        int64_t addr_416500101 = 12096648LL;
        int64_t addr_416200101 = 12096648LL;
        int64_t addr_415900101 = 28877960LL;
        int64_t addr_415600101 = 28877960LL;
        int64_t addr_415300101 = 45659272LL;
        int64_t addr_415000101 = 45659272LL;
        int64_t addr_409600101 = 96003208LL;
        int64_t addr_410400101 = 95995016LL;
        int64_t addr_410800101 = 62440584LL;
        int64_t addr_411500101 = 96011400LL, strd_411500101 = 0;
        int64_t addr_411900101 = 45659272LL;
        int64_t addr_412400101 = 5944LL, strd_412400101 = 0;
        int64_t addr_412600101 = 96003204LL;
        int64_t addr_413000101 = 28877960LL;
        int64_t addr_413500101 = 18248LL, strd_413500101 = 0;
        int64_t addr_413700101 = 96003212LL;
        int64_t addr_414100101 = 12096648LL;
        int64_t addr_414400101 = 62440584LL;
        int64_t addr_414700101 = 62440584LL;
        int64_t addr_423400101 = 67149840LL;
        int64_t addr_428100101 = 83931152LL;
        int64_t addr_427500101 = 83931152LL;
        int64_t addr_427000101 = 24592LL;
        int64_t addr_426600101 = 16805904LL;
        int64_t addr_426200101 = 33587216LL;
        int64_t addr_425800101 = 50368528LL;
        int64_t addr_425400101 = 67149844LL;
block64:
        goto block71;

block71:
        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (62440584LL - 62440580LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (45659272LL - 45659268LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (28877960LL - 28877956LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (12096648LL - 12096644LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (79221896LL - 79221892LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (79221896LL - 79221892LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (79221896LL - 79221892LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_71 = 0;
        out_71++;
        if (out_71 <= 1176290LL) goto block90;
        else goto block91;


block91:
        //Small tile
        READ_4b(addr_423400101);
        addr_423400101 += (67149844LL - 67149840LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_91 = 0;
        out_91++;
        if (out_91 <= 898381LL) goto block98;
        else goto block99;


block90:
        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (96003212LL - 96003208LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (95995020LL - 95995016LL);

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (62440588LL - 62440584LL);

        //Small tile
        READ_4b(addr_411500101);
        switch(addr_411500101) {
            case 100708364LL : strd_411500101 = (100700176LL - 100708364LL); break;
            case 96011400LL : strd_411500101 = (96011404LL - 96011400LL); break;
            case 100700176LL : strd_411500101 = (100700180LL - 100700176LL); break;
        }
        addr_411500101 += strd_411500101;

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (45659276LL - 45659272LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 5944LL : strd_412400101 = (5948LL - 5944LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 100708364LL) addr_412600101 = 96003204LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (28877964LL - 28877960LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 18248LL : strd_413500101 = (18252LL - 18248LL); break;
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 100708368LL) addr_413700101 = 96003212LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (12096652LL - 12096648LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (62440588LL - 62440584LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (62440588LL - 62440584LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (45659276LL - 45659272LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (45659276LL - 45659272LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (28877964LL - 28877960LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (28877964LL - 28877960LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (12096652LL - 12096648LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (12096652LL - 12096648LL);

        goto block71;

block98:
        //Dominant stride
        READ_4b(addr_425400101);
        addr_425400101 += 4LL;
        if(addr_425400101 >= 70743368LL) addr_425400101 = 67149844LL;

        //Small tile
        READ_4b(addr_425800101);
        addr_425800101 += (50368532LL - 50368528LL);

        //Small tile
        READ_4b(addr_426200101);
        addr_426200101 += (33587220LL - 33587216LL);

        //Small tile
        READ_4b(addr_426600101);
        addr_426600101 += (16805908LL - 16805904LL);

        //Small tile
        READ_4b(addr_427000101);
        addr_427000101 += (24596LL - 24592LL);

        //Small tile
        READ_4b(addr_427500101);
        addr_427500101 += (83931156LL - 83931152LL);

        //Small tile
        WRITE_4b(addr_428100101);
        addr_428100101 += (83931156LL - 83931152LL);

        goto block91;

block99:
        int dummy;
    }

    // Interval: 800000000 - 1000000000
    {
        int64_t addr_428100101 = 87524676LL;
        int64_t addr_424200101 = 70751556LL, strd_424200101 = 0;
        int64_t addr_424600101 = 70743364LL;
        int64_t addr_425200101 = 18436LL, strd_425200101 = 0;
        int64_t addr_425400101 = 70743368LL;
        int64_t addr_425800101 = 53962052LL;
        int64_t addr_426200101 = 37180740LL;
        int64_t addr_426600101 = 20399428LL;
        int64_t addr_427000101 = 3618116LL;
        int64_t addr_427500101 = 87524676LL;
        int64_t addr_423400101 = 70743368LL;
block100:
        goto block110;

block110:
        //Small tile
        READ_4b(addr_424200101);
        switch(addr_424200101) {
            case 83927052LL : strd_424200101 = (83918864LL - 83927052LL); break;
            case 70751556LL : strd_424200101 = (70751560LL - 70751556LL); break;
            case 83918864LL : strd_424200101 = (83918868LL - 83918864LL); break;
        }
        addr_424200101 += strd_424200101;

        //Small tile
        READ_4b(addr_424600101);
        addr_424600101 += (70743368LL - 70743364LL);

        //Small tile
        READ_4b(addr_425200101);
        switch(addr_425200101) {
            case 21196LL : strd_425200101 = (13008LL - 21196LL); break;
            case 13008LL : strd_425200101 = (13012LL - 13008LL); break;
            case 18436LL : strd_425200101 = (18440LL - 18436LL); break;
        }
        addr_425200101 += strd_425200101;

        //Dominant stride
        READ_4b(addr_425400101);
        addr_425400101 += 4LL;
        if(addr_425400101 >= 83927056LL) addr_425400101 = 70743368LL;

        //Small tile
        READ_4b(addr_425800101);
        addr_425800101 += (53962056LL - 53962052LL);

        //Small tile
        READ_4b(addr_426200101);
        addr_426200101 += (37180744LL - 37180740LL);

        //Small tile
        READ_4b(addr_426600101);
        addr_426600101 += (20399432LL - 20399428LL);

        //Small tile
        READ_4b(addr_427000101);
        addr_427000101 += (3618120LL - 3618116LL);

        //Small tile
        READ_4b(addr_427500101);
        addr_427500101 += (87524680LL - 87524676LL);

        //Small tile
        WRITE_4b(addr_428100101);
        addr_428100101 += (87524680LL - 87524676LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_110 = 0;
        out_110++;
        if (out_110 <= 3295922LL) goto block111;
        else goto block112;


block111:
        //Small tile
        READ_4b(addr_423400101);
        addr_423400101 += (70743372LL - 70743368LL);

        goto block110;

block112:
        int dummy;
    }

    // Interval: 1000000000 - 1200000000
    {
        int64_t addr_417900101 = 405024LL;
        int64_t addr_417600101 = 17186336LL;
        int64_t addr_417300101 = 33967648LL;
        int64_t addr_417000101 = 50748960LL;
        int64_t addr_416500101 = 405024LL;
        int64_t addr_416200101 = 405024LL;
        int64_t addr_415900101 = 17186336LL;
        int64_t addr_421400101 = 67530272LL;
        int64_t addr_420800101 = 67530272LL;
        int64_t addr_420500101 = 67530272LL;
        int64_t addr_415600101 = 17186340LL;
        int64_t addr_415300101 = 33967652LL;
        int64_t addr_415000101 = 33967652LL;
        int64_t addr_414700101 = 50748964LL;
        int64_t addr_414400101 = 50748964LL;
        int64_t addr_414100101 = 405028LL;
        int64_t addr_413700101 = 84311592LL;
        int64_t addr_413500101 = 16612LL, strd_413500101 = 0;
        int64_t addr_413000101 = 17186340LL;
        int64_t addr_412600101 = 84311584LL;
        int64_t addr_412400101 = 4308LL, strd_412400101 = 0;
        int64_t addr_411900101 = 33967652LL;
        int64_t addr_411500101 = 84319780LL;
        int64_t addr_410800101 = 50748964LL;
        int64_t addr_410400101 = 84303396LL;
block113:
        goto block120;

block138:
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
        if(addr_412600101 >= 90621016LL) addr_412600101 = 84311584LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (17186344LL - 17186340LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 16612LL : strd_413500101 = (16616LL - 16612LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 90621024LL) addr_413700101 = 84311592LL;

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

        goto block120;

block120:
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

        //Few edges. Don't bother optimizing
        static uint64_t out_120 = 0;
        out_120++;
        if (out_120 <= 1577358LL) goto block138;
        else goto block139;


block139:
        int dummy;
    }

    // Interval: 1200000000 - 1400000000
    {
        int64_t addr_409600101 = 90621020LL;
        int64_t addr_421400101 = 73839704LL;
        int64_t addr_420800101 = 73839704LL;
        int64_t addr_420500101 = 73839704LL;
        int64_t addr_417900101 = 6714460LL;
        int64_t addr_417600101 = 23495772LL;
        int64_t addr_417300101 = 40277084LL;
        int64_t addr_417000101 = 57058396LL;
        int64_t addr_416500101 = 6714460LL;
        int64_t addr_416200101 = 6714460LL;
        int64_t addr_415900101 = 23495772LL;
        int64_t addr_415600101 = 23495772LL;
        int64_t addr_415300101 = 40277084LL;
        int64_t addr_415000101 = 40277084LL;
        int64_t addr_414700101 = 57058396LL;
        int64_t addr_414400101 = 57058396LL;
        int64_t addr_414100101 = 6714460LL;
        int64_t addr_413700101 = 90621024LL;
        int64_t addr_413500101 = 18204LL, strd_413500101 = 0;
        int64_t addr_413000101 = 23495772LL;
        int64_t addr_412600101 = 90621016LL;
        int64_t addr_412400101 = 5900LL, strd_412400101 = 0;
        int64_t addr_411900101 = 40277084LL;
        int64_t addr_411500101 = 90629212LL;
        int64_t addr_410800101 = 57058396LL;
block140:
        goto block144;

block165:
        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (57058400LL - 57058396LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (90629216LL - 90629212LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (40277088LL - 40277084LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
            case 5900LL : strd_412400101 = (5904LL - 5900LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 96930476LL) addr_412600101 = 90621016LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (23495776LL - 23495772LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
            case 18204LL : strd_413500101 = (18208LL - 18204LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 96930484LL) addr_413700101 = 90621024LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (6714464LL - 6714460LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (57058400LL - 57058396LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (57058400LL - 57058396LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (40277088LL - 40277084LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (40277088LL - 40277084LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (23495776LL - 23495772LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (23495776LL - 23495772LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (6714464LL - 6714460LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (6714464LL - 6714460LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (57058400LL - 57058396LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (40277088LL - 40277084LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (23495776LL - 23495772LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (6714464LL - 6714460LL);

        goto block144;

block144:
        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (73839708LL - 73839704LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (73839708LL - 73839704LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (73839708LL - 73839704LL);

        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (90621024LL - 90621020LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_144 = 0;
        out_144++;
        if (out_144 <= 1577365LL) goto block165;
        else goto block166;


block166:
        int dummy;
    }

    // Interval: 1400000000 - 1402893039
    {
        int64_t addr_417300101 = 46586544LL;
        int64_t addr_417000101 = 63367856LL;
        int64_t addr_416500101 = 13023920LL;
        int64_t addr_416200101 = 13023920LL;
        int64_t addr_415900101 = 29805232LL;
        int64_t addr_415600101 = 29805232LL;
        int64_t addr_415300101 = 46586544LL;
        int64_t addr_415000101 = 46586544LL;
        int64_t addr_414700101 = 63367856LL;
        int64_t addr_414400101 = 63367856LL;
        int64_t addr_414100101 = 13023920LL;
        int64_t addr_413700101 = 96930484LL;
        int64_t addr_413500101 = 19824LL, strd_413500101 = 0;
        int64_t addr_413000101 = 29805232LL;
        int64_t addr_412600101 = 96930476LL;
        int64_t addr_412400101 = 7520LL, strd_412400101 = 0;
        int64_t addr_411900101 = 46586544LL;
        int64_t addr_411500101 = 96938672LL;
        int64_t addr_410800101 = 63367856LL;
        int64_t addr_410400101 = 96922288LL;
        int64_t addr_420500101 = 80149168LL;
        int64_t addr_420800101 = 80149168LL;
        int64_t addr_421400101 = 80149168LL;
        int64_t addr_417900101 = 13023920LL;
        int64_t addr_417600101 = 29805232LL;
block167:
        goto block187;

block187:
        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (96922292LL - 96922288LL);

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (63367860LL - 63367856LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (96938676LL - 96938672LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (46586548LL - 46586544LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 7520LL : strd_412400101 = (7524LL - 7520LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 97021744LL) addr_412600101 = 96930476LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (29805236LL - 29805232LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 19824LL : strd_413500101 = (19828LL - 19824LL); break;
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 97021752LL) addr_413700101 = 96930484LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (13023924LL - 13023920LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (63367860LL - 63367856LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (63367860LL - 63367856LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (46586548LL - 46586544LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (46586548LL - 46586544LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (29805236LL - 29805232LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (29805236LL - 29805232LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (13023924LL - 13023920LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (13023924LL - 13023920LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (63367860LL - 63367856LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (46586548LL - 46586544LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_187 = 0;
        out_187++;
        if (out_187 <= 22816LL) goto block192;
        else goto block193;


block192:
        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (29805236LL - 29805232LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (13023924LL - 13023920LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (80149172LL - 80149168LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (80149172LL - 80149168LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (80149172LL - 80149168LL);

        goto block187;

block193:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
