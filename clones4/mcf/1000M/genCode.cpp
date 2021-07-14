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
    uint64_t allocSize = 169463808ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1000000000
    {
        int64_t addr_487800201 = 1695712LL;
        int64_t addr_487600201 = 1695696LL;
        int64_t addr_487500201 = 1695704LL;
        int64_t addr_487800101 = 160890912LL;
        int64_t addr_487600101 = 160890896LL;
        int64_t addr_487500101 = 160890904LL;
        int64_t addr_568000101 = 1163352LL;
        int64_t addr_568200101 = 1163400LL;
        int64_t addr_568700101 = 168841256LL;
        int64_t addr_568300101 = 168841184LL;
        int64_t addr_487400201 = 1163304LL;
        int64_t addr_489600101 = 136LL;
        int64_t addr_487400101 = 160890920LL;
        int64_t addr_568100101 = 168841284LL;
        int64_t addr_489600201 = 136LL;
        int64_t addr_489600301 = 136LL;
        int64_t addr_489600401 = 136LL;
        int64_t addr_488000101 = 136LL;
        int64_t addr_488200101 = 136LL;
        int64_t addr_488400101 = 136LL;
        int64_t addr_502500101 = 144LL, strd_502500101 = 0;
        int64_t addr_503700101 = 136LL;
        int64_t addr_503300101 = 136LL;
        int64_t addr_503500101 = 136LL;
        int64_t addr_488000201 = 136LL;
        int64_t addr_488200201 = 136LL;
        int64_t addr_488400201 = 136LL;
        int64_t addr_502500201 = 144LL, strd_502500201 = 0;
        int64_t addr_503700201 = 136LL;
        int64_t addr_503500201 = 136LL;
        int64_t addr_503300201 = 136LL;
block0:
        goto block1;

block98:
        //Small tile
        READ_8b(addr_502500201);
        switch(addr_502500201) {
            case 528LL : strd_502500201 = (144LL - 528LL); break;
            case 144LL : strd_502500201 = (152LL - 144LL); break;
        }
        addr_502500201 += strd_502500201;

        //Random
        addr = (bounded_rnd(11016LL - 2968LL) + 2968LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160857440LL - 1175256LL) + 1175256LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160857432LL - 1175248LL) + 1175248LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463632LL - 168841184LL) + 168841184LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160857448LL - 1175264LL) + 1175264LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463632LL - 168227376LL) + 168227376LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_98_98 = 28445LL;
        static uint64_t out_98_105 = 2625189LL;
        static uint64_t out_98_67 = 455LL;
        tmpRnd = out_98_98 + out_98_105 + out_98_67;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_98_98)){
                out_98_98--;
                goto block98;
            }
            else if (tmpRnd < (out_98_98 + out_98_105)){
                out_98_105--;
                goto block105;
            }
            else {
                out_98_67--;
                goto block67;
            }
        }
        goto block105;


block105:
        //Dominant stride
        READ_8b(addr_503300201);
        addr_503300201 += 8LL;
        if(addr_503300201 >= 528LL) addr_503300201 = 136LL;

        //Random
        addr = (bounded_rnd(11016LL - 2968LL) + 2968LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_503500201);
        addr_503500201 += 8LL;
        if(addr_503500201 >= 528LL) addr_503500201 = 136LL;

        //Random
        addr = (bounded_rnd(11024LL - 2976LL) + 2976LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_503700201);
        addr_503700201 += 8LL;
        if(addr_503700201 >= 528LL) addr_503700201 = 136LL;

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        RMW_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_105 = 0;
        cov_105++;
        if(cov_105 <= 2578080ULL) {
            static uint64_t out_105 = 0;
            out_105 = (out_105 == 48LL) ? 1 : (out_105 + 1);
            if (out_105 <= 47LL) goto block98;
            else goto block67;
        }
        else if (cov_105 <= 2625233ULL) goto block98;
        else goto block67;

