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

volatile uint8_t gm[1060936ULL];

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

    int64_t addr_825900101 = 1104LL;
    int64_t addr_611200101 = 851296LL;
    int64_t addr_593100101 = 851296LL;
    int64_t addr_784400101 = 924224LL;
    int64_t addr_785300101 = 924224LL;

    goto block0;

block5214:
    //Few edges. Don't bother optimizing
    static uint64_t out_5214 = 0;
    out_5214++;
    if (out_5214 <= 3000LL) goto block5217;
    else if (out_5214 <= 3001LL) goto block2570;
    else if (out_5214 <= 6001LL) goto block5217;
    else goto block2570;


block5217:
    //Dominant stride
    READ_8b(addr_825900101);
    addr_825900101 += 8LL;
    if(addr_825900101 >= 23296LL) addr_825900101 = 1104LL;

    //Ordered...
    static float out_5217 = 0.0f;
    out_5217 = (out_5217 > 1625.42456055f) ? out_5217 - 1625.42456055 : (out_5217 + 1.0f);
    if (out_5217 <= 1624.42456055f) goto block5217;
    else goto block5214;


block6630:
    goto block1;

block2975:
    for(uint64_t loop2 = 0; loop2 < 3000ULL; loop2++){
        for(uint64_t loop0 = 0; loop0 < 69ULL; loop0++){
            //Loop Indexed
            addr = 8LL + (16 * loop0);
            READ_8b(addr);

            //Loop Indexed
            addr = 0LL + (16 * loop0);
            READ_8b(addr);

            //Loop Indexed
            addr = 23296LL + (276 * loop2) + (4 * loop0);
            WRITE_4b(addr);

            //Loop Indexed
            addr = 23296LL + (276 * loop2) + (4 * loop0);
            READ_4b(addr);

        }
        for(uint64_t loop1 = 0; loop1 < 69ULL; loop1++){
            //Loop Indexed
            addr = 23296LL + (276 * loop2) + (4 * loop1);
            READ_4b(addr);

            //Dominant stride
            READ_4b(addr_784400101);
            addr_784400101 += 12LL;
            if(addr_784400101 >= 984184LL) addr_784400101 = 913440LL;

            //Loop Indexed
            addr = 23296LL + (276 * loop2) + (4 * loop1);
            READ_4b(addr);

            //Dominant stride
            READ_4b(addr_785300101);
            addr_785300101 += 12LL;
            if(addr_785300101 >= 984184LL) addr_785300101 = 913440LL;

        }
    }
    goto block5214;

block2570:
    //Few edges. Don't bother optimizing
    static uint64_t out_2570 = 0;
    out_2570++;
    if (out_2570 <= 2LL) goto block2975;
    else goto block6630;


block981:
    //Small tile
    READ_4b(addr_593100101);
    addr_593100101 += 4LL;

    //Ordered...
    static float out_981 = 0.0f;
    out_981 = (out_981 > 32.44424438f) ? out_981 - 32.44424438 : (out_981 + 1.0f);
    if (out_981 <= 31.41320038f) goto block992;
    else goto block995;


block992:
    //Random
    addr = (bounded_rnd(1456LL) + 1059480LL) & ~7ULL;
    READ_8b(addr);

    //Random
    addr = (bounded_rnd(2888LL) + 1056592LL) & ~7ULL;
    READ_8b(addr);

    //Random
    addr = (bounded_rnd(2904LL) + 1053680LL) & ~7ULL;
    READ_8b(addr);

    //Random
    addr = (bounded_rnd(2904LL) + 1053688LL) & ~7ULL;
    READ_8b(addr);

    //Random
    addr = (bounded_rnd(5768LL) + 1047912LL) & ~7ULL;
    READ_8b(addr);

    //Random
    addr = (bounded_rnd(5768LL) + 1047904LL) & ~7ULL;
    READ_8b(addr);

    goto block995;

block995:
    //Small tile
    WRITE_4b(addr_611200101);
    addr_611200101 += 4LL;

    goto block966;

block959:
    for(uint64_t loop11 = 0; loop11 < 128ULL; loop11++){
        for(uint64_t loop10 = 0; loop10 < 128ULL; loop10++){
            for(uint64_t loop9 = 0; loop9 < 3ULL; loop9++){
                //Loop Indexed
                addr = 851296LL + (1536 * loop11) + (12 * loop10) + (4 * loop9);
                WRITE_4b(addr);

            }
        }
    }
    for(uint64_t loop5 = 0; loop5 < 128ULL; loop5++){
        for(uint64_t loop4 = 0; loop4 < 128ULL; loop4++){
            for(uint64_t loop3 = 0; loop3 < 3ULL; loop3++){
                //Loop Indexed
                addr = 851296LL + (1536 * loop5) + (12 * loop4) + (4 * loop3);
                READ_4b(addr);

            }
        }
    }
    for(uint64_t loop8 = 0; loop8 < 128ULL; loop8++){
        for(uint64_t loop7 = 0; loop7 < 128ULL; loop7++){
            for(uint64_t loop6 = 0; loop6 < 3ULL; loop6++){
                //Loop Indexed
                addr = 851296LL + (1536 * loop8) + (12 * loop7) + (4 * loop6);
                READ_4b(addr);

            }
        }
    }
    goto block964;

block964:
    //Few edges. Don't bother optimizing
    static uint64_t out_964 = 0;
    out_964++;
    if (out_964 <= 128LL) goto block965;
    else goto block2570;


block965:
    //Ordered...
    //Remainder zero for all out blocks...
    static uint64_t out_965 = 0;
    out_965 = (out_965 == 129LL) ? 1 : (out_965 + 1);
    if (out_965 <= 128LL) goto block966;
    else goto block964;


block966:
    //Ordered...
    //Remainder zero for all out blocks...
    static uint64_t out_966 = 0;
    out_966 = (out_966 == 4LL) ? 1 : (out_966 + 1);
    if (out_966 <= 3LL) goto block981;
    else goto block965;


block0:
    goto block959;

block1:
    return 0;
}
