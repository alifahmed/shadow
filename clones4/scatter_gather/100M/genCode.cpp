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

    // Interval: 0 - 100000000
    {
        int64_t addr_298500101 = 4000064LL, strd_298500101 = 0;
        int64_t addr_299600101 = 16003524LL, strd_299600101 = 0;
        int64_t addr_299700101 = 16003536LL, strd_299700101 = 0;
        int64_t addr_299800101 = 16003536LL, strd_299800101 = 0;
        int64_t addr_300700101 = 8000064LL, strd_300700101 = 0;
        int64_t addr_299600201 = 16003528LL, strd_299600201 = 0;
        int64_t addr_299700201 = 16003540LL, strd_299700201 = 0;
        int64_t addr_299800201 = 16003540LL, strd_299800201 = 0;
        int64_t addr_300900101 = 12000064LL, strd_300900101 = 0;
block0:
        goto block8;

block13:
        for(uint64_t loop1 = 0; loop1 < 1000000ULL; loop1++){
            //Loop Indexed
            addr = 8000064LL + (4 * loop1);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(8000064LL - 4000064LL) + 4000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(4000064LL - 72LL) + 72LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 1000000ULL; loop0++){
            //Loop Indexed
            addr = 64LL + (4 * loop0);
            READ_4b(addr);

        }
        goto block8;

block9:
        //Small tile
        WRITE_4b(addr_300900101);
        switch(addr_300900101) {
            case 12000064LL : strd_300900101 = (12000068LL - 12000064LL); break;
            case 16000060LL : strd_300900101 = (12000064LL - 16000060LL); break;
        }
        addr_300900101 += strd_300900101;

        //Few edges. Don't bother optimizing
        static uint64_t out_9 = 0;
        out_9++;
        if (out_9 <= 999999LL) goto block8;
        else if (out_9 <= 1000000LL) goto block13;
        else goto block8;


block8:
        //Small tile
        WRITE_4b(addr_298500101);
        switch(addr_298500101) {
            case 4000064LL : strd_298500101 = (4000068LL - 4000064LL); break;
            case 8000060LL : strd_298500101 = (4000064LL - 8000060LL); break;
        }
        addr_298500101 += strd_298500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 16003644LL : strd_299600101 = (16003528LL - 16003644LL); break;
            case 16003528LL : strd_299600101 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299600101 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299600101 = (16003532LL - 16003524LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        READ_4b(addr_299700101);
        switch(addr_299700101) {
            case 16003644LL : strd_299700101 = (16003528LL - 16003644LL); break;
            case 16003640LL : strd_299700101 = (16003524LL - 16003640LL); break;
            case 16003528LL : strd_299700101 = (16003536LL - 16003528LL); break;
            case 16003536LL : strd_299700101 = (16003544LL - 16003536LL); break;
            case 16003524LL : strd_299700101 = (16003532LL - 16003524LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_299800101);
        switch(addr_299800101) {
            case 16003644LL : strd_299800101 = (16003528LL - 16003644LL); break;
            case 16003640LL : strd_299800101 = (16003524LL - 16003640LL); break;
            case 16003528LL : strd_299800101 = (16003536LL - 16003528LL); break;
            case 16003536LL : strd_299800101 = (16003544LL - 16003536LL); break;
            case 16003524LL : strd_299800101 = (16003532LL - 16003524LL); break;
        }
        addr_299800101 += strd_299800101;

        //Small tile
        WRITE_4b(addr_300700101);
        switch(addr_300700101) {
            case 8000064LL : strd_300700101 = (8000068LL - 8000064LL); break;
            case 12000060LL : strd_300700101 = (8000064LL - 12000060LL); break;
        }
        addr_300700101 += strd_300700101;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 16003644LL : strd_299600201 = (16003528LL - 16003644LL); break;
            case 16003528LL : strd_299600201 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299600201 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299600201 = (16003532LL - 16003524LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        READ_4b(addr_299700201);
        switch(addr_299700201) {
            case 16003644LL : strd_299700201 = (16003528LL - 16003644LL); break;
            case 16003540LL : strd_299700201 = (16003548LL - 16003540LL); break;
            case 16003528LL : strd_299700201 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299700201 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299700201 = (16003532LL - 16003524LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_299800201);
        switch(addr_299800201) {
            case 16003644LL : strd_299800201 = (16003528LL - 16003644LL); break;
            case 16003540LL : strd_299800201 = (16003548LL - 16003540LL); break;
            case 16003528LL : strd_299800201 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299800201 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299800201 = (16003532LL - 16003524LL); break;
        }
        addr_299800201 += strd_299800201;

        //Few edges. Don't bother optimizing
        static uint64_t out_8 = 0;
        out_8++;
        if (out_8 <= 1791335LL) goto block9;
        else goto block14;


block14:
        int dummy;
    }

    // Interval: 100000000 - 186016480
    {
        int64_t addr_300900101 = 15165404LL, strd_300900101 = 0;
        int64_t addr_298500101 = 7165408LL, strd_298500101 = 0;
        int64_t addr_299600101 = 16003532LL, strd_299600101 = 0;
        int64_t addr_299700101 = 16003544LL, strd_299700101 = 0;
        int64_t addr_299800101 = 16003544LL, strd_299800101 = 0;
        int64_t addr_300700101 = 11165408LL, strd_300700101 = 0;
        int64_t addr_299600201 = 16003536LL, strd_299600201 = 0;
        int64_t addr_299700201 = 16003548LL, strd_299700201 = 0;
        int64_t addr_299800201 = 16003548LL, strd_299800201 = 0;
block15:
        goto block16;

block16:
        //Small tile
        WRITE_4b(addr_300900101);
        switch(addr_300900101) {
            case 15165404LL : strd_300900101 = (15165408LL - 15165404LL); break;
            case 16000060LL : strd_300900101 = (12000064LL - 16000060LL); break;
            case 12000064LL : strd_300900101 = (12000068LL - 12000064LL); break;
        }
        addr_300900101 += strd_300900101;

        //Few edges. Don't bother optimizing
        static uint64_t out_16 = 0;
        out_16++;
        if (out_16 <= 208664LL) goto block24;
        else if (out_16 <= 208665LL) goto block29;
        else if (out_16 <= 1208664LL) goto block24;
        else goto block29;


block24:
        //Small tile
        WRITE_4b(addr_298500101);
        switch(addr_298500101) {
            case 7165408LL : strd_298500101 = (7165412LL - 7165408LL); break;
            case 4000064LL : strd_298500101 = (4000068LL - 4000064LL); break;
            case 8000060LL : strd_298500101 = (4000064LL - 8000060LL); break;
        }
        addr_298500101 += strd_298500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 16003532LL : strd_299600101 = (16003540LL - 16003532LL); break;
            case 16003644LL : strd_299600101 = (16003528LL - 16003644LL); break;
            case 16003528LL : strd_299600101 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299600101 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299600101 = (16003532LL - 16003524LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        READ_4b(addr_299700101);
        switch(addr_299700101) {
            case 16003644LL : strd_299700101 = (16003528LL - 16003644LL); break;
            case 16003640LL : strd_299700101 = (16003524LL - 16003640LL); break;
            case 16003528LL : strd_299700101 = (16003536LL - 16003528LL); break;
            case 16003544LL : strd_299700101 = (16003552LL - 16003544LL); break;
            case 16003524LL : strd_299700101 = (16003532LL - 16003524LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_299800101);
        switch(addr_299800101) {
            case 16003644LL : strd_299800101 = (16003528LL - 16003644LL); break;
            case 16003640LL : strd_299800101 = (16003524LL - 16003640LL); break;
            case 16003528LL : strd_299800101 = (16003536LL - 16003528LL); break;
            case 16003544LL : strd_299800101 = (16003552LL - 16003544LL); break;
            case 16003524LL : strd_299800101 = (16003532LL - 16003524LL); break;
        }
        addr_299800101 += strd_299800101;

        //Small tile
        WRITE_4b(addr_300700101);
        switch(addr_300700101) {
            case 11165408LL : strd_300700101 = (11165412LL - 11165408LL); break;
            case 8000064LL : strd_300700101 = (8000068LL - 8000064LL); break;
            case 12000060LL : strd_300700101 = (8000064LL - 12000060LL); break;
        }
        addr_300700101 += strd_300700101;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 16003644LL : strd_299600201 = (16003528LL - 16003644LL); break;
            case 16003640LL : strd_299600201 = (16003524LL - 16003640LL); break;
            case 16003528LL : strd_299600201 = (16003536LL - 16003528LL); break;
            case 16003536LL : strd_299600201 = (16003544LL - 16003536LL); break;
            case 16003524LL : strd_299600201 = (16003532LL - 16003524LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        READ_4b(addr_299700201);
        switch(addr_299700201) {
            case 16003644LL : strd_299700201 = (16003528LL - 16003644LL); break;
            case 16003548LL : strd_299700201 = (16003556LL - 16003548LL); break;
            case 16003528LL : strd_299700201 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299700201 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299700201 = (16003532LL - 16003524LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_299800201);
        switch(addr_299800201) {
            case 16003644LL : strd_299800201 = (16003528LL - 16003644LL); break;
            case 16003548LL : strd_299800201 = (16003556LL - 16003548LL); break;
            case 16003528LL : strd_299800201 = (16003536LL - 16003528LL); break;
            case 16003640LL : strd_299800201 = (16003524LL - 16003640LL); break;
            case 16003524LL : strd_299800201 = (16003532LL - 16003524LL); break;
        }
        addr_299800201 += strd_299800201;

        goto block16;

block29:
        for(uint64_t loop2 = 0; loop2 < 1000000ULL; loop2++){
            //Loop Indexed
            addr = 12000064LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 8000064LL + (4 * loop2);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(8000064LL - 4000064LL) + 4000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(4000064LL - 64LL) + 64LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop3 = 0; loop3 < 1000000ULL; loop3++){
            //Loop Indexed
            addr = 64LL + (4 * loop3);
            READ_4b(addr);

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_29 = 0;
        out_29++;
        if (out_29 <= 1LL) goto block24;
        else goto block30;


block30:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
