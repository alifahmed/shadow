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
    uint64_t allocSize = 405504ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1000000000
    {
        int64_t addr_678400101 = 10992LL, strd_678400101 = 0;
        int64_t addr_678500101 = 34336LL;
        int64_t addr_678700101 = 34388LL;
        int64_t addr_678800101 = 11112LL, strd_678800101 = 0;
        int64_t addr_678900101 = 50720LL;
        int64_t addr_679000101 = 34388LL;
        int64_t addr_679100101 = 11192LL, strd_679100101 = 0;
        int64_t addr_679200101 = 67104LL;
        int64_t addr_679500101 = 34388LL;
        int64_t addr_679600101 = 13460LL, strd_679600101 = 0;
        int64_t addr_679800101 = 34388LL;
        int64_t addr_679900101 = 11460LL;
        int64_t addr_680000101 = 34388LL;
        int64_t addr_680700101 = 67156LL;
        int64_t addr_680300101 = 67156LL;
        int64_t addr_680500101 = 34384LL;
        int64_t addr_680400101 = 11072LL, strd_680400101 = 0;
        int64_t addr_680200101 = 67152LL;
        int64_t addr_680100101 = 11232LL, strd_680100101 = 0;
        int64_t addr_648500101 = 404276LL;
        int64_t addr_681000101 = 11036LL, strd_681000101 = 0;
        int64_t addr_681100101 = 34340LL;
        int64_t addr_681300101 = 50772LL;
        int64_t addr_681400101 = 11156LL, strd_681400101 = 0;
        int64_t addr_681500101 = 50724LL;
        int64_t addr_681600101 = 50772LL;
        int64_t addr_681700101 = 12516LL;
        int64_t addr_681800101 = 50772LL;
        int64_t addr_675900101 = 24776LL;
        int64_t addr_676000101 = 24768LL;
        int64_t addr_676200101 = 19304LL;
        int64_t addr_676100101 = 22040LL;
        int64_t addr_675300101 = 16560LL;
        int64_t addr_676300101 = 19296LL;
        int64_t addr_676700101 = 22032LL;
block0:
        goto block2;

block25:
        //Small tile
        READ_4b(addr_678400101);
        switch(addr_678400101) {
            case 10992LL : strd_678400101 = (10996LL - 10992LL); break;
            case 11028LL : strd_678400101 = (10992LL - 11028LL); break;
        }
        addr_678400101 += strd_678400101;

        //Dominant stride
        READ_4b(addr_678500101);
        addr_678500101 += 4LL;
        if(addr_678500101 >= 346856LL) addr_678500101 = 34336LL;

        //Dominant stride
        WRITE_4b(addr_678700101);
        addr_678700101 += 4LL;
        if(addr_678700101 >= 346908LL) addr_678700101 = 34388LL;

        //Small tile
        READ_4b(addr_678800101);
        switch(addr_678800101) {
            case 11112LL : strd_678800101 = (11116LL - 11112LL); break;
            case 11148LL : strd_678800101 = (11112LL - 11148LL); break;
        }
        addr_678800101 += strd_678800101;

        //Dominant stride
        READ_4b(addr_678900101);
        addr_678900101 += 4LL;
        if(addr_678900101 >= 396120LL) addr_678900101 = 50720LL;

        //Dominant stride
        WRITE_4b(addr_679000101);
        addr_679000101 += 4LL;
        if(addr_679000101 >= 346908LL) addr_679000101 = 34388LL;

        //Small tile
        READ_4b(addr_679100101);
        switch(addr_679100101) {
            case 11192LL : strd_679100101 = (11196LL - 11192LL); break;
            case 11228LL : strd_679100101 = (11192LL - 11228LL); break;
        }
        addr_679100101 += strd_679100101;

        //Dominant stride
        READ_4b(addr_679200101);
        addr_679200101 += 4LL;
        if(addr_679200101 >= 334824LL) addr_679200101 = 21456LL;

        //Dominant stride
        WRITE_4b(addr_679500101);
        addr_679500101 += 4LL;
        if(addr_679500101 >= 346908LL) addr_679500101 = 34388LL;

        //Small tile
        READ_4b(addr_679600101);
        switch(addr_679600101) {
            case 13460LL : strd_679600101 = (13464LL - 13460LL); break;
            case 13496LL : strd_679600101 = (13460LL - 13496LL); break;
        }
        addr_679600101 += strd_679600101;

        //Dominant stride
        WRITE_4b(addr_679800101);
        addr_679800101 += 4LL;
        if(addr_679800101 >= 346908LL) addr_679800101 = 34388LL;

        //Dominant stride
        READ_4b(addr_679900101);
        addr_679900101 += 4LL;
        if(addr_679900101 >= 12160LL) addr_679900101 = 11284LL;

        //Dominant stride
        WRITE_4b(addr_680000101);
        addr_680000101 += 4LL;
        if(addr_680000101 >= 346908LL) addr_680000101 = 34388LL;

        //Few edges. Don't bother optimizing
        static uint64_t out_25 = 0;
        out_25++;
        if (out_25 <= 20217004LL) goto block31;
        else goto block42;


block31:
        //Small tile
        READ_4b(addr_680100101);
        switch(addr_680100101) {
            case 11268LL : strd_680100101 = (11232LL - 11268LL); break;
            case 11232LL : strd_680100101 = (11236LL - 11232LL); break;
        }
        addr_680100101 += strd_680100101;

        //Dominant stride
        READ_4b(addr_680200101);
        addr_680200101 += 4LL;
        if(addr_680200101 >= 334872LL) addr_680200101 = 21504LL;

        //Dominant stride
        WRITE_4b(addr_680300101);
        addr_680300101 += 4LL;
        if(addr_680300101 >= 334876LL) addr_680300101 = 21508LL;

        //Small tile
        READ_4b(addr_680400101);
        switch(addr_680400101) {
            case 11072LL : strd_680400101 = (11076LL - 11072LL); break;
            case 11108LL : strd_680400101 = (11072LL - 11108LL); break;
        }
        addr_680400101 += strd_680400101;

        //Dominant stride
        READ_4b(addr_680500101);
        addr_680500101 += 4LL;
        if(addr_680500101 >= 346904LL) addr_680500101 = 34384LL;

        //Dominant stride
        WRITE_4b(addr_680700101);
        addr_680700101 += 4LL;
        if(addr_680700101 >= 334876LL) addr_680700101 = 21508LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_31 = 0;
        cov_31++;
        if(cov_31 <= 18195308ULL) {
            static uint64_t out_31 = 0;
            out_31 = (out_31 == 9LL) ? 1 : (out_31 + 1);
            if (out_31 <= 8LL) goto block39;
            else goto block41;
        }
        else goto block39;

block39:
        //Small tile
        READ_4b(addr_681000101);
        switch(addr_681000101) {
            case 11068LL : strd_681000101 = (11036LL - 11068LL); break;
            case 11036LL : strd_681000101 = (11040LL - 11036LL); break;
        }
        addr_681000101 += strd_681000101;

        //Dominant stride
        READ_4b(addr_681100101);
        addr_681100101 += 4LL;
        if(addr_681100101 >= 346856LL) addr_681100101 = 34340LL;

        //Dominant stride
        WRITE_4b(addr_681300101);
        addr_681300101 += 4LL;
        if(addr_681300101 >= 396168LL) addr_681300101 = 50772LL;

        //Small tile
        READ_4b(addr_681400101);
        switch(addr_681400101) {
            case 11156LL : strd_681400101 = (11160LL - 11156LL); break;
            case 11188LL : strd_681400101 = (11156LL - 11188LL); break;
        }
        addr_681400101 += strd_681400101;

        //Dominant stride
        READ_4b(addr_681500101);
        addr_681500101 += 4LL;
        if(addr_681500101 >= 396120LL) addr_681500101 = 50724LL;

        //Dominant stride
        WRITE_4b(addr_681600101);
        addr_681600101 += 4LL;
        if(addr_681600101 >= 396168LL) addr_681600101 = 50772LL;

        //Dominant stride
        READ_4b(addr_681700101);
        addr_681700101 += 4LL;
        if(addr_681700101 >= 13152LL) addr_681700101 = 12356LL;

        //Dominant stride
        WRITE_4b(addr_681800101);
        addr_681800101 += 4LL;
        if(addr_681800101 >= 396168LL) addr_681800101 = 50772LL;

        goto block25;

block41:
        for(uint64_t loop0 = 0; loop0 < 10ULL; loop0++){
            //Loop Indexed
            addr = 13524LL + (4 * loop0);
            READ_4b(addr);

            //Loop Indexed
            addr = 34388LL + (4 * loop0);
            READ_4b(addr);

        }
        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_41 = 0;
        cov_41++;
        if(cov_41 <= 2017196ULL) {
            static uint64_t out_41 = 0;
            out_41 = (out_41 == 351LL) ? 1 : (out_41 + 1);
            if (out_41 <= 350LL) goto block12;
            else goto block2;
        }
        else if (cov_41 <= 2017197ULL) goto block2;
        else goto block12;

block12:
        //Dominant stride
        READ_8b(addr_675300101);
        addr_675300101 += 8LL;
        if(addr_675300101 >= 164384LL) addr_675300101 = 16560LL;

        //Dominant stride
        READ_8b(addr_675900101);
        addr_675900101 += 8LL;
        if(addr_675900101 >= 135552LL) addr_675900101 = 23864LL;

        //Dominant stride
        READ_8b(addr_676000101);
        addr_676000101 += 8LL;
        if(addr_676000101 >= 135544LL) addr_676000101 = 23856LL;

        //Dominant stride
        READ_8b(addr_676100101);
        addr_676100101 += 8LL;
        if(addr_676100101 >= 127760LL) addr_676100101 = 16568LL;

        //Dominant stride
        READ_8b(addr_676200101);
        addr_676200101 += 8LL;
        if(addr_676200101 >= 119968LL) addr_676200101 = 16568LL;

        //Dominant stride
        READ_8b(addr_676300101);
        addr_676300101 += 8LL;
        if(addr_676300101 >= 119960LL) addr_676300101 = 16560LL;

        //Dominant stride
        READ_8b(addr_676700101);
        addr_676700101 += 8LL;
        if(addr_676700101 >= 127752LL) addr_676700101 = 16560LL;

        //Random
        addr = (bounded_rnd(10736LL - 10576LL) + 10576LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(10944LL - 10784LL) + 10784LL) & ~7ULL;
        READ_8b(addr);

        goto block25;

block3:
        //Dominant stride
        READ_4b(addr_648500101);
        addr_648500101 += 4LL;
        if(addr_648500101 >= 404352LL) addr_648500101 = 404276LL;

        //Unordered
        static uint64_t out_3_12 = 5323LL;
        static uint64_t out_3_3 = 16704728LL;
        static uint64_t out_3_2 = 1863466LL;
        tmpRnd = out_3_12 + out_3_3 + out_3_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_3_12)){
                out_3_12--;
                goto block12;
            }
            else if (tmpRnd < (out_3_12 + out_3_3)){
                out_3_3--;
                goto block3;
            }
            else {
                out_3_2--;
                goto block2;
            }
        }
        goto block12;


