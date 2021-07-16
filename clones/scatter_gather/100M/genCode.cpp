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

    // Interval: 0 - 100000000
    {
        int64_t addr_298400101 = 12000064LL;
        int64_t addr_299500101 = 48001476LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001488LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001488LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL;
        int64_t addr_299500201 = 48001480LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001492LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001492LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36000064LL;
block0:
        goto block1;

block9:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299600101 = (48001496LL - 48001488LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299700101 = (48001496LL - 48001488LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24000068LL - 24000064LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001492LL : strd_299600201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001492LL : strd_299700201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (36000068LL - 36000064LL);

        goto block1;

block1:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_1 = 0;
        out_1++;
        if (out_1 <= 2083333LL) goto block9;
        else goto block10;


block10:
        int dummy;
    }

    // Interval: 100000000 - 200000000
    {
        int64_t addr_299500101 = 48001548LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001560LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001560LL, strd_299700101 = 0;
        int64_t addr_300600101 = 32333396LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001552LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001564LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001564LL, strd_299700201 = 0;
        int64_t addr_300800101 = 44333396LL, strd_300800101 = 0;
block11:
        goto block18;

block24:
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
        goto block18;

block18:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001548LL : strd_299500101 = (48001556LL - 48001548LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001560LL : strd_299600101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001560LL : strd_299700101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 32333396LL : strd_300600101 = (32333400LL - 32333396LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001552LL : strd_299500201 = (48001560LL - 48001552LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001564LL : strd_299600201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001564LL : strd_299700201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Few edges. Don't bother optimizing
        static uint64_t out_18 = 0;
        out_18++;
        if (out_18 <= 1208002LL) goto block19;
        else goto block25;


block19:
        //Small tile
        WRITE_4b(addr_300800101);
        switch(addr_300800101) {
            case 44333396LL : strd_300800101 = (44333400LL - 44333396LL); break;
            case 36000064LL : strd_300800101 = (36000068LL - 36000064LL); break;
            case 48000060LL : strd_300800101 = (36000064LL - 48000060LL); break;
        }
        addr_300800101 += strd_300800101;

        //Few edges. Don't bother optimizing
        static uint64_t out_19 = 0;
        out_19++;
        if (out_19 <= 916666LL) goto block18;
        else if (out_19 <= 916667LL) goto block24;
        else goto block18;


block25:
        int dummy;
    }

    // Interval: 200000000 - 300000000
    {
        int64_t addr_298400101 = 13165408LL;
        int64_t addr_300800101 = 37165404LL;
        int64_t addr_299500101 = 48001508LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001520LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001520LL, strd_299700101 = 0;
        int64_t addr_300600101 = 25165408LL;
        int64_t addr_299500201 = 48001512LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001524LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001524LL, strd_299700201 = 0;
block26:
        goto block28;

block28:
        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (37165408LL - 37165404LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (13165412LL - 13165408LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_28 = 0;
        out_28++;
        if (out_28 <= 2083333LL) goto block35;
        else goto block36;


block35:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001508LL : strd_299500101 = (48001516LL - 48001508LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001520LL : strd_299600101 = (48001528LL - 48001520LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001520LL : strd_299700101 = (48001528LL - 48001520LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (25165412LL - 25165408LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001512LL : strd_299500201 = (48001520LL - 48001512LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001524LL : strd_299600201 = (48001532LL - 48001524LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001524LL : strd_299700201 = (48001532LL - 48001524LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        goto block28;

block36:
        int dummy;
    }

    // Interval: 300000000 - 400000000
    {
        int64_t addr_298400101 = 21498744LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001580LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001592LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001592LL, strd_299700101 = 0;
        int64_t addr_300600101 = 33498740LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001584LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001596LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001596LL, strd_299700201 = 0;
block37:
        goto block44;

block45:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 21498744LL : strd_298400101 = (21498748LL - 21498744LL); break;
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Few edges. Don't bother optimizing
        static uint64_t out_45 = 0;
        out_45++;
        if (out_45 <= 1208326LL) goto block44;
        else goto block51;


block44:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001580LL : strd_299500101 = (48001588LL - 48001580LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 33498740LL : strd_300600101 = (33498744LL - 33498740LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001584LL : strd_299500201 = (48001592LL - 48001584LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Few edges. Don't bother optimizing
        static uint64_t out_44 = 0;
        out_44++;
        if (out_44 <= 625330LL) goto block45;
        else if (out_44 <= 625331LL) goto block50;
        else goto block45;


block50:
        for(uint64_t loop3 = 0; loop3 < 3000000ULL; loop3++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop3);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop3);
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(24000064LL - 12000064LL) + 12000064LL) & ~3ULL;
            READ_4b(addr);

            //Random
            addr = (bounded_rnd(12000064LL - 68LL) + 68LL) & ~3ULL;
            WRITE_4b(addr);

        }
        for(uint64_t loop2 = 0; loop2 < 3000000ULL; loop2++){
            //Loop Indexed
            addr = 64LL + (4 * loop2);
            READ_4b(addr);

        }
        goto block45;

block51:
        int dummy;
    }

    // Interval: 400000000 - 500000000
    {
        int64_t addr_299500101 = 48001528LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001540LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001540LL, strd_299700101 = 0;
        int64_t addr_300600101 = 26332048LL;
        int64_t addr_298400101 = 14332052LL;
        int64_t addr_299500201 = 48001532LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001544LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001544LL, strd_299700201 = 0;
        int64_t addr_300800101 = 38332048LL;
block52:
        goto block56;

block56:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001528LL : strd_299500101 = (48001536LL - 48001528LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001540LL : strd_299600101 = (48001548LL - 48001540LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001540LL : strd_299700101 = (48001548LL - 48001540LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (26332052LL - 26332048LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_56 = 0;
        out_56++;
        if (out_56 <= 2083333LL) goto block61;
        else goto block62;


block61:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001532LL : strd_299500201 = (48001540LL - 48001532LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299600201 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299700201 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (38332052LL - 38332048LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (14332056LL - 14332052LL);

        goto block56;

block62:
        int dummy;
    }

    // Interval: 500000000 - 600000000
    {
        int64_t addr_298400101 = 22665384LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001484LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001496LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001496LL, strd_299700101 = 0;
        int64_t addr_300600101 = 34665384LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001480LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001492LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001492LL, strd_299700201 = 0;
block63:
        goto block66;

block66:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001492LL : strd_299600201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001492LL : strd_299700201 = (48001500LL - 48001492LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Few edges. Don't bother optimizing
        static uint64_t out_66 = 0;
        out_66++;
        if (out_66 <= 333670LL) goto block71;
        else if (out_66 <= 333671LL) goto block76;
        else goto block71;


block71:
        //Small tile
        WRITE_4b(addr_298400101);
        switch(addr_298400101) {
            case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
            case 22665384LL : strd_298400101 = (22665388LL - 22665384LL); break;
            case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
        }
        addr_298400101 += strd_298400101;

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001484LL : strd_299500101 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001496LL : strd_299600101 = (48001504LL - 48001496LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001496LL : strd_299700101 = (48001504LL - 48001496LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 34665384LL : strd_300600101 = (34665388LL - 34665384LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Few edges. Don't bother optimizing
        static uint64_t out_71 = 0;
        out_71++;
        if (out_71 <= 1208326LL) goto block66;
        else goto block77;


block76:
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
        goto block71;

block77:
        int dummy;
    }

    // Interval: 600000000 - 700000000
    {
        int64_t addr_299500201 = 48001552LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001564LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001564LL, strd_299700201 = 0;
        int64_t addr_300800101 = 39498688LL;
        int64_t addr_298400101 = 15498692LL;
        int64_t addr_299500101 = 48001556LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001568LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001568LL, strd_299700101 = 0;
        int64_t addr_300600101 = 27498692LL;
block78:
        goto block82;

block87:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (15498696LL - 15498692LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001556LL : strd_299500101 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001568LL : strd_299600101 = (48001576LL - 48001568LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001568LL : strd_299700101 = (48001576LL - 48001568LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (27498696LL - 27498692LL);

        goto block82;

block82:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001552LL : strd_299500201 = (48001560LL - 48001552LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001564LL : strd_299600201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001564LL : strd_299700201 = (48001572LL - 48001564LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (39498692LL - 39498688LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_82 = 0;
        out_82++;
        if (out_82 <= 2083333LL) goto block87;
        else goto block88;


block88:
        int dummy;
    }

    // Interval: 700000000 - 800000000
    {
        int64_t addr_298400101 = 23832024LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001504LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001516LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001516LL, strd_299700101 = 0;
        int64_t addr_300600101 = 35832024LL, strd_300600101 = 0;
        int64_t addr_299500201 = 48001508LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001520LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001520LL, strd_299700201 = 0;
block89:
        goto block97;

block97:
        static int64_t loop6_break = 1208327ULL;
        for(uint64_t loop6 = 0; loop6 < 604164ULL; loop6++){
            if(loop6_break-- <= 0) break;
            //Small tile
            WRITE_4b(addr_298400101);
            switch(addr_298400101) {
                case 23832024LL : strd_298400101 = (23832028LL - 23832024LL); break;
                case 12000064LL : strd_298400101 = (12000068LL - 12000064LL); break;
                case 24000060LL : strd_298400101 = (12000064LL - 24000060LL); break;
            }
            addr_298400101 += strd_298400101;

            //Small tile
            READ_4b(addr_299500101);
            switch(addr_299500101) {
                case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
                case 48001504LL : strd_299500101 = (48001512LL - 48001504LL); break;
                case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            }
            addr_299500101 += strd_299500101;

            //Small tile
            READ_4b(addr_299600101);
            switch(addr_299600101) {
                case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
                case 48001516LL : strd_299600101 = (48001524LL - 48001516LL); break;
                case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            }
            addr_299600101 += strd_299600101;

            //Small tile
            WRITE_4b(addr_299700101);
            switch(addr_299700101) {
                case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
                case 48001516LL : strd_299700101 = (48001524LL - 48001516LL); break;
                case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            }
            addr_299700101 += strd_299700101;

            //Small tile
            WRITE_4b(addr_300600101);
            switch(addr_300600101) {
                case 35832024LL : strd_300600101 = (35832028LL - 35832024LL); break;
                case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
                case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
            }
            addr_300600101 += strd_300600101;

            //Small tile
            READ_4b(addr_299500201);
            switch(addr_299500201) {
                case 48001508LL : strd_299500201 = (48001516LL - 48001508LL); break;
                case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            }
            addr_299500201 += strd_299500201;

            //Small tile
            READ_4b(addr_299600201);
            switch(addr_299600201) {
                case 48001520LL : strd_299600201 = (48001528LL - 48001520LL); break;
                case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            }
            addr_299600201 += strd_299600201;

            //Small tile
            WRITE_4b(addr_299700201);
            switch(addr_299700201) {
                case 48001520LL : strd_299700201 = (48001528LL - 48001520LL); break;
                case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            }
            addr_299700201 += strd_299700201;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_97 = 0;
        out_97++;
        if (out_97 <= 1LL) goto block102;
        else goto block103;


block102:
        for(uint64_t loop8 = 0; loop8 < 3000000ULL; loop8++){
            //Loop Indexed
            addr = 36000064LL + (4 * loop8);
            READ_4b(addr);

            //Loop Indexed
            addr = 24000064LL + (4 * loop8);
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
        goto block97;

block103:
        int dummy;
    }

    // Interval: 800000000 - 900000000
    {
        int64_t addr_299500101 = 48001576LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001588LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001588LL, strd_299700101 = 0;
        int64_t addr_299500201 = 48001580LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001592LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001592LL, strd_299700201 = 0;
        int64_t addr_301500101 = 36000064LL;
        int64_t addr_301700101 = 24000064LL;
block104:
        goto block113;

block116:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (36000068LL - 36000064LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (24000068LL - 24000064LL);

        //Random
        addr = (bounded_rnd(24000060LL - 12000068LL) + 12000068LL) & ~3ULL;
        READ_4b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_116 = 0;
        out_116++;
        if (out_116 <= 1497901LL) goto block117;
        else goto block118;


block117:
        //Random
        addr = (bounded_rnd(12000064LL - 64LL) + 64LL) & ~3ULL;
        WRITE_4b(addr);

        goto block116;

block113:
        for(uint64_t loop9 = 0; loop9 < 1833683ULL; loop9++){
            //Loop Indexed
            addr = 16665332LL + (4 * loop9);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_299500101);
            switch(addr_299500101) {
                case 48001576LL : strd_299500101 = (48001584LL - 48001576LL); break;
                case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            }
            addr_299500101 += strd_299500101;

            //Small tile
            READ_4b(addr_299600101);
            switch(addr_299600101) {
                case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
                case 48001588LL : strd_299600101 = (48001596LL - 48001588LL); break;
                case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            }
            addr_299600101 += strd_299600101;

            //Small tile
            WRITE_4b(addr_299700101);
            switch(addr_299700101) {
                case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
                case 48001588LL : strd_299700101 = (48001596LL - 48001588LL); break;
                case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            }
            addr_299700101 += strd_299700101;

            //Loop Indexed
            addr = 28665332LL + (4 * loop9);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_299500201);
            switch(addr_299500201) {
                case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
                case 48001580LL : strd_299500201 = (48001588LL - 48001580LL); break;
                case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            }
            addr_299500201 += strd_299500201;

            //Small tile
            READ_4b(addr_299600201);
            switch(addr_299600201) {
                case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            }
            addr_299600201 += strd_299600201;

            //Small tile
            WRITE_4b(addr_299700201);
            switch(addr_299700201) {
                case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
                case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            }
            addr_299700201 += strd_299700201;

            //Loop Indexed
            addr = 40665332LL + (4 * loop9);
            WRITE_4b(addr);

        }
        goto block116;

block118:
        int dummy;
    }

    // Interval: 900000000 - 944112579
    {
        int64_t addr_301500101 = 41991672LL;
        int64_t addr_301700101 = 29991672LL;
        int64_t addr_298400101 = 12000064LL;
        int64_t addr_299500101 = 48001592LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001480LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001480LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL;
        int64_t addr_299500201 = 48001596LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001484LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001484LL, strd_299700201 = 0;
block119:
        goto block120;

block120:
        //Random
        addr = (bounded_rnd(12000052LL - 68LL) + 68LL) & ~3ULL;
        WRITE_4b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_120 = 0;
        out_120++;
        if (out_120 <= 1502098LL) goto block123;
        else goto block124;


block125:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_125 = 0;
        out_125++;
        if (out_125 <= 293656LL) goto block132;
        else goto block133;


block124:
        for(uint64_t loop10 = 0; loop10 < 3000000ULL; loop10++){
            //Loop Indexed
            addr = 64LL + (4 * loop10);
            READ_4b(addr);

        }
        goto block125;

block123:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (41991676LL - 41991672LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (29991676LL - 29991672LL);

        //Random
        addr = (bounded_rnd(24000060LL - 12000064LL) + 12000064LL) & ~3ULL;
        READ_4b(addr);

        goto block120;

block132:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24000068LL - 24000064LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            case 48001484LL : strd_299600201 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            case 48001484LL : strd_299700201 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
        }
        addr_299700201 += strd_299700201;

        goto block125;

block133:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
