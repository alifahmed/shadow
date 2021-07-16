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
    uint64_t allocSize = 31563776ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 611250837
    {
        int64_t addr_717900101 = 9367056LL;
        int64_t addr_722200101 = 17350672LL;
        int64_t addr_720500101 = 31358992LL, strd_720500101 = 0;
        int64_t addr_731000101 = 27753992LL;
        int64_t addr_731200101 = 27753984LL;
        int64_t addr_733400101 = 27754000LL;
        int64_t addr_733600101 = 27753984LL;
        int64_t addr_733800101 = 27753984LL;
block0:
        goto block3;

block123:
        //Dominant stride
        READ_4b(addr_722200101);
        addr_722200101 += 4LL;
        if(addr_722200101 >= 22150096LL) addr_722200101 = 17350672LL;

        //Random
        addr = (bounded_rnd(31157584LL - 30957584LL) + 30957584LL) & ~0ULL;
        READ_1b(addr);

        //Unordered
        static uint64_t out_123_123 = 674029LL;
        static uint64_t out_123_125 = 387366LL;
        static uint64_t out_123_126 = 1LL;
        static uint64_t out_123_120 = 138459LL;
        tmpRnd = out_123_123 + out_123_125 + out_123_126 + out_123_120;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_123_123)){
                out_123_123--;
                goto block123;
            }
            else if (tmpRnd < (out_123_123 + out_123_125)){
                out_123_125--;
                goto block125;
            }
            else if (tmpRnd < (out_123_123 + out_123_125 + out_123_126)){
                out_123_126--;
                goto block126;
            }
            else {
                out_123_120--;
                goto block120;
            }
        }
        goto block120;


block125:
        //Random
        addr = (bounded_rnd(22951184LL - 22151188LL) + 22151188LL) & ~3ULL;
        WRITE_4b(addr);

        //Random
        addr = (bounded_rnd(31358288LL - 31158289LL) + 31158289LL) & ~0ULL;
        WRITE_1b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_125 = 0;
        cov_125++;
        if(cov_125 <= 353729ULL) {
            static uint64_t out_125 = 0;
            out_125 = (out_125 == 6LL) ? 1 : (out_125 + 1);
            if (out_125 <= 5LL) goto block123;
            else goto block120;
        }
        else if (cov_125 <= 356314ULL) goto block120;
        else goto block123;