block109:
        //Random
        addr = (bounded_rnd(169463656LL - 168218768LL) + 168218768LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463680LL - 168218792LL) + 168218792LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463632LL - 168218640LL) + 168218640LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(168212440LL - 1163280LL) + 1163280LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_109 = 0;
        cov_109++;
        if(cov_109 <= 2618105ULL) {
            static uint64_t out_109 = 0;
            out_109 = (out_109 == 2LL) ? 1 : (out_109 + 1);
            if (out_109 <= 1LL) goto block110;
            else goto block109;
        }
        else if (cov_109 <= 3062477ULL) goto block109;
        else goto block110;

block110:
        //Random
        addr = (bounded_rnd(169463664LL - 168218776LL) + 168218776LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_110_98 = 270LL;
        static uint64_t out_110_109 = 1490446LL;
        static uint64_t out_110_110 = 1753424LL;
        tmpRnd = out_110_98 + out_110_109 + out_110_110;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_110_98)){
                out_110_98--;
                goto block98;
            }
            else if (tmpRnd < (out_110_98 + out_110_109)){
                out_110_109--;
                goto block109;
            }
            else {
                out_110_110--;
                goto block110;
            }
        }
        goto block98;


block79:
        //Dominant stride
        READ_8b(addr_488000201);
        addr_488000201 += 8LL;
        if(addr_488000201 >= 2824LL) addr_488000201 = 136LL;

        //Random
        addr = (bounded_rnd(11016LL - 2968LL) + 2968LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_488200201);
        addr_488200201 += 8LL;
        if(addr_488200201 >= 2824LL) addr_488200201 = 136LL;

        //Random
        addr = (bounded_rnd(11024LL - 2976LL) + 2976LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_488400201);
        addr_488400201 += 8LL;
        if(addr_488400201 >= 2824LL) addr_488400201 = 136LL;

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        RMW_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_79 = 0;
        cov_79++;
        if(cov_79 <= 2837834ULL) {
            static uint64_t out_79 = 0;
            out_79 = (out_79 == 441LL) ? 1 : (out_79 + 1);
            if (out_79 <= 440LL) goto block67;
            else goto block81;
        }
        else goto block67;

block81:
        //Dominant stride
        READ_8b(addr_489600301);
        addr_489600301 += 8LL;
        if(addr_489600301 >= 2512LL) addr_489600301 = 136LL;

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_81_98 = 9424LL;
        static uint64_t out_81_109 = 54LL;
        static uint64_t out_81_81 = 4284278LL;
        static uint64_t out_81_83 = 836255LL;
        static uint64_t out_81_85 = 2529707LL;
        static uint64_t out_81_89 = 354163LL;
        tmpRnd = out_81_98 + out_81_109 + out_81_81 + out_81_83 + out_81_85 + out_81_89;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_81_98)){
                out_81_98--;
                goto block98;
            }
            else if (tmpRnd < (out_81_98 + out_81_109)){
                out_81_109--;
                goto block109;
            }
            else if (tmpRnd < (out_81_98 + out_81_109 + out_81_81)){
                out_81_81--;
                goto block81;
            }
            else if (tmpRnd < (out_81_98 + out_81_109 + out_81_81 + out_81_83)){
                out_81_83--;
                goto block83;
            }
            else if (tmpRnd < (out_81_98 + out_81_109 + out_81_81 + out_81_83 + out_81_85)){
                out_81_85--;
                goto block85;
            }
            else {
                out_81_89--;
                goto block89;
            }
        }
        goto block85;


block83:
        //Random
        addr = (bounded_rnd(2808LL - 136LL) + 136LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_83_98 = 5730LL;
        static uint64_t out_83_109 = 31LL;
        static uint64_t out_83_81 = 55244LL;
        static uint64_t out_83_83 = 2172251LL;
        static uint64_t out_83_85 = 666219LL;
        static uint64_t out_83_89 = 109030LL;
        tmpRnd = out_83_98 + out_83_109 + out_83_81 + out_83_83 + out_83_85 + out_83_89;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_83_98)){
                out_83_98--;
                goto block98;
            }
            else if (tmpRnd < (out_83_98 + out_83_109)){
                out_83_109--;
                goto block109;
            }
            else if (tmpRnd < (out_83_98 + out_83_109 + out_83_81)){
                out_83_81--;
                goto block81;
            }
            else if (tmpRnd < (out_83_98 + out_83_109 + out_83_81 + out_83_83)){
                out_83_83--;
                goto block83;
            }
            else if (tmpRnd < (out_83_98 + out_83_109 + out_83_81 + out_83_83 + out_83_85)){
                out_83_85--;
                goto block85;
            }
            else {
                out_83_89--;
                goto block89;
            }
        }
        goto block85;


