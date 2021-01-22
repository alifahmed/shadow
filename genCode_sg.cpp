#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include "immintrin.h"

volatile uint8_t* gm;

int main(){
    uint64_t addr;
    uint64_t hash = 0xC32ED012FEA8B4D3ULL;
    uint64_t tmpRnd;
    uint8_t tmpb;
    uint16_t tmpw;
    uint32_t tmpl;
    uint64_t tmpq;
    uint64_t allocSize = 1600124ULL;
    gm = (volatile uint8_t*)malloc(allocSize);
    if(gm == NULL) {
        fprintf(stderr, "Cannot allocate memory\n");
        exit(-1);
    }

    uint64_t addr_413800201 = 1600016, strd_413800201 = 0;
    uint64_t addr_413700201 = 1600016, strd_413700201 = 0;
    uint64_t addr_413600201 = 1600004, strd_413600201 = 0;
    uint64_t addr_413800101 = 1600012, strd_413800101 = 0;
    uint64_t addr_413700101 = 1600012, strd_413700101 = 0;
    uint64_t addr_413600101 = 1600000, strd_413600101 = 0;

    goto block0;

block2:
    for(uint64_t loop3 = 0; loop3 < 2ULL; loop3++){
        for(uint64_t loop2 = 0; loop2 < 100000ULL; loop2++){
            addr = 400000 + (4 * loop2);
            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr), "r"(tmpl) : "memory");

            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr_413600101) : "memory");
            switch(addr_413600101) {
                case 1600000 : strd_413600101 = 8; break;
                case 1600004 : strd_413600101 = 8; break;
                case 1600116 : strd_413600101 = -116; break;
                case 1600120 : strd_413600101 = -116; break;
            }
            addr_413600101 += strd_413600101;

            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr_413700101) : "memory");
            switch(addr_413700101) {
                case 1600000 : strd_413700101 = 8; break;
                case 1600004 : strd_413700101 = 8; break;
                case 1600012 : strd_413700101 = 8; break;
                case 1600116 : strd_413700101 = -116; break;
                case 1600120 : strd_413700101 = -116; break;
            }
            addr_413700101 += strd_413700101;

            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr_413800101), "r"(tmpl) : "memory");
            switch(addr_413800101) {
                case 1600000 : strd_413800101 = 8; break;
                case 1600004 : strd_413800101 = 8; break;
                case 1600012 : strd_413800101 = 8; break;
                case 1600116 : strd_413800101 = -116; break;
                case 1600120 : strd_413800101 = -116; break;
            }
            addr_413800101 += strd_413800101;

            addr = 800000 + (4 * loop2);
            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr), "r"(tmpl) : "memory");

            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr_413600201) : "memory");
            switch(addr_413600201) {
                case 1600000 : strd_413600201 = 8; break;
                case 1600004 : strd_413600201 = 8; break;
                case 1600116 : strd_413600201 = -116; break;
                case 1600120 : strd_413600201 = -116; break;
            }
            addr_413600201 += strd_413600201;

            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr_413700201) : "memory");
            switch(addr_413700201) {
                case 1600000 : strd_413700201 = 8; break;
                case 1600004 : strd_413700201 = 8; break;
                case 1600016 : strd_413700201 = 8; break;
                case 1600116 : strd_413700201 = -116; break;
                case 1600120 : strd_413700201 = -116; break;
            }
            addr_413700201 += strd_413700201;

            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr_413800201), "r"(tmpl) : "memory");
            switch(addr_413800201) {
                case 1600000 : strd_413800201 = 8; break;
                case 1600004 : strd_413800201 = 8; break;
                case 1600016 : strd_413800201 = 8; break;
                case 1600116 : strd_413800201 = -116; break;
                case 1600120 : strd_413800201 = -116; break;
            }
            addr_413800201 += strd_413800201;

            addr = 1200000 + (4 * loop2);
            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr), "r"(tmpl) : "memory");

        }
        for(uint64_t loop0 = 0; loop0 < 100000ULL; loop0++){
            addr = 1200000 + (4 * loop0);
            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr) : "memory");

            addr = 800000 + (4 * loop0);
            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr) : "memory");

            hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);
            addr = ((hash % 400000) + 400000) & ~3ULL;
            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr) : "memory");

            hash = (hash  << 1) ^ (((int64_t)hash < 0) ? 7 : 0);
            addr = ((hash % 400000) + 0) & ~3ULL;
            __asm__ __volatile__ ("movl %2, (%0,%1)" : : "r"(gm), "r"(addr), "r"(tmpl) : "memory");

        }
        for(uint64_t loop1 = 0; loop1 < 100000ULL; loop1++){
            addr = 0 + (4 * loop1);
            __asm__ __volatile__ ("movl (%1,%2), %0" : "=r"(tmpl) : "r"(gm), "r"(addr) : "memory");

        }
    }
    goto block1;

block0:
    goto block2;

block1:
    free((void*)gm);
    return 0;
}
