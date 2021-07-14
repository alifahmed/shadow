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
    uint64_t allocSize = 23547904ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 153830930
    {
        int64_t addr_314100701 = 3808LL, strd_314100701 = 0;
        int64_t addr_314000701 = 3776LL, strd_314000701 = 0;
        int64_t addr_313900701 = 3744LL, strd_313900701 = 0;
        int64_t addr_313800701 = 3712LL, strd_313800701 = 0;
        int64_t addr_313800601 = 3712LL, strd_313800601 = 0;
        int64_t addr_313900601 = 3744LL, strd_313900601 = 0;
        int64_t addr_314000601 = 3776LL, strd_314000601 = 0;
        int64_t addr_314100601 = 3808LL, strd_314100601 = 0;
block0:
        goto block11;

block11:
        for(uint64_t loop5 = 0; loop5 < 18ULL; loop5++){
            static int64_t loop4_break = 1311754ULL;
            for(uint64_t loop4 = 0; loop4 < 72876ULL; loop4++){
                if(loop4_break-- <= 0) break;
                //Small tile
                WRITE_32b(addr_313800601);
                switch(addr_313800601) {
                    case 3712LL : strd_313800601 = (3840LL - 3712LL); break;
                    case 182016LL : strd_313800601 = (3712LL - 182016LL); break;
                }
                addr_313800601 += strd_313800601;

                //Small tile
                WRITE_32b(addr_313900601);
                switch(addr_313900601) {
                    case 3744LL : strd_313900601 = (3872LL - 3744LL); break;
                    case 182048LL : strd_313900601 = (3744LL - 182048LL); break;
                }
                addr_313900601 += strd_313900601;

                //Small tile
                WRITE_32b(addr_314000601);
                switch(addr_314000601) {
                    case 3776LL : strd_314000601 = (3904LL - 3776LL); break;
                    case 182080LL : strd_314000601 = (3776LL - 182080LL); break;
                }
                addr_314000601 += strd_314000601;

                //Small tile
                WRITE_32b(addr_314100601);
                switch(addr_314100601) {
                    case 3808LL : strd_314100601 = (3936LL - 3808LL); break;
                    case 182112LL : strd_314100601 = (3808LL - 182112LL); break;
                }
                addr_314100601 += strd_314100601;

            }
            static int64_t loop3_break = 1370302ULL;
            for(uint64_t loop3 = 0; loop3 < 76128ULL; loop3++){
                if(loop3_break-- <= 0) break;
                //Small tile
                WRITE_32b(addr_313800701);
                switch(addr_313800701) {
                    case 3712LL : strd_313800701 = (3840LL - 3712LL); break;
                    case 182016LL : strd_313800701 = (3712LL - 182016LL); break;
                }
                addr_313800701 += strd_313800701;

                //Small tile
                WRITE_32b(addr_313900701);
                switch(addr_313900701) {
                    case 3744LL : strd_313900701 = (3872LL - 3744LL); break;
                    case 182048LL : strd_313900701 = (3744LL - 182048LL); break;
                }
                addr_313900701 += strd_313900701;

                //Small tile
                WRITE_32b(addr_314000701);
                switch(addr_314000701) {
                    case 3776LL : strd_314000701 = (3904LL - 3776LL); break;
                    case 182080LL : strd_314000701 = (3776LL - 182080LL); break;
                }
                addr_314000701 += strd_314000701;

                //Small tile
                WRITE_32b(addr_314100701);
                switch(addr_314100701) {
                    case 3808LL : strd_314100701 = (3936LL - 3808LL); break;
                    case 182112LL : strd_314100701 = (3808LL - 182112LL); break;
                }
                addr_314100701 += strd_314100701;

            }
            for(uint64_t loop2 = 0; loop2 < 600000ULL; loop2++){
                //Loop Indexed
                addr = 18747408LL + (8 * loop2);
                WRITE_8b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 560000ULL; loop1++){
                //Loop Indexed
                addr = 184340LL + (16 * loop1);
                WRITE_4b(addr);

            }
            for(uint64_t loop0 = 0; loop0 < 400000ULL; loop0++){
                //Loop Indexed
                addr = 9146392LL + (24 * loop0);
                WRITE_8b(addr);

            }
        }
        goto block12;

block12:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