block85:
        //Random
        addr = (bounded_rnd(2232LL - 136LL) + 136LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(2824LL - 144LL) + 144LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_85_98 = 12138LL;
        static uint64_t out_85_109 = 60LL;
        static uint64_t out_85_81 = 46926LL;
        static uint64_t out_85_87 = 2656843LL;
        static uint64_t out_85_89 = 479960LL;
        tmpRnd = out_85_98 + out_85_109 + out_85_81 + out_85_87 + out_85_89;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_85_98)){
                out_85_98--;
                goto block98;
            }
            else if (tmpRnd < (out_85_98 + out_85_109)){
                out_85_109--;
                goto block109;
            }
            else if (tmpRnd < (out_85_98 + out_85_109 + out_85_81)){
                out_85_81--;
                goto block81;
            }
            else if (tmpRnd < (out_85_98 + out_85_109 + out_85_81 + out_85_87)){
                out_85_87--;
                goto block87;
            }
            else {
                out_85_89--;
                goto block89;
            }
        }
        goto block98;


block87:
        //Random
        addr = (bounded_rnd(2816LL - 144LL) + 144LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        goto block81;

block89:
        //Dominant stride
        READ_8b(addr_489600401);
        addr_489600401 += 8LL;
        if(addr_489600401 >= 2440LL) addr_489600401 = 136LL;

        //Random
        addr = (bounded_rnd(11032LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_89_98 = 14742LL;
        static uint64_t out_89_109 = 58LL;
        static uint64_t out_89_81 = 444681LL;
        static uint64_t out_89_89 = 2750934LL;
        static uint64_t out_89_91 = 2523768LL;
        tmpRnd = out_89_98 + out_89_109 + out_89_81 + out_89_89 + out_89_91;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_89_98)){
                out_89_98--;
                goto block98;
            }
            else if (tmpRnd < (out_89_98 + out_89_109)){
                out_89_109--;
                goto block109;
            }
            else if (tmpRnd < (out_89_98 + out_89_109 + out_89_81)){
                out_89_81--;
                goto block81;
            }
            else if (tmpRnd < (out_89_98 + out_89_109 + out_89_81 + out_89_89)){
                out_89_89--;
                goto block89;
            }
            else {
                out_89_91--;
                goto block91;
            }
        }
        goto block91;


block91:
        //Random
        addr = (bounded_rnd(2344LL - 136LL) + 136LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(2504LL - 144LL) + 144LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_91_98 = 11860LL;
        static uint64_t out_91_109 = 68LL;
        static uint64_t out_91_81 = 471742LL;
        static uint64_t out_91_89 = 2040098LL;
        tmpRnd = out_91_98 + out_91_109 + out_91_81 + out_91_89;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_91_98)){
                out_91_98--;
                goto block98;
            }
            else if (tmpRnd < (out_91_98 + out_91_109)){
                out_91_109--;
                goto block109;
            }
            else if (tmpRnd < (out_91_98 + out_91_109 + out_91_81)){
                out_91_81--;
                goto block81;
            }
            else {
                out_91_89--;
                goto block89;
            }
        }
        goto block81;


block48:
        //Dominant stride
        READ_8b(addr_568000101);
        addr_568000101 += -192LL;
        if(addr_568000101 < 1163352LL) addr_568000101 = 2312088LL;

        //Dominant stride
        READ_4b(addr_568100101);
        addr_568100101 += -104LL;
        if(addr_568100101 < 168841284LL) addr_568100101 = 169463516LL;

        //Dominant stride
        READ_8b(addr_568200101);
        addr_568200101 += -192LL;
        if(addr_568200101 < 1163400LL) addr_568200101 = 2312136LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_48 = 0;
        cov_48++;
        if(cov_48 <= 17410840ULL) {
            static uint64_t out_48 = 0;
            out_48 = (out_48 == 62LL) ? 1 : (out_48 + 1);
            if (out_48 <= 8LL) goto block49;
            else goto block50;
        }
        else if (cov_48 <= 17651988ULL) goto block49;
        else goto block50;