block2:
        //Random
        addr = (bounded_rnd(4192LL - 3680LL) + 3680LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(4192LL - 3680LL) + 3680LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_2_12 = 424LL;
        static uint64_t out_2_3 = 1868766LL;
        static uint64_t out_2_2 = 152721LL;
        tmpRnd = out_2_12 + out_2_3 + out_2_2;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_2_12)){
                out_2_12--;
                goto block12;
            }
            else if (tmpRnd < (out_2_12 + out_2_3)){
                out_2_3--;
                goto block3;
            }
            else {
                out_2_2--;
                goto block2;
            }
        }
        goto block3;


block42:
        int dummy;
    }

    // Interval: 1000000000 - 1727075875
    {
        int64_t addr_680200101 = 310512LL;
        int64_t addr_680100101 = 11248LL, strd_680100101 = 0;
        int64_t addr_680300101 = 310516LL;
        int64_t addr_680400101 = 11088LL, strd_680400101 = 0;
        int64_t addr_680500101 = 261248LL;
        int64_t addr_680700101 = 310516LL;
        int64_t addr_679500101 = 261256LL;
        int64_t addr_679600101 = 13480LL, strd_679600101 = 0;
        int64_t addr_679200101 = 310468LL;
        int64_t addr_679100101 = 11212LL, strd_679100101 = 0;
        int64_t addr_679800101 = 261256LL;
        int64_t addr_679900101 = 11480LL;
        int64_t addr_679000101 = 261256LL;
        int64_t addr_680000101 = 261256LL;
        int64_t addr_678900101 = 371764LL;
        int64_t addr_678800101 = 11132LL, strd_678800101 = 0;
        int64_t addr_678700101 = 261256LL;
        int64_t addr_678400101 = 11012LL, strd_678400101 = 0;
        int64_t addr_678500101 = 261204LL;
        int64_t addr_648500101 = 404276LL;
        int64_t addr_681800101 = 371812LL;
        int64_t addr_681700101 = 12532LL;
        int64_t addr_681600101 = 371812LL;
        int64_t addr_681500101 = 371764LL;
        int64_t addr_681400101 = 11172LL, strd_681400101 = 0;
        int64_t addr_681300101 = 371812LL;
        int64_t addr_681100101 = 261204LL;
        int64_t addr_681000101 = 11052LL, strd_681000101 = 0;
        int64_t addr_684800101 = 20504LL;
        int64_t addr_685700101 = 20504LL;
        int64_t addr_687200101 = 20504LL;
        int64_t addr_682900101 = 20504LL;
        int64_t addr_684300101 = 20496LL;
        int64_t addr_684100101 = 20504LL;
        int64_t addr_683300101 = 28728LL;
        int64_t addr_682600101 = 20496LL;
        int64_t addr_686800101 = 20496LL;
        int64_t addr_682400101 = 20504LL;
        int64_t addr_686100101 = 20504LL;
block43:
        goto block49;

block57:
        //Small tile
        READ_4b(addr_681000101);
        switch(addr_681000101) {
            case 11052LL : strd_681000101 = (11056LL - 11052LL); break;
            case 11068LL : strd_681000101 = (11036LL - 11068LL); break;
            case 11036LL : strd_681000101 = (11040LL - 11036LL); break;
        }
        addr_681000101 += strd_681000101;

        //Dominant stride
        READ_4b(addr_681100101);
        addr_681100101 += 4LL;
        if(addr_681100101 >= 281288LL) addr_681100101 = 170324LL;

        //Dominant stride
        WRITE_4b(addr_681300101);
        addr_681300101 += 4LL;
        if(addr_681300101 >= 399288LL) addr_681300101 = 348180LL;

        //Small tile
        READ_4b(addr_681400101);
        switch(addr_681400101) {
            case 11156LL : strd_681400101 = (11160LL - 11156LL); break;
            case 11172LL : strd_681400101 = (11176LL - 11172LL); break;
            case 11188LL : strd_681400101 = (11156LL - 11188LL); break;
        }
        addr_681400101 += strd_681400101;

        //Dominant stride
        READ_4b(addr_681500101);
        addr_681500101 += 4LL;
        if(addr_681500101 >= 399240LL) addr_681500101 = 348132LL;

        //Dominant stride
        WRITE_4b(addr_681600101);
        addr_681600101 += 4LL;
        if(addr_681600101 >= 399288LL) addr_681600101 = 348180LL;

        //Dominant stride
        READ_4b(addr_681700101);
        addr_681700101 += 4LL;
        if(addr_681700101 >= 13152LL) addr_681700101 = 12356LL;

        //Dominant stride
        WRITE_4b(addr_681800101);
        addr_681800101 += 4LL;
        if(addr_681800101 >= 399288LL) addr_681800101 = 348180LL;

        goto block70;

block49:
        //Small tile
        READ_4b(addr_680100101);
        switch(addr_680100101) {
            case 11268LL : strd_680100101 = (11232LL - 11268LL); break;
            case 11248LL : strd_680100101 = (11252LL - 11248LL); break;
            case 11232LL : strd_680100101 = (11236LL - 11232LL); break;
        }
        addr_680100101 += strd_680100101;

        //Dominant stride
        READ_4b(addr_680200101);
        addr_680200101 += 4LL;
        if(addr_680200101 >= 330600LL) addr_680200101 = 222752LL;

        //Dominant stride
        WRITE_4b(addr_680300101);
        addr_680300101 += 4LL;
        if(addr_680300101 >= 330604LL) addr_680300101 = 222756LL;

        //Small tile
        READ_4b(addr_680400101);
        switch(addr_680400101) {
            case 11072LL : strd_680400101 = (11076LL - 11072LL); break;
            case 11108LL : strd_680400101 = (11072LL - 11108LL); break;
            case 11088LL : strd_680400101 = (11092LL - 11088LL); break;
        }
        addr_680400101 += strd_680400101;

        //Dominant stride
        READ_4b(addr_680500101);
        addr_680500101 += 4LL;
        if(addr_680500101 >= 281336LL) addr_680500101 = 170368LL;

        //Dominant stride
        WRITE_4b(addr_680700101);
        addr_680700101 += 4LL;
        if(addr_680700101 >= 330604LL) addr_680700101 = 222756LL;

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_49 = 0;
        cov_49++;
        if(cov_49 <= 13224798ULL) {
            static uint64_t out_49 = 0;
            out_49 = (out_49 == 9LL) ? 1 : (out_49 + 1);
            if (out_49 <= 8LL) goto block57;
            else goto block83;
        }
        else goto block57;

block70:
        //Small tile
        READ_4b(addr_678400101);
        switch(addr_678400101) {
            case 11012LL : strd_678400101 = (11016LL - 11012LL); break;
            case 10992LL : strd_678400101 = (10996LL - 10992LL); break;
            case 11028LL : strd_678400101 = (10992LL - 11028LL); break;
        }
        addr_678400101 += strd_678400101;

        //Dominant stride
        READ_4b(addr_678500101);
        addr_678500101 += 4LL;
        if(addr_678500101 >= 281288LL) addr_678500101 = 170320LL;

        //Dominant stride
        WRITE_4b(addr_678700101);
        addr_678700101 += 4LL;
        if(addr_678700101 >= 281340LL) addr_678700101 = 170372LL;

        //Small tile
        READ_4b(addr_678800101);
        switch(addr_678800101) {
            case 11132LL : strd_678800101 = (11136LL - 11132LL); break;
            case 11112LL : strd_678800101 = (11116LL - 11112LL); break;
            case 11148LL : strd_678800101 = (11112LL - 11148LL); break;
        }
        addr_678800101 += strd_678800101;

        //Dominant stride
        READ_4b(addr_678900101);
        addr_678900101 += 4LL;
        if(addr_678900101 >= 399240LL) addr_678900101 = 348128LL;

        //Dominant stride
        WRITE_4b(addr_679000101);
        addr_679000101 += 4LL;
        if(addr_679000101 >= 281340LL) addr_679000101 = 170372LL;

        //Small tile
        READ_4b(addr_679100101);
        switch(addr_679100101) {
            case 11212LL : strd_679100101 = (11216LL - 11212LL); break;
            case 11192LL : strd_679100101 = (11196LL - 11192LL); break;
            case 11228LL : strd_679100101 = (11192LL - 11228LL); break;
        }
        addr_679100101 += strd_679100101;

        //Dominant stride
        READ_4b(addr_679200101);
        addr_679200101 += 4LL;
        if(addr_679200101 >= 330552LL) addr_679200101 = 222704LL;

        //Dominant stride
        WRITE_4b(addr_679500101);
        addr_679500101 += 4LL;
        if(addr_679500101 >= 281340LL) addr_679500101 = 170372LL;

        //Small tile
        READ_4b(addr_679600101);
        switch(addr_679600101) {
            case 13480LL : strd_679600101 = (13484LL - 13480LL); break;
            case 13460LL : strd_679600101 = (13464LL - 13460LL); break;
            case 13496LL : strd_679600101 = (13460LL - 13496LL); break;
        }
        addr_679600101 += strd_679600101;

        //Dominant stride
        WRITE_4b(addr_679800101);
        addr_679800101 += 4LL;
        if(addr_679800101 >= 281340LL) addr_679800101 = 170372LL;

        //Dominant stride
        READ_4b(addr_679900101);
        addr_679900101 += 4LL;
        if(addr_679900101 >= 12160LL) addr_679900101 = 11284LL;

        //Dominant stride
        WRITE_4b(addr_680000101);
        addr_680000101 += 4LL;
        if(addr_680000101 >= 281340LL) addr_680000101 = 170372LL;

        goto block49;

block83:
        //Dominant stride
        READ_8b(addr_682400101);
        addr_682400101 += 8LL;
        if(addr_682400101 >= 344624LL) addr_682400101 = 16568LL;

        //Dominant stride
        READ_8b(addr_682600101);
        addr_682600101 += 8LL;
        if(addr_682600101 >= 344616LL) addr_682600101 = 16560LL;

        //Dominant stride
        READ_8b(addr_682900101);
        addr_682900101 += 8LL;
        if(addr_682900101 >= 344624LL) addr_682900101 = 16568LL;

        //Dominant stride
        READ_8b(addr_683300101);
        addr_683300101 += 8LL;
        if(addr_683300101 >= 33312LL) addr_683300101 = 24792LL;

        for(uint64_t loop1 = 0; loop1 < 10ULL; loop1++){
            //Loop Indexed
            addr = 13524LL + (4 * loop1);
            READ_4b(addr);

            //Loop Indexed
            addr = 261236LL + (4 * loop1);
            READ_4b(addr);

        }
        //Dominant stride
        READ_8b(addr_684100101);
        addr_684100101 += 8LL;
        if(addr_684100101 >= 344624LL) addr_684100101 = 16568LL;

        //Dominant stride
        READ_8b(addr_684300101);
        addr_684300101 += 8LL;
        if(addr_684300101 >= 344616LL) addr_684300101 = 16560LL;

        //Dominant stride
        READ_8b(addr_684800101);
        addr_684800101 += 8LL;
        if(addr_684800101 >= 344624LL) addr_684800101 = 16568LL;

        //Dominant stride
        READ_8b(addr_685700101);
        addr_685700101 += 8LL;
        if(addr_685700101 >= 344624LL) addr_685700101 = 16568LL;

        //Dominant stride
        READ_8b(addr_686100101);
        addr_686100101 += 8LL;
        if(addr_686100101 >= 344624LL) addr_686100101 = 16568LL;

        //Dominant stride
        READ_8b(addr_686800101);
        addr_686800101 += 8LL;
        if(addr_686800101 >= 344616LL) addr_686800101 = 16560LL;

        //Dominant stride
        READ_8b(addr_687200101);
        addr_687200101 += 8LL;
        if(addr_687200101 >= 344624LL) addr_687200101 = 16568LL;

        //Unordered
        static uint64_t out_83_70 = 1465169LL;
        static uint64_t out_83_84 = 4252LL;
        tmpRnd = out_83_70 + out_83_84;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_83_70)){
                out_83_70--;
                goto block70;
            }
            else {
                out_83_84--;
                goto block84;
            }
        }
        goto block85;


block84:
        static int64_t loop2_break = 13490331ULL;
        for(uint64_t loop2 = 0; loop2 < 3173ULL; loop2++){
            if(loop2_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_648500101);
            addr_648500101 += 4LL;
            if(addr_648500101 >= 404352LL) addr_648500101 = 404276LL;

        }
        goto block70;

block85:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
