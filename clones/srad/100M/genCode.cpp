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

    // Interval: 0 - 100000000
    {
        int64_t addr_399300101 = 117494212LL, strd_399300101 = 0;
        int64_t addr_399400101 = 117494224LL, strd_399400101 = 0;
        int64_t addr_399500101 = 117494224LL, strd_399500101 = 0;
        int64_t addr_400800101 = 100712464LL;
block0:
        goto block3;

block4:
        //Small tile
        WRITE_4b(addr_400800101);
        addr_400800101 += (100712468LL - 100712464LL);

        goto block3;

block3:
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
            case 117494212LL : strd_399400101 = (117494216LL - 117494212LL); break;
            case 117494332LL : strd_399400101 = (117494212LL - 117494332LL); break;
            case 117494224LL : strd_399400101 = (117494228LL - 117494224LL); break;
        }
        addr_399400101 += strd_399400101;

        //Small tile
        WRITE_4b(addr_399500101);
        switch(addr_399500101) {
            case 117494212LL : strd_399500101 = (117494216LL - 117494212LL); break;
            case 117494332LL : strd_399500101 = (117494212LL - 117494332LL); break;
            case 117494224LL : strd_399500101 = (117494228LL - 117494224LL); break;
        }
        addr_399500101 += strd_399500101;

        //Few edges. Don't bother optimizing
        static uint64_t out_3 = 0;
        out_3++;
        if (out_3 <= 3445696LL) goto block4;
        else goto block5;


block5:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_401700101 = 100712464LL;
        int64_t addr_403400101 = 83931152LL;
        int64_t addr_400800101 = 114495248LL;
        int64_t addr_399300101 = 117494276LL, strd_399300101 = 0;
        int64_t addr_399400101 = 117494288LL, strd_399400101 = 0;
block6:
        goto block7;

block12:
        //Random
        addr = (bounded_rnd(117499104LL - 117498848LL) + 117498848LL) & ~7ULL;
        READ_8b(addr);

        //Small tile
        WRITE_4b(addr_403400101);
        addr_403400101 += (83931156LL - 83931152LL);

        goto block10;