block49:
        //Dominant stride
        READ_8b(addr_568700101);
        addr_568700101 += -104LL;
        if(addr_568700101 < 168841256LL) addr_568700101 = 169463488LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_49 = 0;
        out_49++;
        if (out_49 <= 17907119LL) goto block48;
        else goto block67;


block50:
        //Dominant stride
        READ_8b(addr_568300101);
        addr_568300101 += -104LL;
        if(addr_568300101 < 168841184LL) addr_568300101 = 169462688LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_50 = 0;
        cov_50++;
        if(cov_50 <= 14411339ULL) {
            static uint64_t out_50 = 0;
            out_50 = (out_50 == 20LL) ? 1 : (out_50 + 1);
            if (out_50 <= 19LL) goto block49;
            else goto block65;
        }
        else if (cov_50 <= 15034852ULL) goto block65;
        else goto block49;

block65:
        //Random
        addr = (bounded_rnd(84302432LL - 7717144LL) + 7717144LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160887776LL - 7717208LL) + 7717208LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302440LL - 7717152LL) + 7717152LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160887784LL - 7717216LL) + 7717216LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302424LL - 7717136LL) + 7717136LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160887768LL - 7717200LL) + 7717200LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302424LL - 7717136LL) + 7717136LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160887824LL - 7717256LL) + 7717256LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302472LL - 7717184LL) + 7717184LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(160887816LL - 7717248LL) + 7717248LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302432LL - 7717144LL) + 7717144LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302440LL - 7717152LL) + 7717152LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302424LL - 7717136LL) + 7717136LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302480LL - 7717192LL) + 7717192LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(84302472LL - 7717184LL) + 7717184LL) & ~7ULL;
        WRITE_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_65 = 0;
        out_65++;
        if (out_65 <= 1LL) goto block49;
        else if (out_65 <= 12LL) goto block66;
        else if (out_65 <= 13LL) goto block49;
        else if (out_65 <= 93LL) goto block66;
        else if (out_65 <= 94LL) goto block49;
        else if (out_65 <= 122LL) goto block66;
        else if (out_65 <= 123LL) goto block49;
        else goto block66;


block66:
        //Random
        addr = (bounded_rnd(46009800LL - 7717184LL) + 7717184LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_66 = 0;
        cov_66++;
        if(cov_66 <= 1861607ULL) {
            static uint64_t out_66 = 0;
            out_66 = (out_66 == 3LL) ? 1 : (out_66 + 1);
            if (out_66 <= 2LL) goto block49;
            else goto block65;
        }
        else if (cov_66 <= 2477926ULL) goto block65;
        else goto block49;

block67:
        //Dominant stride
        READ_4b(addr_487400201);
        addr_487400201 += 532416LL;
        if(addr_487400201 >= 160887788LL) addr_487400201 = 1163304LL;

        //Unordered
        static uint64_t out_67_81 = 244LL;
        static uint64_t out_67_67 = 121253LL;
        static uint64_t out_67_72 = 29602628LL;
        tmpRnd = out_67_81 + out_67_67 + out_67_72;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_67_81)){
                out_67_81--;
                goto block81;
            }
            else if (tmpRnd < (out_67_81 + out_67_67)){
                out_67_67--;
                goto block67;
            }
            else {
                out_67_72--;
                goto block72;
            }
        }
        goto block111;


block72:
        //Dominant stride
        READ_8b(addr_487500201);
        addr_487500201 += 532416LL;
        if(addr_487500201 >= 160887776LL) addr_487500201 = 1163352LL;

        //Dominant stride
        READ_8b(addr_487600201);
        addr_487600201 += 532416LL;
        if(addr_487600201 >= 160887768LL) addr_487600201 = 1163344LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        READ_8b(addr);

        //Dominant stride
        READ_8b(addr_487800201);
        addr_487800201 += 532416LL;
        if(addr_487800201 >= 160887784LL) addr_487800201 = 1163360LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168222592LL) + 168222592LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_72_79 = 2843659LL;
        static uint64_t out_72_81 = 47488LL;
        static uint64_t out_72_67 = 26543428LL;
        tmpRnd = out_72_79 + out_72_81 + out_72_67;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_72_79)){
                out_72_79--;
                goto block79;
            }
            else if (tmpRnd < (out_72_79 + out_72_81)){
                out_72_81--;
                goto block81;
            }
            else {
                out_72_67--;
                goto block67;
            }
        }
        goto block67;


