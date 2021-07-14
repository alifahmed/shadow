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
    uint64_t allocSize = 134287360ULL;
    gm = (volatile uint8_t*)aligned_alloc(4096, allocSize);

    // Interval: 0 - 1270866273
    {
        int64_t addr_375300101 = 67149848LL;
        int64_t addr_374700101 = 4116LL, strd_374700101 = 0;
        int64_t addr_408100101 = 4112LL;
        int64_t addr_409500101 = 134283332LL;
        int64_t addr_409100101 = 134283268LL;
        int64_t addr_406500101 = 67149848LL;
        int64_t addr_409900101 = 134283264LL;
        int64_t addr_412000101 = 134283336LL;
        int64_t addr_413500101 = 134283336LL;
        int64_t addr_413600101 = 20504LL;
        int64_t addr_418000101 = 66867216LL;
        int64_t addr_418100101 = 134283264LL, strd_418100101 = 0;
        int64_t addr_416400101 = 134012952LL;
        int64_t addr_419000101 = 134283268LL;
        int64_t addr_419400101 = 134283332LL;
        int64_t addr_419800101 = 134283264LL;
block0:
        goto block15;

block22:
        for(uint64_t loop0 = 0; loop0 < 256ULL; loop0++){
            //Dominant stride
            READ_4b(addr_419000101);
            addr_419000101 += 4LL;
            if(addr_419000101 >= 134284352LL) addr_419000101 = 134283268LL;

            //Dominant stride
            READ_4b(addr_419400101);
            addr_419400101 += 4LL;
            if(addr_419400101 >= 134284416LL) addr_419400101 = 134283332LL;

            //Dominant stride
            READ_4b(addr_419800101);
            addr_419800101 += 4LL;
            if(addr_419800101 >= 134284348LL) addr_419800101 = 134283264LL;

        }
        goto block19;

block19:
        for(uint64_t loop2 = 0; loop2 < 256ULL; loop2++){
            //Dominant stride
            READ_4b(addr_416400101);
            addr_416400101 += 4LL;
            if(addr_416400101 >= 134263380LL) addr_416400101 = 67428376LL;

            //Loop Indexed
            addr = 134282240LL + (4 * loop2);
            WRITE_4b(addr);

        }
        static int64_t loop1_break = 4564791ULL;
        for(uint64_t loop1 = 0; loop1 < 289ULL; loop1++){
            if(loop1_break-- <= 0) break;
            //Dominant stride
            READ_4b(addr_418000101);
            addr_418000101 += 4LL;
            if(addr_418000101 >= 67134036LL) addr_418000101 = 282640LL;

            //Small tile
            WRITE_4b(addr_418100101);
            switch(addr_418100101) {
                case 134284416LL : strd_418100101 = (134283264LL - 134284416LL); break;
                case 134283264LL : strd_418100101 = (134283268LL - 134283264LL); break;
            }
            addr_418100101 += strd_418100101;

        }
        //Few edges. Don't bother optimizing
        static uint64_t out_19 = 0;
        out_19++;
        if (out_19 <= 15795LL) goto block22;
        else goto block23;


block15:
        for(uint64_t loop9 = 0; loop9 < 16785409ULL; loop9++){
            //Loop Indexed
            addr = 4112LL + (4 * loop9);
            WRITE_4b(addr);

        }
        for(uint64_t loop8 = 0; loop8 < 16777216ULL; loop8++){
            //Small tile
            READ_4b(addr_374700101);
            switch(addr_374700101) {
                case 4116LL : strd_374700101 = (4120LL - 4116LL); break;
                case 20496LL : strd_374700101 = (4116LL - 20496LL); break;
            }
            addr_374700101 += strd_374700101;

            //Random
            addr = (bounded_rnd(1036LL - 132LL) + 132LL) & ~3ULL;
            READ_4b(addr);

            //Dominant stride
            WRITE_4b(addr_375300101);
            addr_375300101 += 4LL;
            if(addr_375300101 >= 134275092LL) addr_375300101 = 67149848LL;

        }
        for(uint64_t loop7 = 0; loop7 < 32896ULL; loop7++){
            addr_409500101 = 134283332LL;
            addr_409100101 = 134283268LL;
            addr_409900101 = 134283264LL;
            addr_412000101 = 134283336LL;
            addr_413500101 = 134283336LL;
            for(uint64_t loop6 = 0; loop6 < 256ULL; loop6++){
                //Dominant stride
                READ_4b(addr_406500101);
                addr_406500101 += 4LL;
                if(addr_406500101 >= 134258772LL) addr_406500101 = 67149848LL;

                //Loop Indexed
                addr = 134282240LL + (4 * loop6);
                WRITE_4b(addr);

            }
            for(uint64_t loop5 = 0; loop5 < 289ULL; loop5++){
                //Dominant stride
                READ_4b(addr_408100101);
                addr_408100101 += 4LL;
                if(addr_408100101 >= 67129428LL) addr_408100101 = 4112LL;

                //Loop Indexed
                addr = 134283264LL + (4 * loop5);
                WRITE_4b(addr);

            }
            for(uint64_t loop4 = 0; loop4 < 256ULL; loop4++){
                //Dominant stride
                READ_4b(addr_409100101);
                addr_409100101 += 4LL;
                if(addr_409100101 >= 134284352LL) addr_409100101 = 134283268LL;

                //Dominant stride
                READ_4b(addr_409500101);
                addr_409500101 += 4LL;
                if(addr_409500101 >= 134284416LL) addr_409500101 = 134283332LL;

                //Dominant stride
                READ_4b(addr_409900101);
                addr_409900101 += 4LL;
                if(addr_409900101 >= 134284348LL) addr_409900101 = 134283264LL;

                //Loop Indexed
                addr = 134282240LL + (4 * loop4);
                READ_4b(addr);

                //Dominant stride
                WRITE_4b(addr_412000101);
                addr_412000101 += 4LL;
                if(addr_412000101 >= 134284420LL) addr_412000101 = 134283336LL;

            }
            for(uint64_t loop3 = 0; loop3 < 256ULL; loop3++){
                //Dominant stride
                READ_4b(addr_413500101);
                addr_413500101 += 4LL;
                if(addr_413500101 >= 134284420LL) addr_413500101 = 134283336LL;

                //Dominant stride
                WRITE_4b(addr_413600101);
                addr_413600101 += 4LL;
                if(addr_413600101 >= 67129428LL) addr_413600101 = 20504LL;

            }
        }
        goto block19;

block23:
        int dummy;
    }

    free((void*)gm);
    return 0;
}
