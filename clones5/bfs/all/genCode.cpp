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
    uint64_t allocSize = 62341120ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1387650559
    {
block0:
        goto block3;

block76:
        //Random
        addr = (bounded_rnd(47506832LL - 3856LL) + 3856LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(47506864LL - 3856LL) + 3856LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(47932528LL - 4144LL) + 4144LL) & ~31ULL;
        WRITE_32b(addr);

        //Random
        addr = (bounded_rnd(47932560LL - 4144LL) + 4144LL) & ~31ULL;
        WRITE_32b(addr);

        goto block34;

block80:
        //Random
        addr = (bounded_rnd(47644560LL - 3856LL) + 3856LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(47644592LL - 3856LL) + 3856LL) & ~31ULL;
        READ_32b(addr);

        //Random
        addr = (bounded_rnd(47931376LL - 3904LL) + 3904LL) & ~31ULL;
        WRITE_32b(addr);

        //Random
        addr = (bounded_rnd(47931408LL - 3904LL) + 3904LL) & ~31ULL;
        WRITE_32b(addr);

        goto block44;

block81:
        //Random
        addr = (bounded_rnd(31422160LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_81 = 0;
        cov_81++;
        if(cov_81 <= 126586ULL) {
            static uint64_t out_81 = 0;
            out_81 = (out_81 == 758LL) ? 1 : (out_81 + 1);
            if (out_81 <= 757LL) goto block81;
            else goto block82;
        }
        else if (cov_81 <= 126743ULL) goto block81;
        else goto block82;

block82:
        //Random
        addr = (bounded_rnd(31422160LL - 3760LL) + 3760LL) & ~15ULL;
        WRITE_16b(addr);

        //Unordered
        static uint64_t out_82_82 = 110561LL;
        static uint64_t out_82_13 = 4675LL;
        static uint64_t out_82_10 = 463LL;
        tmpRnd = out_82_82 + out_82_13 + out_82_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_82_82)){
                out_82_82--;
                goto block82;
            }
            else if (tmpRnd < (out_82_82 + out_82_13)){
                out_82_13--;
                goto block13;
            }
            else {
                out_82_10--;
                goto block10;
            }
        }
        goto block13;


block83:
        //Random
        addr = (bounded_rnd(42794384LL - 3792LL) + 3792LL) & ~15ULL;
        WRITE_16b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_83 = 0;
        cov_83++;
        if(cov_83 <= 139832ULL) {
            static uint64_t out_83 = 0;
            out_83 = (out_83 == 454LL) ? 1 : (out_83 + 1);
            if (out_83 <= 453LL) goto block83;
            else goto block84;
        }
        else if (cov_83 <= 139971ULL) goto block83;
        else goto block84;

block84:
        //Random
        addr = (bounded_rnd(42794384LL - 3792LL) + 3792LL) & ~15ULL;
        WRITE_16b(addr);

        //Unordered
        static uint64_t out_84_84 = 151070LL;
        static uint64_t out_84_29 = 1574LL;
        static uint64_t out_84_32 = 4640LL;
        tmpRnd = out_84_84 + out_84_29 + out_84_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_84_84)){
                out_84_84--;
                goto block84;
            }
            else if (tmpRnd < (out_84_84 + out_84_29)){
                out_84_29--;
                goto block29;
            }
            else {
                out_84_32--;
                goto block32;
            }
        }
        goto block29;