block23:
        //Dominant stride
        READ_8b(addr_489600201);
        addr_489600201 += 8LL;
        if(addr_489600201 >= 1696LL) addr_489600201 = 136LL;

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_23_23 = 6911846LL;
        static uint64_t out_23_25 = 1125695LL;
        static uint64_t out_23_29 = 71LL;
        static uint64_t out_23_38 = 17132LL;
        static uint64_t out_23_15 = 702380LL;
        tmpRnd = out_23_23 + out_23_25 + out_23_29 + out_23_38 + out_23_15;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_23_23)){
                out_23_23--;
                goto block23;
            }
            else if (tmpRnd < (out_23_23 + out_23_25)){
                out_23_25--;
                goto block25;
            }
            else if (tmpRnd < (out_23_23 + out_23_25 + out_23_29)){
                out_23_29--;
                goto block29;
            }
            else if (tmpRnd < (out_23_23 + out_23_25 + out_23_29 + out_23_38)){
                out_23_38--;
                goto block38;
            }
            else {
                out_23_15--;
                goto block15;
            }
        }
        goto block15;


block25:
        //Random
        addr = (bounded_rnd(1752LL - 136LL) + 136LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_25_23 = 680190LL;
        static uint64_t out_25_25 = 2955721LL;
        static uint64_t out_25_29 = 75LL;
        static uint64_t out_25_38 = 14390LL;
        static uint64_t out_25_15 = 431004LL;
        tmpRnd = out_25_23 + out_25_25 + out_25_29 + out_25_38 + out_25_15;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_25_23)){
                out_25_23--;
                goto block23;
            }
            else if (tmpRnd < (out_25_23 + out_25_25)){
                out_25_25--;
                goto block25;
            }
            else if (tmpRnd < (out_25_23 + out_25_25 + out_25_29)){
                out_25_29--;
                goto block29;
            }
            else if (tmpRnd < (out_25_23 + out_25_25 + out_25_29 + out_25_38)){
                out_25_38--;
                goto block38;
            }
            else {
                out_25_15--;
                goto block15;
            }
        }
        goto block23;


block29:
        //Random
        addr = (bounded_rnd(169463656LL - 168218768LL) + 168218768LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463680LL - 168218792LL) + 168218792LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463632LL - 168218640LL) + 168218640LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(168214680LL - 160890896LL) + 160890896LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_29_29 = 683033LL;
        static uint64_t out_29_31 = 2475067LL;
        static uint64_t out_29_32 = 648649LL;
        tmpRnd = out_29_29 + out_29_31 + out_29_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_29_29)){
                out_29_29--;
                goto block29;
            }
            else if (tmpRnd < (out_29_29 + out_29_31)){
                out_29_31--;
                goto block31;
            }
            else {
                out_29_32--;
                goto block32;
            }
        }
        goto block32;


block31:
        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(169463648LL - 168218760LL) + 168218760LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_31 = 0;
        cov_31++;
        if(cov_31 <= 2021970ULL) {
            static uint64_t out_31 = 0;
            out_31 = (out_31 == 6LL) ? 1 : (out_31 + 1);
            if (out_31 <= 2LL) goto block32;
            else goto block29;
        }
        else if (cov_31 <= 2192467ULL) goto block32;
        else goto block29;

block32:
        //Random
        addr = (bounded_rnd(169463664LL - 168218776LL) + 168218776LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_32_29 = 1492847LL;
        static uint64_t out_32_32 = 2313613LL;
        static uint64_t out_32_38 = 317LL;
        tmpRnd = out_32_29 + out_32_32 + out_32_38;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_32_29)){
                out_32_29--;
                goto block29;
            }
            else if (tmpRnd < (out_32_29 + out_32_32)){
                out_32_32--;
                goto block32;
            }
            else {
                out_32_38--;
                goto block38;
            }
        }
        goto block38;


