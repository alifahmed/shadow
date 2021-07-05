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
    uint64_t allocSize = 16007168ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 186016480
    {
        int64_t addr_299700201 = 16003540UL, strd_299700201 = 0;
        int64_t addr_299600201 = 16003540UL, strd_299600201 = 0;
        int64_t addr_299500201 = 16003528UL, strd_299500201 = 0;
        int64_t addr_299700101 = 16003536UL, strd_299700101 = 0;
        int64_t addr_299600101 = 16003536UL, strd_299600101 = 0;
        int64_t addr_299500101 = 16003524UL, strd_299500101 = 0;
block0:
        goto block14;

block14:
        for(uint64_t loop3 = 0; loop3 < 3ULL; loop3++){
            for(uint64_t loop2 = 0; loop2 < 1000000ULL; loop2++){
                //Loop Indexed
                addr = 4000064UL + (4 * loop2);
                WRITE_4b(addr);

                //Small tile
                READ_4b(addr_299500101);
                switch(addr_299500101) {
                    case 16003524UL : strd_299500101 = 8LL; break;
                    case 16003644UL : strd_299500101 = -116LL; break;
                    case 16003528UL : strd_299500101 = 8LL; break;
                    case 16003640UL : strd_299500101 = -116LL; break;
                }
                addr_299500101 += strd_299500101;

                //Small tile
                READ_4b(addr_299600101);
                switch(addr_299600101) {
                    case 16003524UL : strd_299600101 = 8LL; break;
                    case 16003644UL : strd_299600101 = -116LL; break;
                    case 16003640UL : strd_299600101 = -116LL; break;
                    case 16003528UL : strd_299600101 = 8LL; break;
                    case 16003536UL : strd_299600101 = 8LL; break;
                }
                addr_299600101 += strd_299600101;

                //Small tile
                WRITE_4b(addr_299700101);
                switch(addr_299700101) {
                    case 16003524UL : strd_299700101 = 8LL; break;
                    case 16003644UL : strd_299700101 = -116LL; break;
                    case 16003640UL : strd_299700101 = -116LL; break;
                    case 16003528UL : strd_299700101 = 8LL; break;
                    case 16003536UL : strd_299700101 = 8LL; break;
                }
                addr_299700101 += strd_299700101;

                //Loop Indexed
                addr = 8000064UL + (4 * loop2);
                WRITE_4b(addr);

                //Small tile
                READ_4b(addr_299500201);
                switch(addr_299500201) {
                    case 16003524UL : strd_299500201 = 8LL; break;
                    case 16003644UL : strd_299500201 = -116LL; break;
                    case 16003528UL : strd_299500201 = 8LL; break;
                    case 16003640UL : strd_299500201 = -116LL; break;
                }
                addr_299500201 += strd_299500201;

                //Small tile
                READ_4b(addr_299600201);
                switch(addr_299600201) {
                    case 16003524UL : strd_299600201 = 8LL; break;
                    case 16003644UL : strd_299600201 = -116LL; break;
                    case 16003540UL : strd_299600201 = 8LL; break;
                    case 16003528UL : strd_299600201 = 8LL; break;
                    case 16003640UL : strd_299600201 = -116LL; break;
                }
                addr_299600201 += strd_299600201;

                //Small tile
                WRITE_4b(addr_299700201);
                switch(addr_299700201) {
                    case 16003524UL : strd_299700201 = 8LL; break;
                    case 16003644UL : strd_299700201 = -116LL; break;
                    case 16003540UL : strd_299700201 = 8LL; break;
                    case 16003528UL : strd_299700201 = 8LL; break;
                    case 16003640UL : strd_299700201 = -116LL; break;
                }
                addr_299700201 += strd_299700201;

                //Loop Indexed
                addr = 12000064UL + (4 * loop2);
                WRITE_4b(addr);

            }
            for(uint64_t loop1 = 0; loop1 < 1000000ULL; loop1++){
                //Loop Indexed
                addr = 12000064UL + (4 * loop1);
                READ_4b(addr);

                //Loop Indexed
                addr = 8000064UL + (4 * loop1);
                READ_4b(addr);

                //Random
                addr = (bounded_rnd(4000000) + 4000064UL) & ~3ULL;
                READ_4b(addr);

                //Random
                addr = (bounded_rnd(4000000) + 64UL) & ~3ULL;
                WRITE_4b(addr);

            }
            for(uint64_t loop0 = 0; loop0 < 1000000ULL; loop0++){
                //Loop Indexed
                addr = 64UL + (4 * loop0);
                READ_4b(addr);

            }
        }
        goto block15;

block15:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