block126:
        for(uint64_t loop0 = 0; loop0 < 200000ULL; loop0++){
            //Loop Indexed
            addr = 31158288LL + (1 * loop0);
            READ_1b(addr);

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_126 = 0;
        out_126++;
        if (out_126 <= 9LL) goto block120;
        else goto block127;


block127:
        for(uint64_t loop1 = 0; loop1 < 200000ULL; loop1++){
            //Loop Indexed
            addr = 22151184LL + (4 * loop1);
            READ_4b(addr);

        }
        goto block135;

block135:
        //Small tile
        READ_8b(addr_731000101);
        addr_731000101 += (27753968LL - 27753992LL);

        //Small tile
        READ_8b(addr_731200101);
        addr_731200101 += (27753960LL - 27753984LL);

        //Small tile
        READ_8b(addr_733400101);
        addr_733400101 += (27753976LL - 27754000LL);

        //Small tile
        READ_8b(addr_733600101);
        addr_733600101 += (27753960LL - 27753984LL);

        //Small tile
        READ_8b(addr_733800101);
        addr_733800101 += (27753960LL - 27753984LL);

        //Random
        addr = (bounded_rnd(17350480LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17350480LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17350496LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_135 = 0;
        cov_135++;
        if(cov_135 <= 180160ULL) {
            static uint64_t out_135 = 0;
            out_135 = (out_135 == 10LL) ? 1 : (out_135 + 1);
            if (out_135 <= 1LL) goto block135;
            else goto block137;
        }
        else if (cov_135 <= 182205ULL) goto block135;
        else goto block137;

block137:
        //Random
        addr = (bounded_rnd(17350256LL - 3848LL) + 3848LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17350184LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_137 = 0;
        out_137++;
        if (out_137 <= 179938LL) goto block135;
        else goto block138;


block76:
        //Random
        addr = (bounded_rnd(17206784LL - 3840LL) + 3840LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(17206816LL - 3840LL) + 3840LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(17350272LL - 3840LL) + 3840LL) & ~31ULL;
        WRITE_32b(addr);

        //Random
        addr = (bounded_rnd(17350304LL - 3840LL) + 3840LL) & ~31ULL;
        WRITE_32b(addr);

        goto block34;

block80:
        //Random
        addr = (bounded_rnd(17200096LL - 4160LL) + 4160LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(17200128LL - 4160LL) + 4160LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(17350496LL - 3744LL) + 3744LL) & ~31ULL;
        WRITE_32b(addr);

        //Random
        addr = (bounded_rnd(17350496LL - 3744LL) + 3744LL) & ~31ULL;
        WRITE_32b(addr);

        goto block44;

block82:
        //Random
        addr = (bounded_rnd(15855872LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(15855800LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block37;

block84:
        //Random
        addr = (bounded_rnd(15365968LL - 3816LL) + 3816LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(15365896LL - 3792LL) + 3792LL) & ~7ULL;
        WRITE_8b(addr);

        goto block16;

block91:
        //Random
        addr = (bounded_rnd(10471536LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10471544LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10471584LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(31562752LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(10471536LL - 3752LL) + 3752LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(10471552LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(10471576LL - 3808LL) + 3808LL) & ~7ULL;
        WRITE_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_91 = 0;
        cov_91++;
        if(cov_91 <= 49282ULL) {
            static uint64_t out_91 = 0;
            out_91 = (out_91 == 601LL) ? 1 : (out_91 + 1);
            if (out_91 <= 600LL) goto block91;
            else goto block95;
        }
        else if (cov_91 <= 49312ULL) goto block91;
        else goto block95;

block95:
        //Random
        addr = (bounded_rnd(10472816LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10472864LL - 3816LL) + 3816LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10472856LL - 3808LL) + 3808LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10472832LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_95_95 = 583LL;
        static uint64_t out_95_96 = 46245LL;
        static uint64_t out_95_13 = 76LL;
        tmpRnd = out_95_95 + out_95_96 + out_95_13;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_95_95)){
                out_95_95--;
                goto block95;
            }
            else if (tmpRnd < (out_95_95 + out_95_96)){
                out_95_96--;
                goto block96;
            }
            else {
                out_95_13--;
                goto block13;
            }
        }
        goto block96;


block96:
        //Random
        addr = (bounded_rnd(10472832LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Unordered
        static uint64_t out_96_95 = 43722LL;
        static uint64_t out_96_13 = 2359LL;
        static uint64_t out_96_10 = 281LL;
        tmpRnd = out_96_95 + out_96_13 + out_96_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_96_95)){
                out_96_95--;
                goto block95;
            }
            else if (tmpRnd < (out_96_95 + out_96_13)){
                out_96_13--;
                goto block13;
            }
            else {
                out_96_10--;
                goto block10;
            }
        }
        goto block10;


block103:
        //Random
        addr = (bounded_rnd(11765952LL - 3816LL) + 3816LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11765960LL - 3824LL) + 3824LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11766032LL - 3848LL) + 3848LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(31562752LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(11765952LL - 3752LL) + 3752LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(11765968LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(11766024LL - 3840LL) + 3840LL) & ~7ULL;
        WRITE_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_103 = 0;
        cov_103++;
        if(cov_103 <= 56925ULL) {
            static uint64_t out_103 = 0;
            out_103 = (out_103 == 495LL) ? 1 : (out_103 + 1);
            if (out_103 <= 494LL) goto block103;
            else goto block109;
        }
        else if (cov_103 <= 56993ULL) goto block103;
        else goto block109;

block109:
        //Random
        addr = (bounded_rnd(11765952LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11766032LL - 3848LL) + 3848LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11766024LL - 3840LL) + 3840LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11765968LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(31562744LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(11765960LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Few edges. Don't bother optimizing
        static uint64_t out_109 = 0;
        out_109++;
        if (out_109 <= 45523LL) goto block110;
        else if (out_109 <= 45524LL) goto block32;
        else goto block110;


block110:
        //Random
        addr = (bounded_rnd(31562744LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_110_109 = 862LL;
        static uint64_t out_110_112 = 62459LL;
        static uint64_t out_110_32 = 108LL;
        tmpRnd = out_110_109 + out_110_112 + out_110_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_110_109)){
                out_110_109--;
                goto block109;
            }
            else if (tmpRnd < (out_110_109 + out_110_112)){
                out_110_112--;
                goto block112;
            }
            else {
                out_110_32--;
                goto block32;
            }
        }
        goto block112;


block112:
        //Random
        addr = (bounded_rnd(11765968LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(31563056LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_112_109 = 59399LL;
        static uint64_t out_112_29 = 940LL;
        static uint64_t out_112_32 = 2255LL;
        tmpRnd = out_112_109 + out_112_29 + out_112_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_112_109)){
                out_112_109--;
                goto block109;
            }
            else if (tmpRnd < (out_112_109 + out_112_29)){
                out_112_29--;
                goto block29;
            }
            else {
                out_112_32--;
                goto block32;
            }
        }
        goto block32;


block119:
        for(uint64_t loop2 = 0; loop2 < 200000ULL; loop2++){
            //Loop Indexed
            addr = 22954016LL + (24 * loop2);
            READ_8b(addr);

            //Loop Indexed
            addr = 22954008LL + (24 * loop2);
            READ_8b(addr);

            //Loop Indexed
            addr = 27754512LL + (16 * loop2);
            WRITE_8b(addr);

            //Loop Indexed
            addr = 27754520LL + (16 * loop2);
            WRITE_8b(addr);

        }
        for(uint64_t loop3 = 0; loop3 < 1199856ULL; loop3++){
            //Dominant stride
            READ_8b(addr_717900101);
            addr_717900101 += 8LL;
            if(addr_717900101 >= 17350536LL) addr_717900101 = 3760LL;

            //Loop Indexed
            addr = 17350672LL + (4 * loop3);
            WRITE_4b(addr);

        }
        for(uint64_t loop4 = 0; loop4 < 200000ULL; loop4++){
            //Loop Indexed
            addr = 22151184LL + (4 * loop4);
            WRITE_4b(addr);

        }
        goto block120;

block120:
        //Small tile
        READ_1b(addr_720500101);
        switch(addr_720500101) {
            case 31358992LL : strd_720500101 = (31358993LL - 31358992LL); break;
            case 31558991LL : strd_720500101 = (31358992LL - 31558991LL); break;
        }
        addr_720500101 += strd_720500101;

        //Unordered
        static uint64_t out_120_126 = 8LL;
        static uint64_t out_120_120 = 1799991LL;
        static uint64_t out_120_121 = 200000LL;
        tmpRnd = out_120_126 + out_120_120 + out_120_121;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_120_126)){
                out_120_126--;
                goto block126;
            }
            else if (tmpRnd < (out_120_126 + out_120_120)){
                out_120_120--;
                goto block120;
            }
            else {
                out_120_121--;
                goto block121;
            }
        }
        goto block126;


block121:
        //Random
        addr = (bounded_rnd(30954504LL - 27754512LL) + 27754512LL) & ~7ULL;
        READ_8b(addr);

        goto block123;

block48:
        //Random
        addr = (bounded_rnd(17206776LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17206784LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        goto block33;

block52:
        //Random
        addr = (bounded_rnd(6273232LL - 3792LL) + 3792LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(6273232LL - 3792LL) + 3792LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(10472880LL - 3856LL) + 3856LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(10472880LL - 3856LL) + 3856LL) & ~15ULL;
        WRITE_16b(addr);

        goto block44;

block53:
        //Random
        addr = (bounded_rnd(17350536LL - 3800LL) + 3800LL) & ~7ULL;
        WRITE_8b(addr);

        goto block16;

block57:
        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17321568LL - 3880LL) + 3880LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_57_9 = 149848LL;
        static uint64_t out_57_6 = 75190LL;
        tmpRnd = out_57_9 + out_57_6;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_57_9)){
                out_57_9--;
                goto block9;
            }
            else {
                out_57_6--;
                goto block6;
            }
        }
        goto block119;


block61:
        //Random
        addr = (bounded_rnd(6264712LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(6264712LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(6273224LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(6273224LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block34;

block64:
        //Random
        addr = (bounded_rnd(17206768LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17206768LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17206784LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_64 = 0;
        cov_64++;
        if(cov_64 <= 220975ULL) {
            static uint64_t out_64 = 0;
            out_64 = (out_64 == 7LL) ? 1 : (out_64 + 1);
            if (out_64 <= 6LL) goto block66;
            else goto block82;
        }
        else if (cov_64 <= 236832ULL) goto block82;
        else goto block66;

block66:
        //Random
        addr = (bounded_rnd(17206784LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17206776LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block37;

block68:
        //Random
        addr = (bounded_rnd(17173320LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17173328LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        goto block14;

block72:
        //Random
        addr = (bounded_rnd(6266704LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(6266704LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(10472832LL - 4176LL) + 4176LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(10472832LL - 4176LL) + 4176LL) & ~15ULL;
        WRITE_16b(addr);

        goto block34;

block28:
        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_28_109 = 3186LL;
        static uint64_t out_28_48 = 236983LL;
        static uint64_t out_28_29 = 123588LL;
        static uint64_t out_28_32 = 11129LL;
        tmpRnd = out_28_109 + out_28_48 + out_28_29 + out_28_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_28_109)){
                out_28_109--;
                goto block109;
            }
            else if (tmpRnd < (out_28_109 + out_28_48)){
                out_28_48--;
                goto block48;
            }
            else if (tmpRnd < (out_28_109 + out_28_48 + out_28_29)){
                out_28_29--;
                goto block29;
            }
            else {
                out_28_32--;
                goto block32;
            }
        }
        goto block29;


block29:
        //Random
        addr = (bounded_rnd(17350256LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_29_103 = 121LL;
        static uint64_t out_29_29 = 4LL;
        static uint64_t out_29_31 = 123701LL;
        static uint64_t out_29_32 = 64LL;
        tmpRnd = out_29_103 + out_29_29 + out_29_31 + out_29_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_29_103)){
                out_29_103--;
                goto block103;
            }
            else if (tmpRnd < (out_29_103 + out_29_29)){
                out_29_29--;
                goto block29;
            }
            else if (tmpRnd < (out_29_103 + out_29_29 + out_29_31)){
                out_29_31--;
                goto block31;
            }
            else {
                out_29_32--;
                goto block32;
            }
        }
        goto block31;


block31:
        //Random
        addr = (bounded_rnd(17350256LL - 3784LL) + 3784LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17350400LL - 3816LL) + 3816LL) & ~7ULL;
        WRITE_8b(addr);

        goto block32;

block32:
        //Random
        addr = (bounded_rnd(17350256LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        goto block33;

block33:
        //Random
        addr = (bounded_rnd(17350328LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_33_76 = 91656LL;
        static uint64_t out_33_61 = 83668LL;
        static uint64_t out_33_72 = 62852LL;
        static uint64_t out_33_34 = 136686LL;
        tmpRnd = out_33_76 + out_33_61 + out_33_72 + out_33_34;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_33_76)){
                out_33_76--;
                goto block76;
            }
            else if (tmpRnd < (out_33_76 + out_33_61)){
                out_33_61--;
                goto block61;
            }
            else if (tmpRnd < (out_33_76 + out_33_61 + out_33_72)){
                out_33_72--;
                goto block72;
            }
            else {
                out_33_34--;
                goto block34;
            }
        }
        goto block76;


block34:
        //Random
        addr = (bounded_rnd(27754008LL - 22954024LL) + 22954024LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_34 = 0;
        cov_34++;
        if(cov_34 <= 350370ULL) {
            static uint64_t out_34 = 0;
            out_34 = (out_34 == 6LL) ? 1 : (out_34 + 1);
            if (out_34 <= 2LL) goto block37;
            else goto block64;
        }
        else if (cov_34 <= 370266ULL) goto block37;
        else goto block64;

block37:
        //Random
        addr = (bounded_rnd(27753992LL - 22954008LL) + 22954008LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(27754008LL - 22954024LL) + 22954024LL) & ~7ULL;
        WRITE_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_37 = 0;
        cov_37++;
        if(cov_37 <= 337935ULL) {
            static uint64_t out_37 = 0;
            out_37 = (out_37 == 3LL) ? 1 : (out_37 + 1);
            if (out_37 <= 2LL) goto block9;
            else goto block6;
        }
        else if (cov_37 <= 362725ULL) goto block9;
        else goto block6;

block41:
        //Random
        addr = (bounded_rnd(6266696LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(6266696LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(6273224LL - 3792LL) + 3792LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(6273224LL - 3792LL) + 3792LL) & ~7ULL;
        WRITE_8b(addr);

        goto block44;

block44:
        //Random
        addr = (bounded_rnd(17200064LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17200064LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17200080LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_44 = 0;
        cov_44++;
        if(cov_44 <= 300444ULL) {
            static uint64_t out_44 = 0;
            out_44 = (out_44 == 6LL) ? 1 : (out_44 + 1);
            if (out_44 <= 5LL) goto block46;
            else goto block84;
        }
        else if (cov_44 <= 314412ULL) goto block46;
        else goto block84;

block46:
        //Random
        addr = (bounded_rnd(17200080LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17200072LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block16;

block16:
        //Random
        addr = (bounded_rnd(27754000LL - 22954016LL) + 22954016LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(27754008LL - 22954024LL) + 22954024LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_16 = 0;
        cov_16++;
        if(cov_16 <= 538185ULL) {
            static uint64_t out_16 = 0;
            out_16 = (out_16 == 5LL) ? 1 : (out_16 + 1);
            if (out_16 <= 3LL) goto block28;
            else goto block57;
        }
        else if (cov_16 <= 590163ULL) goto block28;
        else goto block57;

block14:
        //Random
        addr = (bounded_rnd(17350520LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_14_80 = 83789LL;
        static uint64_t out_14_52 = 133812LL;
        static uint64_t out_14_41 = 116332LL;
        static uint64_t out_14_16 = 63314LL;
        tmpRnd = out_14_80 + out_14_52 + out_14_41 + out_14_16;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_14_80)){
                out_14_80--;
                goto block80;
            }
            else if (tmpRnd < (out_14_80 + out_14_52)){
                out_14_52--;
                goto block52;
            }
            else if (tmpRnd < (out_14_80 + out_14_52 + out_14_41)){
                out_14_41--;
                goto block41;
            }
            else {
                out_14_16--;
                goto block16;
            }
        }
        goto block80;


block13:
        //Random
        addr = (bounded_rnd(17350480LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        goto block14;

block12:
        //Random
        addr = (bounded_rnd(17350480LL - 3752LL) + 3752LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17350560LL - 3784LL) + 3784LL) & ~7ULL;
        WRITE_8b(addr);

        goto block13;

block10:
        //Random
        addr = (bounded_rnd(17350480LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_10_91 = 84LL;
        static uint64_t out_10_13 = 64LL;
        static uint64_t out_10_12 = 152000LL;
        static uint64_t out_10_10 = 6LL;
        tmpRnd = out_10_91 + out_10_13 + out_10_12 + out_10_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_10_91)){
                out_10_91--;
                goto block91;
            }
            else if (tmpRnd < (out_10_91 + out_10_13)){
                out_10_13--;
                goto block13;
            }
            else if (tmpRnd < (out_10_91 + out_10_13 + out_10_12)){
                out_10_12--;
                goto block12;
            }
            else {
                out_10_10--;
                goto block10;
            }
        }
        goto block12;


block9:
        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        WRITE_4b(addr);

        //Unordered
        static uint64_t out_9_95 = 2633LL;
        static uint64_t out_9_53 = 202677LL;
        static uint64_t out_9_68 = 229905LL;
        static uint64_t out_9_13 = 12530LL;
        static uint64_t out_9_10 = 152181LL;
        tmpRnd = out_9_95 + out_9_53 + out_9_68 + out_9_13 + out_9_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_9_95)){
                out_9_95--;
                goto block95;
            }
            else if (tmpRnd < (out_9_95 + out_9_53)){
                out_9_53--;
                goto block53;
            }
            else if (tmpRnd < (out_9_95 + out_9_53 + out_9_68)){
                out_9_68--;
                goto block68;
            }
            else if (tmpRnd < (out_9_95 + out_9_53 + out_9_68 + out_9_13)){
                out_9_13--;
                goto block13;
            }
            else {
                out_9_10--;
                goto block10;
            }
        }
        goto block53;


block3:
        for(uint64_t loop5 = 0; loop5 < 200000ULL; loop5++){
            //Loop Indexed
            addr = 22954008LL + (24 * loop5);
            WRITE_8b(addr);

            //Loop Indexed
            addr = 22954016LL + (24 * loop5);
            WRITE_8b(addr);

            //Loop Indexed
            addr = 22954024LL + (24 * loop5);
            WRITE_8b(addr);

        }
        goto block6;

block6:
        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(31560256LL - 31560132LL) + 31560132LL) & ~3ULL;
        WRITE_4b(addr);

        goto block9;

block138:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