block38:
        //Small tile
        READ_8b(addr_502500101);
        switch(addr_502500101) {
            case 528LL : strd_502500101 = (144LL - 528LL); break;
            case 248LL : strd_502500101 = (144LL - 248LL); break;
            case 144LL : strd_502500101 = (152LL - 144LL); break;
            case 200LL : strd_502500101 = (144LL - 200LL); break;
            case 288LL : strd_502500101 = (144LL - 288LL); break;
        }
        addr_502500101 += strd_502500101;

        //Random
        addr = (bounded_rnd(8112LL - 2968LL) + 2968LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(167444704LL - 160890904LL) + 160890904LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(167444696LL - 160890896LL) + 160890896LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(167444712LL - 160890912LL) + 160890912LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_38_38 = 46078LL;
        static uint64_t out_38_45 = 3063515LL;
        static uint64_t out_38_1 = 529LL;
        tmpRnd = out_38_38 + out_38_45 + out_38_1;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_38_38)){
                out_38_38--;
                goto block38;
            }
            else if (tmpRnd < (out_38_38 + out_38_45)){
                out_38_45--;
                goto block45;
            }
            else {
                out_38_1--;
                goto block1;
            }
        }
        goto block1;


block45:
        //Dominant stride
        READ_8b(addr_503300101);
        addr_503300101 += 8LL;
        if(addr_503300101 >= 528LL) addr_503300101 = 136LL;

        //Random
        addr = (bounded_rnd(8112LL - 2968LL) + 2968LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_503500101);
        addr_503500101 += 8LL;
        if(addr_503500101 >= 528LL) addr_503500101 = 136LL;

        //Random
        addr = (bounded_rnd(8120LL - 2976LL) + 2976LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_503700101);
        addr_503700101 += 8LL;
        if(addr_503700101 >= 528LL) addr_503700101 = 136LL;

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        RMW_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_45 = 0;
        cov_45++;
        if(cov_45 <= 3021360ULL) {
            static uint64_t out_45 = 0;
            out_45 = (out_45 == 48LL) ? 1 : (out_45 + 1);
            if (out_45 <= 47LL) goto block38;
            else goto block1;
        }
        else goto block38;

block19:
        //Random
        addr = (bounded_rnd(1712LL - 136LL) + 136LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(1856LL - 144LL) + 144LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_19_23 = 478427LL;
        static uint64_t out_19_29 = 73LL;
        static uint64_t out_19_38 = 13747LL;
        static uint64_t out_19_21 = 2432206LL;
        static uint64_t out_19_15 = 100147LL;
        tmpRnd = out_19_23 + out_19_29 + out_19_38 + out_19_21 + out_19_15;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_19_23)){
                out_19_23--;
                goto block23;
            }
            else if (tmpRnd < (out_19_23 + out_19_29)){
                out_19_29--;
                goto block29;
            }
            else if (tmpRnd < (out_19_23 + out_19_29 + out_19_38)){
                out_19_38--;
                goto block38;
            }
            else if (tmpRnd < (out_19_23 + out_19_29 + out_19_38 + out_19_21)){
                out_19_21--;
                goto block21;
            }
            else {
                out_19_15--;
                goto block15;
            }
        }
        goto block38;


