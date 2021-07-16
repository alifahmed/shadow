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

    // Interval: 0 - 50000000
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
        goto block5;

block9:
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

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (36000068LL - 36000064LL);

        goto block5;

block5:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

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
        addr_300600101 += (24000068LL - 24000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_5 = 0;
        out_5++;
        if (out_5 <= 1041666LL) goto block9;
        else goto block10;


block10:
        int dummy;
    }

    // Interval: 50000000 - 100000000
    {
        int64_t addr_298400101 = 16166732LL;
        int64_t addr_299500201 = 48001512LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001524LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001524LL, strd_299700201 = 0;
        int64_t addr_300800101 = 40166728LL;
        int64_t addr_299500101 = 48001516LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001528LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001528LL, strd_299700101 = 0;
        int64_t addr_300600101 = 28166732LL;
block11:
        goto block16;

block16:
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

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (40166732LL - 40166728LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (16166736LL - 16166732LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_16 = 0;
        out_16++;
        if (out_16 <= 1041666LL) goto block20;
        else goto block21;


block20:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001516LL : strd_299500101 = (48001524LL - 48001516LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001528LL : strd_299600101 = (48001536LL - 48001528LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001528LL : strd_299700101 = (48001536LL - 48001528LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (28166736LL - 28166732LL);

        goto block16;

block21:
        int dummy;
    }

    // Interval: 100000000 - 150000000
    {
        int64_t addr_299500101 = 48001548LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001560LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001560LL, strd_299700101 = 0;
        int64_t addr_300600101 = 32333396LL;
        int64_t addr_299500201 = 48001552LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001564LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001564LL, strd_299700201 = 0;
        int64_t addr_300800101 = 44333396LL;
        int64_t addr_298400101 = 20333400LL;
        int64_t addr_301500101 = 36000064LL;
        int64_t addr_301700101 = 24000064LL;
block22:
        goto block30;

block35:
        //Random
        addr = (bounded_rnd(24000060LL - 12000076LL) + 12000076LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(12000036LL - 80LL) + 80LL) & ~3ULL;
        WRITE_4b(addr);

        goto block33;

block33:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (36000068LL - 36000064LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (24000068LL - 24000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_33 = 0;
        out_33++;
        if (out_33 <= 749998LL) goto block35;
        else goto block36;


block31:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (20333404LL - 20333400LL);

        goto block30;

block30:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001548LL : strd_299500101 = (48001556LL - 48001548LL); break;
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
            case 48001560LL : strd_299600101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001560LL : strd_299700101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (32333400LL - 32333396LL);

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
        addr_300800101 += (44333400LL - 44333396LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_30 = 0;
        out_30++;
        if (out_30 <= 916666LL) goto block31;
        else goto block33;


block36:
        int dummy;
    }

    // Interval: 150000000 - 200000000
    {
        int64_t addr_301700101 = 27000060LL;
        int64_t addr_301500101 = 39000060LL;
        int64_t addr_299700201 = 48001540LL, strd_299700201 = 0;
        int64_t addr_299600201 = 48001540LL, strd_299600201 = 0;
        int64_t addr_299500201 = 48001528LL, strd_299500201 = 0;
        int64_t addr_299700101 = 48001536LL, strd_299700101 = 0;
        int64_t addr_299600101 = 48001536LL, strd_299600101 = 0;
        int64_t addr_299500101 = 48001524LL, strd_299500101 = 0;
block37:
        goto block39;

block39:
        //Random
        addr = (bounded_rnd(24000056LL - 12000064LL) + 12000064LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(12000064LL - 68LL) + 68LL) & ~3ULL;
        WRITE_4b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_39 = 0;
        out_39++;
        if (out_39 <= 2250001LL) goto block41;
        else goto block49;


block41:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (39000064LL - 39000060LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (27000064LL - 27000060LL);

        goto block39;

block49:
        for(uint64_t loop0 = 0; loop0 < 3000000ULL; loop0++){
            //Loop Indexed
            addr = 64LL + (4 * loop0);
            READ_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 291336ULL; loop1++){
            //Small tile
            READ_4b(addr_299500101);
            switch(addr_299500101) {
                case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
                case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
                case 48001524LL : strd_299500101 = (48001532LL - 48001524LL); break;
                case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            }
            addr_299500101 += strd_299500101;

            //Small tile
            READ_4b(addr_299600101);
            switch(addr_299600101) {
                case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
                case 48001536LL : strd_299600101 = (48001544LL - 48001536LL); break;
                case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
                case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            }
            addr_299600101 += strd_299600101;

            //Small tile
            WRITE_4b(addr_299700101);
            switch(addr_299700101) {
                case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
                case 48001536LL : strd_299700101 = (48001544LL - 48001536LL); break;
                case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
                case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            }
            addr_299700101 += strd_299700101;

            //Loop Indexed
            addr = 24000064LL + (4 * loop1);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_299500201);
            switch(addr_299500201) {
                case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
                case 48001528LL : strd_299500201 = (48001536LL - 48001528LL); break;
                case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
            }
            addr_299500201 += strd_299500201;

            //Small tile
            READ_4b(addr_299600201);
            switch(addr_299600201) {
                case 48001540LL : strd_299600201 = (48001548LL - 48001540LL); break;
                case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
                case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
                case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            }
            addr_299600201 += strd_299600201;

            //Small tile
            WRITE_4b(addr_299700201);
            switch(addr_299700201) {
                case 48001540LL : strd_299700201 = (48001548LL - 48001540LL); break;
                case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
                case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
                case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            }
            addr_299700201 += strd_299700201;

        }
        goto block50;

block50:
        int dummy;
    }

    // Interval: 200000000 - 250000000
    {
        int64_t addr_298400101 = 13165408LL;
        int64_t addr_299500101 = 48001508LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001520LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001520LL, strd_299700101 = 0;
        int64_t addr_300600101 = 25165408LL;
        int64_t addr_300800101 = 37165404LL;
        int64_t addr_299500201 = 48001512LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001524LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001524LL, strd_299700201 = 0;
block51:
        goto block57;

block60:
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

        goto block57;

block57:
        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (37165408LL - 37165404LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (13165412LL - 13165408LL);

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
        addr_300600101 += (25165412LL - 25165408LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_57 = 0;
        out_57++;
        if (out_57 <= 1041666LL) goto block60;
        else goto block61;


block61:
        int dummy;
    }

    // Interval: 250000000 - 300000000
    {
        int64_t addr_298400101 = 17332076LL;
        int64_t addr_299500201 = 48001544LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001556LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001556LL, strd_299700201 = 0;
        int64_t addr_300800101 = 41332072LL;
        int64_t addr_299500101 = 48001548LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001560LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001560LL, strd_299700101 = 0;
        int64_t addr_300600101 = 29332076LL;
block62:
        goto block67;

block67:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299500201 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001556LL : strd_299600201 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001556LL : strd_299700201 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (41332076LL - 41332072LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (17332080LL - 17332076LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_67 = 0;
        out_67++;
        if (out_67 <= 1041666LL) goto block71;
        else goto block72;


block71:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001548LL : strd_299500101 = (48001556LL - 48001548LL); break;
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
            case 48001560LL : strd_299600101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001560LL : strd_299700101 = (48001568LL - 48001560LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (29332080LL - 29332076LL);

        goto block67;

block72:
        int dummy;
    }

    // Interval: 300000000 - 350000000
    {
        int64_t addr_301500101 = 36000064LL;
        int64_t addr_301700101 = 24000064LL;
        int64_t addr_299500101 = 48001580LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001592LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001592LL, strd_299700101 = 0;
        int64_t addr_299500201 = 48001584LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001596LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001596LL, strd_299700201 = 0;
block73:
        goto block81;

block85:
        //Random
        addr = (bounded_rnd(24000064LL - 12000064LL) + 12000064LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(12000064LL - 72LL) + 72LL) & ~3ULL;
        WRITE_4b(addr);

        goto block83;

block83:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (36000068LL - 36000064LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (24000068LL - 24000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_83 = 0;
        out_83++;
        if (out_83 <= 2498014LL) goto block85;
        else goto block86;


block81:
        for(uint64_t loop2 = 0; loop2 < 625331ULL; loop2++){
            //Small tile
            READ_4b(addr_299500101);
            switch(addr_299500101) {
                case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
                case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
                case 48001580LL : strd_299500101 = (48001588LL - 48001580LL); break;
                case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
            }
            addr_299500101 += strd_299500101;

            //Small tile
            READ_4b(addr_299600101);
            switch(addr_299600101) {
                case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
                case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
            }
            addr_299600101 += strd_299600101;

            //Small tile
            WRITE_4b(addr_299700101);
            switch(addr_299700101) {
                case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
                case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
                case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
                case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
            }
            addr_299700101 += strd_299700101;

            //Loop Indexed
            addr = 33498740LL + (4 * loop2);
            WRITE_4b(addr);

            //Small tile
            READ_4b(addr_299500201);
            switch(addr_299500201) {
                case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
                case 48001584LL : strd_299500201 = (48001592LL - 48001584LL); break;
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
                case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
            }
            addr_299600201 += strd_299600201;

            //Small tile
            WRITE_4b(addr_299700201);
            switch(addr_299700201) {
                case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
                case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
                case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
                case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
            }
            addr_299700201 += strd_299700201;

            //Loop Indexed
            addr = 45498740LL + (4 * loop2);
            WRITE_4b(addr);

        }
        goto block83;

block86:
        int dummy;
    }

    // Interval: 350000000 - 400000000
    {
        int64_t addr_298400101 = 12000064LL;
        int64_t addr_299500101 = 48001572LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001584LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001584LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL;
        int64_t addr_299500201 = 48001576LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001588LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001588LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36000064LL;
        int64_t addr_301500101 = 45992124LL;
block87:
        goto block89;

block89:
        //Random
        addr = (bounded_rnd(24000044LL - 12000076LL) + 12000076LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(12000060LL - 68LL) + 68LL) & ~3ULL;
        WRITE_4b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_89 = 0;
        out_89++;
        if (out_89 <= 501985LL) goto block90;
        else goto block91;


block90:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (45992128LL - 45992124LL);

        goto block89;

block91:
        for(uint64_t loop3 = 0; loop3 < 3000000ULL; loop3++){
            //Loop Indexed
            addr = 64LL + (4 * loop3);
            READ_4b(addr);

        }
        goto block92;

block92:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_92 = 0;
        out_92++;
        if (out_92 <= 582996LL) goto block100;
        else goto block101;


block100:
        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001572LL : strd_299500101 = (48001580LL - 48001572LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001584LL : strd_299600101 = (48001592LL - 48001584LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001584LL : strd_299700101 = (48001592LL - 48001584LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24000068LL - 24000064LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001576LL : strd_299500201 = (48001584LL - 48001576LL); break;
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
            case 48001588LL : strd_299600201 = (48001596LL - 48001588LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001588LL : strd_299700201 = (48001596LL - 48001588LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (36000068LL - 36000064LL);

        goto block92;

block101:
        int dummy;
    }

    // Interval: 400000000 - 450000000
    {
        int64_t addr_299500101 = 48001528LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001540LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001540LL, strd_299700101 = 0;
        int64_t addr_300600101 = 26332048LL;
        int64_t addr_299500201 = 48001532LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001544LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001544LL, strd_299700201 = 0;
        int64_t addr_298400101 = 14332052LL;
        int64_t addr_300800101 = 38332048LL;
block102:
        goto block109;

block111:
        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (38332052LL - 38332048LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (14332056LL - 14332052LL);

        goto block109;

block109:
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
        addr_300600101 += (26332052LL - 26332048LL);

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

        //Few edges. Don't bother optimizing
        static uint64_t out_109 = 0;
        out_109++;
        if (out_109 <= 1041666LL) goto block111;
        else goto block112;


block112:
        int dummy;
    }

    // Interval: 450000000 - 500000000
    {
        int64_t addr_298400101 = 18498716LL;
        int64_t addr_299500101 = 48001568LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001580LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001580LL, strd_299700101 = 0;
        int64_t addr_300600101 = 30498716LL;
        int64_t addr_300800101 = 42498712LL;
        int64_t addr_299500201 = 48001572LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001584LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001584LL, strd_299700201 = 0;
block113:
        goto block119;

block119:
        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (42498716LL - 42498712LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (18498720LL - 18498716LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001568LL : strd_299500101 = (48001576LL - 48001568LL); break;
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
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
            case 48001580LL : strd_299600101 = (48001588LL - 48001580LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001580LL : strd_299700101 = (48001588LL - 48001580LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (30498720LL - 30498716LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_119 = 0;
        out_119++;
        if (out_119 <= 1041666LL) goto block122;
        else goto block123;


block122:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001572LL : strd_299500201 = (48001580LL - 48001572LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001584LL : strd_299600201 = (48001592LL - 48001584LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001584LL : strd_299700201 = (48001592LL - 48001584LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        goto block119;

block123:
        int dummy;
    }

    // Interval: 500000000 - 550000000
    {
        int64_t addr_299500201 = 48001480LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001492LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001492LL, strd_299700201 = 0;
        int64_t addr_300800101 = 46665380LL;
        int64_t addr_298400101 = 22665384LL;
        int64_t addr_299500101 = 48001484LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001496LL, strd_299600101 = 0;
block124:
        goto block128;

block136:
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
        for(uint64_t loop4 = 0; loop4 < 1663968ULL; loop4++){
            //Loop Indexed
            addr = 64LL + (4 * loop4);
            READ_4b(addr);

        }
        goto block137;

block131:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (22665388LL - 22665384LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001484LL : strd_299500101 = (48001492LL - 48001484LL); break;
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
            case 48001496LL : strd_299600101 = (48001504LL - 48001496LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        goto block128;

block128:
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

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (46665384LL - 46665380LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_128 = 0;
        out_128++;
        if (out_128 <= 333670LL) goto block131;
        else goto block136;


block137:
        int dummy;
    }

    // Interval: 550000000 - 600000000
    {
        int64_t addr_298400101 = 12000064LL;
        int64_t addr_299500101 = 48001496LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001508LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001508LL, strd_299700101 = 0;
        int64_t addr_300600101 = 24000064LL;
        int64_t addr_299500201 = 48001500LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001512LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001512LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36000064LL;
block138:
        goto block139;

block139:
        for(uint64_t loop6 = 0; loop6 < 1336032ULL; loop6++){
            //Loop Indexed
            addr = 6655936LL + (4 * loop6);
            READ_4b(addr);

        }
        goto block144;

block144:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001496LL : strd_299500101 = (48001504LL - 48001496LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001508LL : strd_299600101 = (48001516LL - 48001508LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001508LL : strd_299700101 = (48001516LL - 48001508LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24000068LL - 24000064LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_144 = 0;
        out_144++;
        if (out_144 <= 874656LL) goto block148;
        else goto block149;


block148:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001500LL : strd_299500201 = (48001508LL - 48001500LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001512LL : strd_299600201 = (48001520LL - 48001512LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001512LL : strd_299700201 = (48001520LL - 48001512LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (36000068LL - 36000064LL);

        goto block144;

block149:
        int dummy;
    }

    // Interval: 600000000 - 650000000
    {
        int64_t addr_298400101 = 15498692LL;
        int64_t addr_299500101 = 48001556LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001568LL, strd_299600101 = 0;
        int64_t addr_299500201 = 48001552LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001564LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001564LL, strd_299700201 = 0;
        int64_t addr_300800101 = 39498688LL;
        int64_t addr_299700101 = 48001568LL, strd_299700101 = 0;
        int64_t addr_300600101 = 27498692LL;
block150:
        goto block157;

block159:
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
        addr_300600101 += (27498696LL - 27498692LL);

        goto block157;

block157:
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
        addr_300800101 += (39498692LL - 39498688LL);

        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (15498696LL - 15498692LL);

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

        //Few edges. Don't bother optimizing
        static uint64_t out_157 = 0;
        out_157++;
        if (out_157 <= 1041666LL) goto block159;
        else goto block160;


block160:
        int dummy;
    }

    // Interval: 650000000 - 700000000
    {
        int64_t addr_299700101 = 48001476LL, strd_299700101 = 0;
        int64_t addr_300600101 = 31665356LL;
        int64_t addr_299500201 = 48001592LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001480LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001480LL, strd_299700201 = 0;
        int64_t addr_300800101 = 43665356LL;
        int64_t addr_298400101 = 19665360LL;
        int64_t addr_299500101 = 48001596LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001484LL, strd_299600101 = 0;
block161:
        goto block167;

block167:
        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (31665360LL - 31665356LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
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
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (43665360LL - 43665356LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_167 = 0;
        out_167++;
        if (out_167 <= 1041666LL) goto block170;
        else goto block171;


block170:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (19665364LL - 19665360LL);

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
            case 48001484LL : strd_299600101 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        goto block167;

block171:
        int dummy;
    }

    // Interval: 700000000 - 750000000
    {
        int64_t addr_298400101 = 23832024LL, strd_298400101 = 0;
        int64_t addr_299500101 = 48001504LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001516LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001516LL, strd_299700101 = 0;
        int64_t addr_300600101 = 35832024LL, strd_300600101 = 0;
block172:
        goto block176;

block182:
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
        goto block176;

block177:
        //Small tile
        WRITE_4b(addr_300600101);
        switch(addr_300600101) {
            case 35832024LL : strd_300600101 = (35832028LL - 35832024LL); break;
            case 24000064LL : strd_300600101 = (24000068LL - 24000064LL); break;
            case 36000060LL : strd_300600101 = (24000064LL - 36000060LL); break;
        }
        addr_300600101 += strd_300600101;

        //Few edges. Don't bother optimizing
        static uint64_t out_177 = 0;
        out_177++;
        if (out_177 <= 42009LL) goto block176;
        else if (out_177 <= 42010LL) goto block182;
        else goto block176;


block176:
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
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001504LL : strd_299500101 = (48001512LL - 48001504LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001516LL : strd_299600101 = (48001524LL - 48001516LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001516LL : strd_299700101 = (48001524LL - 48001516LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Few edges. Don't bother optimizing
        static uint64_t out_176 = 0;
        out_176++;
        if (out_176 <= 166660LL) goto block177;
        else goto block183;


block183:
        int dummy;
    }

    // Interval: 750000000 - 800000000
    {
        int64_t addr_300600101 = 24498664LL;
        int64_t addr_299500201 = 48001540LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001552LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001552LL, strd_299700201 = 0;
        int64_t addr_300800101 = 36498664LL;
        int64_t addr_298400101 = 12498668LL;
        int64_t addr_299500101 = 48001544LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001556LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001556LL, strd_299700101 = 0;
block184:
        goto block189;

block189:
        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24498668LL - 24498664LL);

        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001540LL : strd_299500201 = (48001548LL - 48001540LL); break;
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
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001552LL : strd_299600201 = (48001560LL - 48001552LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001552LL : strd_299700201 = (48001560LL - 48001552LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (36498668LL - 36498664LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_189 = 0;
        out_189++;
        if (out_189 <= 1041666LL) goto block193;
        else goto block194;


block193:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12498672LL - 12498668LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500101 = (48001488LL - 48001480LL); break;
            case 48001544LL : strd_299500101 = (48001552LL - 48001544LL); break;
            case 48001476LL : strd_299500101 = (48001484LL - 48001476LL); break;
        }
        addr_299500101 += strd_299500101;

        //Small tile
        READ_4b(addr_299600101);
        switch(addr_299600101) {
            case 48001596LL : strd_299600101 = (48001480LL - 48001596LL); break;
            case 48001556LL : strd_299600101 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299600101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001556LL : strd_299700101 = (48001564LL - 48001556LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        goto block189;

block194:
        int dummy;
    }

    // Interval: 800000000 - 850000000
    {
        int64_t addr_298400101 = 16665332LL;
        int64_t addr_299500101 = 48001576LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001588LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001588LL, strd_299700101 = 0;
        int64_t addr_300600101 = 28665332LL;
        int64_t addr_299500201 = 48001580LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001592LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001592LL, strd_299700201 = 0;
        int64_t addr_300800101 = 40665332LL;
block195:
        goto block200;

block204:
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
        addr_300800101 += (40665336LL - 40665332LL);

        goto block200;

block200:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (16665336LL - 16665332LL);

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
        addr_300600101 += (28665336LL - 28665332LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_200 = 0;
        out_200++;
        if (out_200 <= 1041666LL) goto block204;
        else goto block205;


block205:
        int dummy;
    }

    // Interval: 850000000 - 900000000
    {
        int64_t addr_301500101 = 36000064LL;
        int64_t addr_301700101 = 24000064LL;
        int64_t addr_299500201 = 48001488LL, strd_299500201 = 0;
        int64_t addr_299600201 = 48001500LL, strd_299600201 = 0;
        int64_t addr_299700201 = 48001500LL, strd_299700201 = 0;
        int64_t addr_300800101 = 44831996LL;
        int64_t addr_298400101 = 20832000LL;
        int64_t addr_299500101 = 48001492LL, strd_299500101 = 0;
        int64_t addr_299600101 = 48001504LL, strd_299600101 = 0;
        int64_t addr_299700101 = 48001504LL, strd_299700101 = 0;
        int64_t addr_300600101 = 32832000LL;
block206:
        goto block210;

block210:
        //Small tile
        READ_4b(addr_299500201);
        switch(addr_299500201) {
            case 48001596LL : strd_299500201 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299500201 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299500201 = (48001488LL - 48001480LL); break;
            case 48001488LL : strd_299500201 = (48001496LL - 48001488LL); break;
            case 48001476LL : strd_299500201 = (48001484LL - 48001476LL); break;
        }
        addr_299500201 += strd_299500201;

        //Small tile
        READ_4b(addr_299600201);
        switch(addr_299600201) {
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001500LL : strd_299600201 = (48001508LL - 48001500LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001500LL : strd_299700201 = (48001508LL - 48001500LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        //Small tile
        WRITE_4b(addr_300800101);
        addr_300800101 += (44832000LL - 44831996LL);

        //Few edges. Don't bother optimizing
        static uint64_t out_210 = 0;
        out_210++;
        if (out_210 <= 792016LL) goto block215;
        else goto block218;


block215:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (20832004LL - 20832000LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
            case 48001492LL : strd_299500101 = (48001500LL - 48001492LL); break;
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
            case 48001504LL : strd_299600101 = (48001512LL - 48001504LL); break;
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001504LL : strd_299700101 = (48001512LL - 48001504LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (32832004LL - 32832000LL);

        goto block210;

block218:
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
        static uint64_t out_218 = 0;
        out_218++;
        if (out_218 <= 1497901LL) goto block219;
        else goto block220;


block219:
        //Random
        addr = (bounded_rnd(12000064LL - 64LL) + 64LL) & ~3ULL;
        WRITE_4b(addr);

        goto block218;

block220:
        int dummy;
    }

    // Interval: 900000000 - 944112594
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
block221:
        goto block222;

block234:
        //Small tile
        WRITE_4b(addr_300600101);
        addr_300600101 += (24000068LL - 24000064LL);

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
            case 48001484LL : strd_299600201 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299600201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299600201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299600201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299600201 = (48001484LL - 48001476LL); break;
        }
        addr_299600201 += strd_299600201;

        //Small tile
        WRITE_4b(addr_299700201);
        switch(addr_299700201) {
            case 48001484LL : strd_299700201 = (48001492LL - 48001484LL); break;
            case 48001596LL : strd_299700201 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700201 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700201 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700201 = (48001484LL - 48001476LL); break;
        }
        addr_299700201 += strd_299700201;

        goto block230;

block230:
        //Small tile
        WRITE_4b(addr_298400101);
        addr_298400101 += (12000068LL - 12000064LL);

        //Small tile
        READ_4b(addr_299500101);
        switch(addr_299500101) {
            case 48001596LL : strd_299500101 = (48001480LL - 48001596LL); break;
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
            case 48001476LL : strd_299600101 = (48001484LL - 48001476LL); break;
        }
        addr_299600101 += strd_299600101;

        //Small tile
        WRITE_4b(addr_299700101);
        switch(addr_299700101) {
            case 48001596LL : strd_299700101 = (48001480LL - 48001596LL); break;
            case 48001480LL : strd_299700101 = (48001488LL - 48001480LL); break;
            case 48001592LL : strd_299700101 = (48001476LL - 48001592LL); break;
            case 48001476LL : strd_299700101 = (48001484LL - 48001476LL); break;
        }
        addr_299700101 += strd_299700101;

        //Few edges. Don't bother optimizing
        static uint64_t out_230 = 0;
        out_230++;
        if (out_230 <= 293656LL) goto block234;
        else goto block235;


block226:
        for(uint64_t loop9 = 0; loop9 < 3000000ULL; loop9++){
            //Loop Indexed
            addr = 64LL + (4 * loop9);
            READ_4b(addr);

        }
        goto block230;

block225:
        //Small tile
        READ_4b(addr_301500101);
        addr_301500101 += (41991676LL - 41991672LL);

        //Small tile
        READ_4b(addr_301700101);
        addr_301700101 += (29991676LL - 29991672LL);

        //Random
        addr = (bounded_rnd(24000060LL - 12000064LL) + 12000064LL) & ~3ULL;
        READ_4b(addr);

        goto block222;

block222:
        //Random
        addr = (bounded_rnd(12000052LL - 68LL) + 68LL) & ~3ULL;
        WRITE_4b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_222 = 0;
        out_222++;
        if (out_222 <= 1502098LL) goto block225;
        else goto block226;


block235:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