block48:
        //Random
        addr = (bounded_rnd(47601112LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47601120LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        goto block33;

block52:
        //Random
        addr = (bounded_rnd(17901424LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(17901424LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(31424416LL - 3792LL) + 3792LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(31424416LL - 3792LL) + 3792LL) & ~15ULL;
        WRITE_16b(addr);

        goto block44;

block53:
        //Random
        addr = (bounded_rnd(47930712LL - 3880LL) + 3880LL) & ~7ULL;
        WRITE_8b(addr);

        goto block16;

block57:
        //Random
        addr = (bounded_rnd(62335192LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47902448LL - 3880LL) + 3880LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(62335192LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335192LL - 47935520LL) + 47935520LL) & ~7ULL;
        WRITE_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_57 = 0;
        cov_57++;
        if(cov_57 <= 457853ULL) {
            static uint64_t out_57 = 0;
            out_57 = (out_57 == 3LL) ? 1 : (out_57 + 1);
            if (out_57 <= 2LL) goto block9;
            else goto block6;
        }
        else if (cov_57 <= 490695ULL) goto block6;
        else goto block9;

block61:
        //Random
        addr = (bounded_rnd(17901424LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(17901424LL - 3760LL) + 3760LL) & ~15ULL;
        READ_16b(addr);

        //Random
        addr = (bounded_rnd(31424048LL - 4176LL) + 4176LL) & ~15ULL;
        WRITE_16b(addr);

        //Random
        addr = (bounded_rnd(31424048LL - 4176LL) + 4176LL) & ~15ULL;
        WRITE_16b(addr);

        goto block34;

block64:
        //Random
        addr = (bounded_rnd(47506800LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47506800LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47506816LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_64 = 0;
        cov_64++;
        if(cov_64 <= 578731ULL) {
            static uint64_t out_64 = 0;
            out_64 = (out_64 == 7LL) ? 1 : (out_64 + 1);
            if (out_64 <= 6LL) goto block66;
            else goto block37;
        }
        else if (cov_64 <= 617449ULL) goto block37;
        else goto block66;

block66:
        //Random
        addr = (bounded_rnd(47506816LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(47506808LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block37;

block68:
        //Random
        addr = (bounded_rnd(47644536LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47644544LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        goto block14;

block72:
        //Random
        addr = (bounded_rnd(17901416LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17901416LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17901416LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17901416LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block34;

block28:
        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_28_84 = 5894LL;
        static uint64_t out_28_48 = 692572LL;
        static uint64_t out_28_29 = 348183LL;
        static uint64_t out_28_32 = 27141LL;
        tmpRnd = out_28_84 + out_28_48 + out_28_29 + out_28_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_28_84)){
                out_28_84--;
                goto block84;
            }
            else if (tmpRnd < (out_28_84 + out_28_48)){
                out_28_48--;
                goto block48;
            }
            else if (tmpRnd < (out_28_84 + out_28_48 + out_28_29)){
                out_28_29--;
                goto block29;
            }
            else {
                out_28_32--;
                goto block32;
            }
        }
        goto block32;


block29:
        //Random
        addr = (bounded_rnd(47932496LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_29_83 = 321LL;
        static uint64_t out_29_29 = 17LL;
        static uint64_t out_29_31 = 349121LL;
        static uint64_t out_29_32 = 216LL;
        tmpRnd = out_29_83 + out_29_29 + out_29_31 + out_29_32;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_29_83)){
                out_29_83--;
                goto block83;
            }
            else if (tmpRnd < (out_29_83 + out_29_29)){
                out_29_29--;
                goto block29;
            }
            else if (tmpRnd < (out_29_83 + out_29_29 + out_29_31)){
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
        addr = (bounded_rnd(47932496LL - 3784LL) + 3784LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(47932640LL - 3816LL) + 3816LL) & ~7ULL;
        WRITE_8b(addr);

        goto block32;

block32:
        //Random
        addr = (bounded_rnd(47932496LL - 3784LL) + 3784LL) & ~7ULL;
        READ_8b(addr);

        goto block33;

block33:
        //Random
        addr = (bounded_rnd(47932568LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_33_76 = 232580LL;
        static uint64_t out_33_61 = 182556LL;
        static uint64_t out_33_72 = 248573LL;
        static uint64_t out_33_34 = 410072LL;
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
        addr = (bounded_rnd(62335512LL - 47935528LL) + 47935528LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_34 = 0;
        cov_34++;
        if(cov_34 <= 878330ULL) {
            static uint64_t out_34 = 0;
            out_34 = (out_34 == 5LL) ? 1 : (out_34 + 1);
            if (out_34 <= 2LL) goto block37;
            else goto block64;
        }
        else if (cov_34 <= 937069ULL) goto block37;
        else goto block64;

block37:
        //Random
        addr = (bounded_rnd(62335496LL - 47935512LL) + 47935512LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(62335512LL - 47935528LL) + 47935528LL) & ~7ULL;
        WRITE_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_37 = 0;
        cov_37++;
        if(cov_37 <= 974738ULL) {
            static uint64_t out_37 = 0;
            out_37 = (out_37 == 3LL) ? 1 : (out_37 + 1);
            if (out_37 <= 2LL) goto block9;
            else goto block6;
        }
        else if (cov_37 <= 1007338ULL) goto block6;
        else goto block9;

block41:
        //Random
        addr = (bounded_rnd(17901384LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17901384LL - 3760LL) + 3760LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(17969560LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(17969560LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block44;

block44:
        //Random
        addr = (bounded_rnd(47644528LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47644528LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(47644544LL - 3768LL) + 3768LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_44 = 0;
        cov_44++;
        if(cov_44 <= 773034ULL) {
            static uint64_t out_44 = 0;
            out_44 = (out_44 == 6LL) ? 1 : (out_44 + 1);
            if (out_44 <= 5LL) goto block46;
            else goto block16;
        }
        else if (cov_44 <= 884610ULL) goto block46;
        else goto block16;

block46:
        //Random
        addr = (bounded_rnd(47644544LL - 3768LL) + 3768LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(47644536LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        goto block16;

block16:
        //Random
        addr = (bounded_rnd(62335504LL - 47935520LL) + 47935520LL) & ~7ULL;
        READ_8b(addr);

        //Random
        addr = (bounded_rnd(62335512LL - 47935528LL) + 47935528LL) & ~7ULL;
        READ_8b(addr);

        //Ordered...
        //Remainder NOT zero
        static uint64_t cov_16 = 0;
        cov_16++;
        if(cov_16 <= 1151991ULL) {
            static uint64_t out_16 = 0;
            out_16 = (out_16 == 4LL) ? 1 : (out_16 + 1);
            if (out_16 <= 3LL) goto block28;
            else goto block57;
        }
        else if (cov_16 <= 1419187ULL) goto block57;
        else goto block28;

block14:
        //Random
        addr = (bounded_rnd(47931416LL - 3760LL) + 3760LL) & ~7ULL;
        WRITE_8b(addr);

        //Unordered
        static uint64_t out_14_80 = 212680LL;
        static uint64_t out_14_52 = 377499LL;
        static uint64_t out_14_41 = 337416LL;
        static uint64_t out_14_16 = 186265LL;
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
        goto block85;


block13:
        //Random
        addr = (bounded_rnd(47931344LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        goto block14;

block12:
        //Random
        addr = (bounded_rnd(47931344LL - 3752LL) + 3752LL) & ~7ULL;
        WRITE_8b(addr);

        //Random
        addr = (bounded_rnd(47931488LL - 3784LL) + 3784LL) & ~7ULL;
        WRITE_8b(addr);

        goto block13;

block10:
        //Random
        addr = (bounded_rnd(47931344LL - 3752LL) + 3752LL) & ~7ULL;
        READ_8b(addr);

        //Unordered
        static uint64_t out_10_81 = 169LL;
        static uint64_t out_10_13 = 139LL;
        static uint64_t out_10_12 = 442922LL;
        static uint64_t out_10_10 = 24LL;
        tmpRnd = out_10_81 + out_10_13 + out_10_12 + out_10_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_10_81)){
                out_10_81--;
                goto block81;
            }
            else if (tmpRnd < (out_10_81 + out_10_13)){
                out_10_13--;
                goto block13;
            }
            else if (tmpRnd < (out_10_81 + out_10_13 + out_10_12)){
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
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        WRITE_4b(addr);

        //Unordered
        static uint64_t out_9_82 = 4970LL;
        static uint64_t out_9_53 = 515124LL;
        static uint64_t out_9_68 = 635200LL;
        static uint64_t out_9_13 = 30901LL;
        static uint64_t out_9_10 = 442789LL;
        tmpRnd = out_9_82 + out_9_53 + out_9_68 + out_9_13 + out_9_10;
        if (tmpRnd) {
            tmpRnd = bounded_rnd(tmpRnd);
            if (tmpRnd < (out_9_82)){
                out_9_82--;
                goto block82;
            }
            else if (tmpRnd < (out_9_82 + out_9_53)){
                out_9_53--;
                goto block53;
            }
            else if (tmpRnd < (out_9_82 + out_9_53 + out_9_68)){
                out_9_68--;
                goto block68;
            }
            else if (tmpRnd < (out_9_82 + out_9_53 + out_9_68 + out_9_13)){
                out_9_13--;
                goto block13;
            }
            else {
                out_9_10--;
                goto block10;
            }
        }
        goto block13;


block3:
        for(uint64_t loop0 = 0; loop0 < 600000ULL; loop0++){
            //Loop Indexed
            addr = 47935512LL + (24 * loop0);
            WRITE_8b(addr);

            //Loop Indexed
            addr = 47935520LL + (24 * loop0);
            WRITE_8b(addr);

            //Loop Indexed
            addr = 47935528LL + (24 * loop0);
            WRITE_8b(addr);

        }
        goto block6;

block6:
        //Random
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        READ_4b(addr);

        //Random
        addr = (bounded_rnd(62337600LL - 62337476LL) + 62337476LL) & ~3ULL;
        WRITE_4b(addr);

        goto block9;

block85:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