block21:
        //Random
        addr = (bounded_rnd(1848LL - 144LL) + 144LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        goto block15;

block17:
        //Random
        addr = (bounded_rnd(1832LL - 136LL) + 136LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_17_23 = 381776LL;
        static uint64_t out_17_29 = 68LL;
        static uint64_t out_17_38 = 12147LL;
        static uint64_t out_17_19 = 945330LL;
        static uint64_t out_17_17 = 3722694LL;
        static uint64_t out_17_15 = 77342LL;
        tmpRnd = out_17_23 + out_17_29 + out_17_38 + out_17_19 + out_17_17 + out_17_15;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_17_23)){
                out_17_23--;
                goto block23;
            }
            else if (tmpRnd < (out_17_23 + out_17_29)){
                out_17_29--;
                goto block29;
            }
            else if (tmpRnd < (out_17_23 + out_17_29 + out_17_38)){
                out_17_38--;
                goto block38;
            }
            else if (tmpRnd < (out_17_23 + out_17_29 + out_17_38 + out_17_19)){
                out_17_19--;
                goto block19;
            }
            else if (tmpRnd < (out_17_23 + out_17_29 + out_17_38 + out_17_19 + out_17_17)){
                out_17_17--;
                goto block17;
            }
            else {
                out_17_15--;
                goto block15;
            }
        }
        goto block19;


block15:
        //Dominant stride
        READ_8b(addr_489600101);
        addr_489600101 += 8LL;
        if(addr_489600101 >= 1776LL) addr_489600101 = 136LL;

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_15_23 = 304853LL;
        static uint64_t out_15_29 = 31LL;
        static uint64_t out_15_38 = 5740LL;
        static uint64_t out_15_19 = 2079263LL;
        static uint64_t out_15_17 = 1416664LL;
        static uint64_t out_15_15 = 8211304LL;
        tmpRnd = out_15_23 + out_15_29 + out_15_38 + out_15_19 + out_15_17 + out_15_15;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_15_23)){
                out_15_23--;
                goto block23;
            }
            else if (tmpRnd < (out_15_23 + out_15_29)){
                out_15_29--;
                goto block29;
            }
            else if (tmpRnd < (out_15_23 + out_15_29 + out_15_38)){
                out_15_38--;
                goto block38;
            }
            else if (tmpRnd < (out_15_23 + out_15_29 + out_15_38 + out_15_19)){
                out_15_19--;
                goto block19;
            }
            else if (tmpRnd < (out_15_23 + out_15_29 + out_15_38 + out_15_19 + out_15_17)){
                out_15_17--;
                goto block17;
            }
            else {
                out_15_15--;
                goto block15;
            }
        }
        goto block19;


block13:
        //Dominant stride
        READ_8b(addr_488000101);
        addr_488000101 += 8LL;
        if(addr_488000101 >= 1856LL) addr_488000101 = 136LL;

        //Random
        addr = (bounded_rnd(8112LL - 2968LL) + 2968LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_488200101);
        addr_488200101 += 8LL;
        if(addr_488200101 >= 1856LL) addr_488200101 = 136LL;

        //Random
        addr = (bounded_rnd(8120LL - 2976LL) + 2976LL) & ~7ULL;
        WRITE_8b(addr);

        //Dominant stride
        READ_8b(addr_488400101);
        addr_488400101 += 8LL;
        if(addr_488400101 >= 1856LL) addr_488400101 = 136LL;

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(8128LL - 2984LL) + 2984LL) & ~7ULL;
        RMW_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_13 = 0;
        cov_13++;
        if(cov_13 <= 5130623ULL) {
            static uint64_t out_13 = 0;
            out_13 = (out_13 == 384LL) ? 1 : (out_13 + 1);
            if (out_13 <= 383LL) goto block1;
            else goto block15;
        }
        else if (cov_13 <= 5130628ULL) goto block15;
        else goto block1;

block6:
        //Dominant stride
        READ_8b(addr_487500101);
        addr_487500101 += 21888LL;
        if(addr_487500101 >= 167444704LL) addr_487500101 = 160890904LL;

        //Dominant stride
        READ_8b(addr_487600101);
        addr_487600101 += 21888LL;
        if(addr_487600101 >= 167444696LL) addr_487600101 = 160890896LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        READ_8b(addr);

        //Dominant stride
        READ_8b(addr_487800101);
        addr_487800101 += 21888LL;
        if(addr_487800101 >= 167444712LL) addr_487800101 = 160890912LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_6_15 = 33184LL;
        static uint64_t out_6_13 = 5140567LL;
        static uint64_t out_6_1 = 13225217LL;
        tmpRnd = out_6_15 + out_6_13 + out_6_1;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_6_15)){
                out_6_15--;
                goto block15;
            }
            else if (tmpRnd < (out_6_15 + out_6_13)){
                out_6_13--;
                goto block13;
            }
            else {
                out_6_1--;
                goto block1;
            }
        }
        goto block48;


