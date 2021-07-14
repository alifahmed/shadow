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
    uint64_t allocSize = 48005120ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 200000000
    {
        int64_t addr_298400101 = 12000064LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001476LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001488LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001488LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001480LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001492LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001492LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36000064LL, strd_300800101 = 0;
block0:
        goto block8;

block14:
        for(uint64_t loop1 = 0; loop1 < 3000000ULL; loop1++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop1);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop1);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000060LL - 12000064LL) + 12000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 68LL) + 68LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop0 = 0; loop0 < 3000000ULL; loop0++){
            //Loop Indexed
            addr = 64LL + (4 * loop0);
            READ_4b(addr);

        }
        goto block8;

block9:
        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_9 = 0;
        out_9++;
        if (out_9 <= 2999999LL) goto block8;
        else if (out_9 <= 3000000LL) goto block14;
        else goto block8;


block8:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299600101 = (48001496LL - 48001488LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299700101 = (48001496LL - 48001488LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001492LL : strd_299600201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001492LL : strd_299700201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Few edges. Don't bother optimizing
        static uint64_t out_8 = 0;
        out_8++;
        if (out_8 <= 3291335LL) goto block9;
        else goto block15;


block15:
        int dummy;
    }

    // Interval: 200000000 - 400000000
    {
        int64_t addr_298400101 = 13165408LL, strd_298400101 = 0;
        int64_t addr_300800101 = 37165404LL, strd_300800101 = 0;
        int64_t addr_299500101 = 48001508LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001520LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001520LL, strd_299700101 = 0;
        int64_t addr_300600101 = 25165408LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001512LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001524LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001524LL, strd_299700201 = 0;
block16:
        goto block17;

block17:
        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 37165404LL : strd_300800101 = (37165408LL - 37165404LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_17 = 0;
        out_17++;
        if (out_17 <= 2708664LL) goto block18;
        else if (out_17 <= 2708665LL) goto block30;
        else goto block18;


block18:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 13165408LL : strd_298400101 = (13165412LL - 13165408LL); break;
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_18 = 0;
        out_18++;
        if (out_18 <= 3291660LL) goto block25;
        else goto block31;


block25:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001508LL : strd_299500101 = (48001516LL - 48001508LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001520LL : strd_299600101 = (48001528LL - 48001520LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001520LL : strd_299700101 = (48001528LL - 48001520LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 25165408LL : strd_300600101 = (25165412LL - 25165408LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001512LL : strd_299500201 = (48001520LL - 48001512LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001524LL : strd_299600201 = (48001532LL - 48001524LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001524LL : strd_299700201 = (48001532LL - 48001524LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        goto block17;

block30:
        for(uint64_t loop2 = 0; loop2 < 3000000ULL; loop2++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop2);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop2);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000064LL - 12000064LL) + 12000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 68LL) + 68LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop3 = 0; loop3 < 3000000ULL; loop3++){
            //Loop Indexed
            addr = 64LL + (4 * loop3);
            READ_4b(addr);

        }
        goto block18;

block31:
        int dummy;
    }

    // Interval: 400000000 - 600000000
    {
        int64_t addr_299500101 = 48001528LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001540LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001540LL, strd_299700101 = 0;
        int64_t addr_300600101 = 26332048LL, strd_300600101 = 0;
        int64_t addr_298400101 = 14332052LL, strd_298400101 = 0;
        int64_t addr_299500201 = 48001532LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001544LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001544LL, strd_299700201 = 0;
        int64_t addr_300800101 = 38332048LL, strd_300800101 = 0;
block32:
        goto block36;

block46:
        for(uint64_t loop5 = 0; loop5 < 3000000ULL; loop5++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop5);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop5);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000064LL - 12000076LL) + 12000076LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000040LL - 64LL) + 64LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop4 = 0; loop4 < 3000000ULL; loop4++){
            //Loop Indexed
            addr = 64LL + (4 * loop4);
            READ_4b(addr);

        }
        goto block41;

block41:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 14332052LL : strd_298400101 = (14332056LL - 14332052LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        goto block36;

block40:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001532LL : strd_299500201 = (48001540LL - 48001532LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299600201 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299700201 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
            case 38332048LL : strd_300800101 = (38332052LL - 38332048LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_40 = 0;
        out_40++;
        if (out_40 <= 2417003LL) goto block41;
        else if (out_40 <= 2417004LL) goto block46;
        else goto block41;


block36:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001528LL : strd_299500101 = (48001536LL - 48001528LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001540LL : strd_299600101 = (48001548LL - 48001540LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001540LL : strd_299700101 = (48001548LL - 48001540LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
            case 26332048LL : strd_300600101 = (26332052LL - 26332048LL); break;
        }
        addr_300600101 += strd_300600101;

        //Few edges. Don't bother optimizing
        static uint64_t out_36 = 0;
        out_36++;
        if (out_36 <= 3291660LL) goto block40;
        else goto block47;


block47:
        int dummy;
    }

    // Interval: 600000000 - 800000000
    {
        int64_t addr_299500201 = 48001552LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001564LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001564LL, strd_299700201 = 0;
        int64_t addr_300800101 = 39498688LL, strd_300800101 = 0;
        int64_t addr_298400101 = 15498692LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001556LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001568LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001568LL, strd_299700101 = 0;
        int64_t addr_300600101 = 27498692LL, strd_300600101 = 0;
block48:
        goto block52;

block52:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001552LL : strd_299500201 = (48001560LL - 48001552LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001564LL : strd_299600201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001564LL : strd_299700201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
            case 39498688LL : strd_300800101 = (39498692LL - 39498688LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_52 = 0;
        out_52++;
        if (out_52 <= 2125343LL) goto block57;
        else if (out_52 <= 2125344LL) goto block62;
        else if (out_52 <= 3291660LL) goto block57;
        else goto block63;


block57:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 15498692LL : strd_298400101 = (15498696LL - 15498692LL); break;
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001556LL : strd_299500101 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001568LL : strd_299600101 = (48001576LL - 48001568LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001568LL : strd_299700101 = (48001576LL - 48001568LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 27498692LL : strd_300600101 = (27498696LL - 27498692LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        goto block52;

block62:
        for(uint64_t loop6 = 0; loop6 < 3000000ULL; loop6++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop6);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop6);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000064LL - 12000068LL) + 12000068LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 76LL) + 76LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop7 = 0; loop7 < 3000000ULL; loop7++){
            //Loop Indexed
            addr = 64LL + (4 * loop7);
            READ_4b(addr);

        }
        goto block57;

block63:
        int dummy;
    }

    // Interval: 800000000 - 944112579
    {
        int64_t addr_298400101 = 16665332LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001576LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001588LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001588LL, strd_299700101 = 0;
        int64_t addr_300600101 = 28665332LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001580LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001592LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001592LL, strd_299700201 = 0;
        int64_t addr_300800101 = 40665332LL, strd_300800101 = 0;
block64:
        goto block65;

block78:
        for(uint64_t loop9 = 0; loop9 < 3000000ULL; loop9++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop9);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop9);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000060LL - 12000064LL) + 12000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 64LL) + 64LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop8 = 0; loop8 < 3000000ULL; loop8++){
            //Loop Indexed
            addr = 64LL + (4 * loop8);
            READ_4b(addr);

        }
        goto block65;

block73:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001576LL : strd_299500101 = (48001584LL - 48001576LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001588LL : strd_299600101 = (48001596LL - 48001588LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001588LL : strd_299700101 = (48001596LL - 48001588LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 28665332LL : strd_300600101 = (28665336LL - 28665332LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001580LL : strd_299500201 = (48001588LL - 48001580LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
            case 40665332LL : strd_300800101 = (40665336LL - 40665332LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_73 = 0;
        out_73++;
        if (out_73 <= 1833682LL) goto block65;
        else if (out_73 <= 1833683LL) goto block78;
        else goto block65;


block65:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 16665332LL : strd_298400101 = (16665336LL - 16665332LL); break;
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_65 = 0;
        out_65++;
        if (out_65 <= 2127339LL) goto block73;
        else goto block79;


block79:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
