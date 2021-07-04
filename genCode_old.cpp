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
    uint64_t allocSize = 1822720ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    int64_t addr_298400101 = 2368LL;
    int64_t addr_299500101 = 1819076LL, strd_299500101 = 0;
    int64_t addr_299600101 = 1819088LL, strd_299600101 = 0;
    int64_t addr_299700101 = 1819088LL, strd_299700101 = 0;
    int64_t addr_300600101 = 606784LL;
    int64_t addr_299500201 = 1819080LL, strd_299500201 = 0;
    int64_t addr_299600201 = 1819092LL, strd_299600201 = 0;
    int64_t addr_299700201 = 1819092LL, strd_299700201 = 0;
    int64_t addr_300800101 = 1215296LL;

    goto block0;

block10:
    //Small tile
    WRITE_4b(addr_300600101);
    addr_300600101 += 4LL;

    //Small tile
    READ_4b(addr_299500201);
    switch(addr_299500201) {
        case 1819076LL : strd_299500201 = 8LL; break;
        case 1819196LL : strd_299500201 = -116LL; break;
        case 1819080LL : strd_299500201 = 8LL; break;
        case 1819192LL : strd_299500201 = -116LL; break;
    }
    addr_299500201 += strd_299500201;

    //Small tile
    READ_4b(addr_299600201);
    switch(addr_299600201) {
        case 1819076LL : strd_299600201 = 8LL; break;
        case 1819196LL : strd_299600201 = -116LL; break;
        case 1819092LL : strd_299600201 = 8LL; break;
        case 1819080LL : strd_299600201 = 8LL; break;
        case 1819192LL : strd_299600201 = -116LL; break;
    }
    addr_299600201 += strd_299600201;

    //Small tile
    WRITE_4b(addr_299700201);
    switch(addr_299700201) {
        case 1819076LL : strd_299700201 = 8LL; break;
        case 1819196LL : strd_299700201 = -116LL; break;
        case 1819092LL : strd_299700201 = 8LL; break;
        case 1819080LL : strd_299700201 = 8LL; break;
        case 1819192LL : strd_299700201 = -116LL; break;
    }
    addr_299700201 += strd_299700201;

    //Small tile
    WRITE_4b(addr_300800101);
    addr_300800101 += 4LL;

    goto block5;

block5:
    //Small tile
    WRITE_4b(addr_298400101);
    addr_298400101 += 4LL;

    //Small tile
    READ_4b(addr_299500101);
    switch(addr_299500101) {
        case 1819076LL : strd_299500101 = 8LL; break;
        case 1819196LL : strd_299500101 = -116LL; break;
        case 1819080LL : strd_299500101 = 8LL; break;
        case 1819192LL : strd_299500101 = -116LL; break;
    }
    addr_299500101 += strd_299500101;

    //Small tile
    READ_4b(addr_299600101);
    switch(addr_299600101) {
        case 1819076LL : strd_299600101 = 8LL; break;
        case 1819196LL : strd_299600101 = -116LL; break;
        case 1819192LL : strd_299600101 = -116LL; break;
        case 1819080LL : strd_299600101 = 8LL; break;
        case 1819088LL : strd_299600101 = 8LL; break;
    }
    addr_299600101 += strd_299600101;

    //Small tile
    WRITE_4b(addr_299700101);
    switch(addr_299700101) {
        case 1819076LL : strd_299700101 = 8LL; break;
        case 1819196LL : strd_299700101 = -116LL; break;
        case 1819192LL : strd_299700101 = -116LL; break;
        case 1819080LL : strd_299700101 = 8LL; break;
        case 1819088LL : strd_299700101 = 8LL; break;
    }
    addr_299700101 += strd_299700101;

    //Few edges. Don't bother optimizing
    static uint64_t out_5 = 0;
    out_5++;
    if (out_5 <= 150526LL) goto block10;
    else goto block1;


block0:
    goto block5;

block1:
    free((void*)gm);
    return 0;
}