block7:
        //Small tile
        WRITE_4b(addr_400800101);
        addr_400800101 += (114495252LL - 114495248LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_7 = 0;
        out_7++;
        if (out_7 <= 748607LL) goto block9;
        else goto block10;


block9:
        //Small tile
        READ_4b(addr_399300101);
        switch(addr_399300101) {
            case 117494212LL : strd_399300101 = (117494216LL - 117494212LL); break;
            case 117494276LL : strd_399300101 = (117494280LL - 117494276LL); break;
            case 117494332LL : strd_399300101 = (117494212LL - 117494332LL); break;
        }
        addr_399300101 += strd_399300101;

        //Small tile
        READ_4b(addr_399400101);
        switch(addr_399400101) {
            case 117494288LL : strd_399400101 = (117494292LL - 117494288LL); break;
            case 117494212LL : strd_399400101 = (117494216LL - 117494212LL); break;
            case 117494332LL : strd_399400101 = (117494212LL - 117494332LL); break;
        }
        addr_399400101 += strd_399400101;

        goto block7;

block10:
        //Small tile
        READ_4b(addr_401700101);
        addr_401700101 += (100712468LL - 100712464LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_10 = 0;
        out_10++;
        if (out_10 <= 3403834LL) goto block12;
        else goto block13;


block13:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_403400101 = 97546488LL;
        int64_t addr_401700101 = 114327804LL;
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
        int64_t addr_410400101 = 83931152LL, strd_410400101 = 0;
        int64_t addr_409600101 = 83931152LL;
        int64_t addr_420500101 = 67149840LL;
block14:
        goto block16;

block40:
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
        if(addr_412600101 >= 86516488LL) addr_412600101 = 83931152LL;

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
        if(addr_413700101 >= 86516496LL) addr_413700101 = 83931156LL;

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

        //Few edges. Don't bother optimizing
        static uint64_t out_40 = 0;
        out_40++;
        if (out_40 <= 646334LL) goto block41;
        else goto block42;


block41:
        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (67149844LL - 67149840LL);

        goto block40;

block17:
        //Small tile
        READ_4b(addr_401700101);
        addr_401700101 += (114327808LL - 114327804LL);

        goto block16;

block16:
        //Random
        addr = (bounded_rnd(117499104LL - 117498848LL) + 117498848LL) & ~7ULL;
        READ_8b(addr);

        //Small tile
        WRITE_4b(addr_403400101);
        addr_403400101 += (97546492LL - 97546488LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_16 = 0;
        out_16++;
        if (out_16 <= 790469LL) goto block17;
        else goto block40;


block42:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_409600101 = 86516492LL;
        int64_t addr_410400101 = 86508300LL;
        int64_t addr_421400101 = 69735176LL;
        int64_t addr_420800101 = 69735176LL;
        int64_t addr_420500101 = 69735176LL;
        int64_t addr_417900101 = 2609932LL;
        int64_t addr_417600101 = 19391244LL;
        int64_t addr_417300101 = 36172556LL;
        int64_t addr_417000101 = 52953868LL;
        int64_t addr_416500101 = 2609932LL;
        int64_t addr_416200101 = 2609932LL;
        int64_t addr_415900101 = 19391244LL;
        int64_t addr_415600101 = 19391244LL;
        int64_t addr_415300101 = 36172556LL;
        int64_t addr_415000101 = 36172556LL;
        int64_t addr_414700101 = 52953868LL;
        int64_t addr_414400101 = 52953868LL;
        int64_t addr_414100101 = 2609932LL;
        int64_t addr_413700101 = 86516496LL;
        int64_t addr_413500101 = 17868LL, strd_413500101 = 0;
        int64_t addr_413000101 = 19391244LL;
        int64_t addr_412600101 = 86516488LL;
        int64_t addr_412400101 = 5564LL, strd_412400101 = 0;
        int64_t addr_411900101 = 36172556LL;
        int64_t addr_411500101 = 86524684LL;
block43:
        goto block48;

block48:
        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (69735180LL - 69735176LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (69735180LL - 69735176LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (69735180LL - 69735176LL);

        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (86516496LL - 86516492LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (86508304LL - 86508300LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_48 = 0;
        out_48++;
        if (out_48 <= 790568LL) goto block68;
        else goto block69;


block68:
        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (86524688LL - 86524684LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (36172560LL - 36172556LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 5564LL : strd_412400101 = (5568LL - 5564LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 89678760LL) addr_412600101 = 86516488LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (19391248LL - 19391244LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 17868LL : strd_413500101 = (17872LL - 17868LL); break;
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 89678768LL) addr_413700101 = 86516496LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (2609936LL - 2609932LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (52953872LL - 52953868LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (52953872LL - 52953868LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (36172560LL - 36172556LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (36172560LL - 36172556LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (19391248LL - 19391244LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (19391248LL - 19391244LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (2609936LL - 2609932LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (2609936LL - 2609932LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (52953872LL - 52953868LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (36172560LL - 36172556LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (19391248LL - 19391244LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (2609936LL - 2609932LL);

        goto block48;

block69:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_410800101 = 56116140LL;
        int64_t addr_421400101 = 72897452LL;
        int64_t addr_420800101 = 72897452LL;
        int64_t addr_420500101 = 72897452LL;
        int64_t addr_417900101 = 5772204LL;
        int64_t addr_417600101 = 22553516LL;
        int64_t addr_417300101 = 39334828LL;
        int64_t addr_417000101 = 56116140LL;
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
        int64_t addr_410400101 = 89670576LL;
block70:
        goto block71;

block95:
        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (89686960LL - 89686956LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (39334832LL - 39334828LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 5724LL : strd_412400101 = (5728LL - 5724LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 92840976LL) addr_412600101 = 89678760LL;

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
        if(addr_413700101 >= 92840984LL) addr_413700101 = 89678768LL;

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

        goto block71;

block71:
        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (56116144LL - 56116140LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_71 = 0;
        out_71++;
        if (out_71 <= 790554LL) goto block95;
        else goto block96;


block96:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_416200101 = 8934420LL;
        int64_t addr_415900101 = 25715732LL;
        int64_t addr_415600101 = 25715732LL;
        int64_t addr_415300101 = 42497044LL;
        int64_t addr_415000101 = 42497044LL;
        int64_t addr_414700101 = 59278356LL;
        int64_t addr_414400101 = 59278356LL;
        int64_t addr_414100101 = 8934420LL;
        int64_t addr_413700101 = 92840984LL;
        int64_t addr_413500101 = 18132LL, strd_413500101 = 0;
        int64_t addr_413000101 = 25715732LL;
        int64_t addr_412600101 = 92840976LL;
        int64_t addr_412400101 = 5828LL, strd_412400101 = 0;
        int64_t addr_411900101 = 42497044LL;
        int64_t addr_411500101 = 92849172LL;
        int64_t addr_416500101 = 8934420LL;
        int64_t addr_417900101 = 8934420LL;
        int64_t addr_417600101 = 25715732LL;
        int64_t addr_420500101 = 76059668LL;
        int64_t addr_420800101 = 76059668LL;
        int64_t addr_421400101 = 76059668LL;
        int64_t addr_417300101 = 42497044LL;
        int64_t addr_417000101 = 59278356LL;
        int64_t addr_410800101 = 59278360LL;
        int64_t addr_410400101 = 92832792LL;
block97:
        goto block113;

block113:
        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (92849176LL - 92849172LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (42497048LL - 42497044LL);

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
        if(addr_412600101 >= 96003204LL) addr_412600101 = 92840976LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (25715736LL - 25715732LL);

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
        if(addr_413700101 >= 96003212LL) addr_413700101 = 92840984LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (8934424LL - 8934420LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (59278360LL - 59278356LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (59278360LL - 59278356LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (42497048LL - 42497044LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (42497048LL - 42497044LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (25715736LL - 25715732LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (25715736LL - 25715732LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (8934424LL - 8934420LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (8934424LL - 8934420LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_113 = 0;
        out_113++;
        if (out_113 <= 790556LL) goto block122;
        else goto block123;


block122:
        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (59278360LL - 59278356LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (42497048LL - 42497044LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (25715736LL - 25715732LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (8934424LL - 8934420LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (76059672LL - 76059668LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (76059672LL - 76059668LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (76059672LL - 76059668LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (92832796LL - 92832792LL);

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (59278364LL - 59278360LL);

        goto block113;

block123:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_409600101 = 96003208LL;
        int64_t addr_410400101 = 95995016LL;
        int64_t addr_410800101 = 62440584LL;
        int64_t addr_411500101 = 96011400LL;
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
        int64_t addr_414700101 = 62440584LL;
        int64_t addr_414400101 = 62440584LL;
        int64_t addr_414100101 = 12096648LL;
        int64_t addr_413700101 = 96003212LL;
        int64_t addr_413500101 = 18248LL, strd_413500101 = 0;
        int64_t addr_413000101 = 28877960LL;
        int64_t addr_412600101 = 96003204LL;
        int64_t addr_412400101 = 5944LL, strd_412400101 = 0;
block124:
        goto block135;

block135:
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
        addr_411500101 += (96011404LL - 96011400LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_135 = 0;
        out_135++;
        if (out_135 <= 790577LL) goto block149;
        else goto block150;


block149:
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
        if(addr_412600101 >= 99165512LL) addr_412600101 = 96003204LL;

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
        if(addr_413700101 >= 99165520LL) addr_413700101 = 96003212LL;

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

        goto block135;

block150:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_423400101 = 67149840LL;
        int64_t addr_424200101 = 67158032LL;
        int64_t addr_424600101 = 67149840LL;
        int64_t addr_425200101 = 13008LL, strd_425200101 = 0;
        int64_t addr_425400101 = 67149844LL;
        int64_t addr_425800101 = 50368528LL;
        int64_t addr_426200101 = 33587216LL;
        int64_t addr_426600101 = 16805904LL;
        int64_t addr_427000101 = 24592LL;
        int64_t addr_427500101 = 83931152LL;
        int64_t addr_428100101 = 83931152LL;
        int64_t addr_412400101 = 6140LL, strd_412400101 = 0;
        int64_t addr_412600101 = 99165512LL;
        int64_t addr_413500101 = 18444LL, strd_413500101 = 0;
        int64_t addr_413700101 = 99165520LL;
block151:
        goto block173;

block174:
        //Small tile
        READ_4b(addr_423400101);
        addr_423400101 += (67149844LL - 67149840LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_174 = 0;
        out_174++;
        if (out_174 <= 898381LL) goto block184;
        else goto block185;


block173:
        for(uint64_t loop0 = 0; loop0 < 385713ULL; loop0++){
            //Loop Indexed
            addr = 48821580LL + (4 * loop0);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_412400101);
            switch(addr_412400101) {
                case 6140LL : strd_412400101 = (6144LL - 6140LL); break;
                case 8892LL : strd_412400101 = (704LL - 8892LL); break;
                case 704LL : strd_412400101 = (708LL - 704LL); break;
            }
            addr_412400101 += strd_412400101;

            //Dominant stride
            READ_4b(addr_412600101);
            addr_412600101 += 4LL;
            if(addr_412600101 >= 100708364LL) addr_412600101 = 99165512LL;

            //Loop Indexed
            addr = 32040268LL + (4 * loop0);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_413500101);
            switch(addr_413500101) {
                case 18444LL : strd_413500101 = (18448LL - 18444LL); break;
                case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
                case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
            }
            addr_413500101 += strd_413500101;

            //Dominant stride
            READ_4b(addr_413700101);
            addr_413700101 += 4LL;
            if(addr_413700101 >= 100708368LL) addr_413700101 = 99165520LL;

            //Loop Indexed
            addr = 15258956LL + (4 * loop0);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 65602892LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 65602892LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 48821580LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 48821580LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 32040268LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 32040268LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 15258956LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 15258956LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 65602892LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 48821580LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 32040268LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 15258956LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 82384204LL + (4 * loop0);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 82384204LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 82384204LL + (4 * loop0);
            READ_4b(addr);

        }
        goto block174;

block184:
        //Small tile
        READ_4b(addr_424200101);
        addr_424200101 += (67158036LL - 67158032LL);

        //Small tile
        READ_4b(addr_424600101);
        addr_424600101 += (67149844LL - 67149840LL);

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

        goto block174;

block185:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_424200101 = 70751556LL;
        int64_t addr_424600101 = 70743364LL;
        int64_t addr_425200101 = 18436LL, strd_425200101 = 0;
        int64_t addr_425400101 = 70743368LL;
        int64_t addr_425800101 = 53962052LL;
        int64_t addr_426200101 = 37180740LL;
        int64_t addr_426600101 = 20399428LL;
        int64_t addr_427000101 = 3618116LL;
        int64_t addr_427500101 = 87524676LL;
        int64_t addr_428100101 = 87524676LL;
        int64_t addr_423400101 = 70743368LL;
block186:
        goto block196;

block196:
        //Small tile
        READ_4b(addr_424200101);
        addr_424200101 += (70751560LL - 70751556LL);

        //Small tile
        READ_4b(addr_424600101);
        addr_424600101 += (70743368LL - 70743364LL);

        //Small tile
        READ_4b(addr_425200101);
        switch(addr_425200101) {
            case 18436LL : strd_425200101 = (18440LL - 18436LL); break;
            case 21196LL : strd_425200101 = (13008LL - 21196LL); break;
            case 13008LL : strd_425200101 = (13012LL - 13008LL); break;
        }
        addr_425200101 += strd_425200101;

        //Dominant stride
        READ_4b(addr_425400101);
        addr_425400101 += 4LL;
        if(addr_425400101 >= 77760552LL) addr_425400101 = 70743368LL;

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
        static uint64_t out_196 = 0;
        out_196++;
        if (out_196 <= 1754295LL) goto block197;
        else goto block198;


block197:
        //Small tile
        READ_4b(addr_423400101);
        addr_423400101 += (70743372LL - 70743368LL);

        goto block196;

block198:
        int dummy;
    }

    // Interval: 900000000 - 1000000000
    {
        int64_t addr_424200101 = 77768740LL, strd_424200101 = 0;
        int64_t addr_425200101 = 15076LL, strd_425200101 = 0;
        int64_t addr_425400101 = 77760552LL;
        int64_t addr_410400101 = 83931152LL, strd_410400101 = 0;
        int64_t addr_412400101 = 704LL, strd_412400101 = 0;
        int64_t addr_412600101 = 83931152LL;
        int64_t addr_413500101 = 13008LL, strd_413500101 = 0;
block199:
        goto block220;

block220:
        for(uint64_t loop2 = 0; loop2 < 1541627ULL; loop2++){
            //Loop Indexed
            addr = 77760548LL + (4 * loop2);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_424200101);
            switch(addr_424200101) {
                case 83927052LL : strd_424200101 = (83918864LL - 83927052LL); break;
                case 77768740LL : strd_424200101 = (77768744LL - 77768740LL); break;
                case 83918864LL : strd_424200101 = (83918868LL - 83918864LL); break;
            }
            addr_424200101 += strd_424200101;

            //Loop Indexed
            addr = 77760548LL + (4 * loop2);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_425200101);
            switch(addr_425200101) {
                case 15076LL : strd_425200101 = (15080LL - 15076LL); break;
                case 21196LL : strd_425200101 = (13008LL - 21196LL); break;
                case 13008LL : strd_425200101 = (13012LL - 13008LL); break;
            }
            addr_425200101 += strd_425200101;

            //Dominant stride
            READ_4b(addr_425400101);
            addr_425400101 += 4LL;
            if(addr_425400101 >= 83927056LL) addr_425400101 = 77760552LL;

            //Loop Indexed
            addr = 60979236LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 44197924LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 27416612LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 10635300LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 94541860LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 94541860LL + (4 * loop2);
            WRITE_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 95109ULL; loop1++){
            //Loop Indexed
            addr = 83931152LL + (4 * loop1);
            READ_4b(addr);

            //Small tile
            READ_4b(addr_410400101);
            switch(addr_410400101) {
                case 83939340LL : strd_410400101 = (83931152LL - 83939340LL); break;
                case 83931152LL : strd_410400101 = (83931156LL - 83931152LL); break;
            }
            addr_410400101 += strd_410400101;

            //Loop Indexed
            addr = 50368528LL + (4 * loop1);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 83939344LL + (4 * loop1);
            READ_4b(addr);

            //Loop Indexed
            addr = 33587216LL + (4 * loop1);
            WRITE_4b(addr);

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
            if(addr_412600101 >= 84311584LL) addr_412600101 = 83931152LL;

            //Loop Indexed
            addr = 16805904LL + (4 * loop1);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_413500101);
            switch(addr_413500101) {
                case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
                case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
            }
            addr_413500101 += strd_413500101;

            //Loop Indexed
            addr = 16805904LL + (4 * loop1);
            READ_4b(addr);

        }
        goto block221;

block221:
        int dummy;
    }

    // Interval: 1000000000 - 1100000000
    {
        int64_t addr_417000101 = 50748960LL;
        int64_t addr_416500101 = 405024LL;
        int64_t addr_416200101 = 405024LL;
        int64_t addr_415900101 = 17186336LL;
        int64_t addr_421400101 = 67530272LL;
        int64_t addr_420800101 = 67530272LL;
        int64_t addr_420500101 = 67530272LL;
        int64_t addr_417900101 = 405024LL;
        int64_t addr_417600101 = 17186336LL;
        int64_t addr_417300101 = 33967648LL;
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
block222:
        goto block226;

block226:
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

        //Few edges. Don't bother optimizing
        static uint64_t out_226 = 0;
        out_226++;
        if (out_226 <= 788696LL) goto block247;
        else goto block248;


block247:
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
        if(addr_412600101 >= 87466368LL) addr_412600101 = 84311584LL;

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
        if(addr_413700101 >= 87466376LL) addr_413700101 = 84311592LL;

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

        goto block226;

block248:
        int dummy;
    }

    // Interval: 1100000000 - 1200000000
    {
        int64_t addr_417900101 = 3559808LL;
        int64_t addr_417600101 = 20341120LL;
        int64_t addr_417300101 = 37122432LL;
        int64_t addr_421400101 = 70685056LL;
        int64_t addr_420800101 = 70685056LL;
        int64_t addr_420500101 = 70685056LL;
        int64_t addr_417000101 = 53903748LL;
        int64_t addr_416500101 = 3559812LL;
        int64_t addr_416200101 = 3559812LL;
        int64_t addr_415900101 = 20341124LL;
        int64_t addr_415600101 = 20341124LL;
        int64_t addr_415300101 = 37122436LL;
        int64_t addr_415000101 = 37122436LL;
        int64_t addr_414700101 = 53903748LL;
        int64_t addr_414400101 = 53903748LL;
        int64_t addr_414100101 = 3559812LL;
        int64_t addr_413700101 = 87466376LL;
        int64_t addr_413500101 = 17476LL, strd_413500101 = 0;
        int64_t addr_413000101 = 20341124LL;
        int64_t addr_412600101 = 87466368LL;
        int64_t addr_412400101 = 5172LL, strd_412400101 = 0;
        int64_t addr_411900101 = 37122436LL;
        int64_t addr_411500101 = 87474564LL;
        int64_t addr_410800101 = 53903748LL;
        int64_t addr_410400101 = 87458180LL;
block249:
        goto block252;

block274:
        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (70685060LL - 70685056LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (70685060LL - 70685056LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (70685060LL - 70685056LL);

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (87458184LL - 87458180LL);

        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (53903752LL - 53903748LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (87474568LL - 87474564LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (37122440LL - 37122436LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 5172LL : strd_412400101 = (5176LL - 5172LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 90621016LL) addr_412600101 = 87466368LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (20341128LL - 20341124LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 17476LL : strd_413500101 = (17480LL - 17476LL); break;
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 90621024LL) addr_413700101 = 87466376LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (3559816LL - 3559812LL);

        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (53903752LL - 53903748LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (53903752LL - 53903748LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (37122440LL - 37122436LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (37122440LL - 37122436LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (20341128LL - 20341124LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (20341128LL - 20341124LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (3559816LL - 3559812LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (3559816LL - 3559812LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (53903752LL - 53903748LL);

        goto block252;

block252:
        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (37122436LL - 37122432LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (20341124LL - 20341120LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (3559812LL - 3559808LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_252 = 0;
        out_252++;
        if (out_252 <= 788662LL) goto block274;
        else goto block275;


block275:
        int dummy;
    }

    // Interval: 1200000000 - 1300000000
    {
        int64_t addr_420500101 = 73839704LL;
        int64_t addr_420800101 = 73839704LL;
        int64_t addr_421400101 = 73839704LL;
        int64_t addr_414100101 = 6714460LL;
        int64_t addr_413700101 = 90621024LL;
        int64_t addr_413500101 = 18204LL, strd_413500101 = 0;
        int64_t addr_413000101 = 23495772LL;
        int64_t addr_412600101 = 90621016LL;
        int64_t addr_412400101 = 5900LL, strd_412400101 = 0;
        int64_t addr_411900101 = 40277084LL;
        int64_t addr_411500101 = 90629212LL;
        int64_t addr_410800101 = 57058396LL;
        int64_t addr_410400101 = 90612828LL;
        int64_t addr_409600101 = 90621020LL;
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
block276:
        goto block290;

block301:
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

        goto block290;

block290:
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

        //Small tile
        READ_4b(addr_410400101);
        addr_410400101 += (90612832LL - 90612828LL);

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
            case 5900LL : strd_412400101 = (5904LL - 5900LL); break;
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 93775752LL) addr_412600101 = 90621016LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (23495776LL - 23495772LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 18204LL : strd_413500101 = (18208LL - 18204LL); break;
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 93775760LL) addr_413700101 = 90621024LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (6714464LL - 6714460LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_290 = 0;
        out_290++;
        if (out_290 <= 788683LL) goto block301;
        else goto block302;


block302:
        int dummy;
    }

    // Interval: 1300000000 - 1400000000
    {
        int64_t addr_421400101 = 76994440LL;
        int64_t addr_420800101 = 76994440LL;
        int64_t addr_420500101 = 76994440LL;
        int64_t addr_417900101 = 9869192LL;
        int64_t addr_417600101 = 26650504LL;
        int64_t addr_417300101 = 43431816LL;
        int64_t addr_417000101 = 60213128LL;
        int64_t addr_416500101 = 9869192LL;
        int64_t addr_416200101 = 9869192LL;
        int64_t addr_415900101 = 26650504LL;
        int64_t addr_415600101 = 26650504LL;
        int64_t addr_415300101 = 43431816LL;
        int64_t addr_415000101 = 43431816LL;
        int64_t addr_414700101 = 60213128LL;
        int64_t addr_414400101 = 60213128LL;
        int64_t addr_409600101 = 93775756LL;
        int64_t addr_414100101 = 9869196LL;
        int64_t addr_413700101 = 93775760LL;
        int64_t addr_413500101 = 19020LL, strd_413500101 = 0;
        int64_t addr_413000101 = 26650508LL;
        int64_t addr_412600101 = 93775752LL;
        int64_t addr_412400101 = 6716LL, strd_412400101 = 0;
        int64_t addr_411900101 = 43431820LL;
        int64_t addr_411500101 = 93783948LL;
        int64_t addr_410800101 = 60213132LL;
block303:
        goto block319;

block328:
        //Small tile
        WRITE_4b(addr_410800101);
        addr_410800101 += (60213136LL - 60213132LL);

        //Small tile
        READ_4b(addr_411500101);
        addr_411500101 += (93783952LL - 93783948LL);

        //Small tile
        WRITE_4b(addr_411900101);
        addr_411900101 += (43431824LL - 43431820LL);

        //Small tile
        READ_4b(addr_412400101);
        switch(addr_412400101) {
            case 8892LL : strd_412400101 = (704LL - 8892LL); break;
            case 6716LL : strd_412400101 = (6720LL - 6716LL); break;
            case 704LL : strd_412400101 = (708LL - 704LL); break;
        }
        addr_412400101 += strd_412400101;

        //Dominant stride
        READ_4b(addr_412600101);
        addr_412600101 += 4LL;
        if(addr_412600101 >= 96930476LL) addr_412600101 = 93775752LL;

        //Small tile
        WRITE_4b(addr_413000101);
        addr_413000101 += (26650512LL - 26650508LL);

        //Small tile
        READ_4b(addr_413500101);
        switch(addr_413500101) {
            case 21196LL : strd_413500101 = (13008LL - 21196LL); break;
            case 19020LL : strd_413500101 = (19024LL - 19020LL); break;
            case 13008LL : strd_413500101 = (13012LL - 13008LL); break;
        }
        addr_413500101 += strd_413500101;

        //Dominant stride
        READ_4b(addr_413700101);
        addr_413700101 += 4LL;
        if(addr_413700101 >= 96930484LL) addr_413700101 = 93775760LL;

        //Small tile
        WRITE_4b(addr_414100101);
        addr_414100101 += (9869200LL - 9869196LL);

        goto block319;

block319:
        //Small tile
        READ_4b(addr_414400101);
        addr_414400101 += (60213132LL - 60213128LL);

        //Small tile
        READ_4b(addr_414700101);
        addr_414700101 += (60213132LL - 60213128LL);

        //Small tile
        READ_4b(addr_415000101);
        addr_415000101 += (43431820LL - 43431816LL);

        //Small tile
        READ_4b(addr_415300101);
        addr_415300101 += (43431820LL - 43431816LL);

        //Small tile
        READ_4b(addr_415600101);
        addr_415600101 += (26650508LL - 26650504LL);

        //Small tile
        READ_4b(addr_415900101);
        addr_415900101 += (26650508LL - 26650504LL);

        //Small tile
        READ_4b(addr_416200101);
        addr_416200101 += (9869196LL - 9869192LL);

        //Small tile
        READ_4b(addr_416500101);
        addr_416500101 += (9869196LL - 9869192LL);

        //Small tile
        READ_4b(addr_417000101);
        addr_417000101 += (60213132LL - 60213128LL);

        //Small tile
        READ_4b(addr_417300101);
        addr_417300101 += (43431820LL - 43431816LL);

        //Small tile
        READ_4b(addr_417600101);
        addr_417600101 += (26650508LL - 26650504LL);

        //Small tile
        READ_4b(addr_417900101);
        addr_417900101 += (9869196LL - 9869192LL);

        //Small tile
        WRITE_4b(addr_420500101);
        addr_420500101 += (76994444LL - 76994440LL);

        //Small tile
        READ_4b(addr_420800101);
        addr_420800101 += (76994444LL - 76994440LL);

        //Small tile
        READ_4b(addr_421400101);
        addr_421400101 += (76994444LL - 76994440LL);

        //Small tile
        READ_4b(addr_409600101);
        addr_409600101 += (93775760LL - 93775756LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_319 = 0;
        out_319++;
        if (out_319 <= 788681LL) goto block328;
        else goto block329;


block329:
        int dummy;
    }

    // Interval: 1400000000 - 1402892999
    {
        int64_t addr_410400101 = 96922288LL;
        int64_t addr_410800101 = 63367856LL;
        int64_t addr_411500101 = 96938672LL;
        int64_t addr_411900101 = 46586544LL;
        int64_t addr_412400101 = 7520LL, strd_412400101 = 0;
        int64_t addr_412600101 = 96930476LL;
        int64_t addr_413000101 = 29805232LL;
        int64_t addr_421400101 = 80149168LL;
        int64_t addr_420800101 = 80149168LL;
        int64_t addr_420500101 = 80149168LL;
        int64_t addr_417900101 = 13023920LL;
        int64_t addr_417600101 = 29805232LL;
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
block330:
        goto block337;

block355:
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
        if(addr_413700101 >= 97021748LL) addr_413700101 = 96930484LL;

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

        goto block337;

block337:
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

        //Few edges. Don't bother optimizing
        static uint64_t out_337 = 0;
        out_337++;
        if (out_337 <= 22816LL) goto block355;
        else goto block356;


block356:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