block1:
        //Dominant stride
        READ_4b(addr_487400101);
        addr_487400101 += 21888LL;
        if(addr_487400101 >= 167444716LL) addr_487400101 = 160890920LL;

        //Unordered
        static uint64_t out_1_15 = 16926LL;
        static uint64_t out_1_6 = 18398964LL;
        static uint64_t out_1_1 = 2062812LL;
        tmpRnd = out_1_15 + out_1_6 + out_1_1;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_1_15)){
                out_1_15--;
                goto block15;
            }
            else if (tmpRnd < (out_1_15 + out_1_6)){
                out_1_6--;
                goto block6;
            }
            else {
                out_1_1--;
                goto block1;
            }
        }
        goto block6;


block111:
        int dummy;
    }

    // Interval: 1000000000 - 1339644213
    {
        int64_t addr_487500201 = 91626136LL;
        int64_t addr_487600201 = 91626128LL;
        int64_t addr_487800201 = 91626144LL;
        int64_t addr_568200201 = 12424LL;
        int64_t addr_568000201 = 12376LL;
        int64_t addr_568700201 = 168841256LL;
        int64_t addr_487400201 = 92158568LL;
        int64_t addr_568300201 = 168841184LL;
block112:
        goto block117;

block122:
        //Dominant stride
        READ_8b(addr_568300201);
        addr_568300201 += -104LL;
        if(addr_568300201 < 168841184LL) addr_568300201 = 169462688LL;

        goto block121;

block121:
        //Dominant stride
        READ_8b(addr_568700201);
        addr_568700201 += -104LL;
        if(addr_568700201 < 168841256LL) addr_568700201 = 169463488LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_121 = 0;
        out_121++;
        if (out_121 <= 17907119LL) goto block120;
        else goto block123;


block120:
        //Dominant stride
        READ_8b(addr_568000201);
        addr_568000201 += -192LL;
        if(addr_568000201 < 12376LL) addr_568000201 = 1161112LL;

        //Dominant stride
        READ_8b(addr_568200201);
        addr_568200201 += -192LL;
        if(addr_568200201 < 12424LL) addr_568200201 = 1161160LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_120 = 0;
        cov_120++;
        if(cov_120 <= 17410840ULL) {
            static uint64_t out_120 = 0;
            out_120 = (out_120 == 62LL) ? 1 : (out_120 + 1);
            if (out_120 <= 8LL) goto block121;
            else goto block122;
        }
        else if (cov_120 <= 17651988ULL) goto block121;
        else goto block122;

block118:
        //Dominant stride
        READ_4b(addr_487400201);
        addr_487400201 += 532416LL;
        if(addr_487400201 >= 160887788LL) addr_487400201 = 1163304LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_118 = 0;
        cov_118++;
        if(cov_118 <= 31752704ULL) {
            static uint64_t out_118 = 0;
            out_118 = (out_118 == 215LL) ? 1 : (out_118 + 1);
            if (out_118 <= 214LL) goto block117;
            else goto block118;
        }
        else if (cov_118 <= 31757331ULL) goto block118;
        else goto block117;

block117:
        //Dominant stride
        READ_8b(addr_487500201);
        addr_487500201 += 532416LL;
        if(addr_487500201 >= 160887776LL) addr_487500201 = 1163352LL;

        //Dominant stride
        READ_8b(addr_487600201);
        addr_487600201 += 532416LL;
        if(addr_487600201 >= 160887768LL) addr_487600201 = 1163344LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168218744LL) + 168218744LL) & ~7ULL;
        READ_8b(addr);

        //Dominant stride
        READ_8b(addr_487800201);
        addr_487800201 += 532416LL;
        if(addr_487800201 >= 160887784LL) addr_487800201 = 1163360LL;

        //Random
        addr = (bounded_rnd(169463632LL - 168222592LL) + 168222592LL) & ~7ULL;
        READ_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_117 = 0;
        out_117++;
        if (out_117 <= 31686165LL) goto block118;
        else goto block120;


block123:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
