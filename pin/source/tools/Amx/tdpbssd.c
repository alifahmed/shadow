/*
 * Copyright 2002-2020 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

/* @file
 * This test application execute tdpbssd instruction on tile registers.
 * It initialize the tile config and the tiles. Execute tdpbssd instruction and later store the result tile
 * into a result buffer/
 * It validates the result of this instruction by emulating what the instruction does according to the spec.
 *
 */
#include "tool_macros.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#if defined(_MSC_VER)
#define PRE_ALIGNTO(c) __declspec(align(c))
#define POST_ALIGNTO(c)
#elif defined(__GNUC__)
#define PRE_ALIGNTO(c)
#define POST_ALIGNTO(c) __attribute__((aligned(c)))
#else
#error "Could not find suitable compiler (MS or GNU)"
#endif

//
// Some macros for defining matrixes for tiles below (A,B,C,ref1)
//
#define NELEM 4 /* 4 int8 combine to 1 C type */
#define N 16
#define K 16
#define M 16
#define COLSB NELEM * 16

// Tile configuration register
PRE_ALIGNTO(64) static unsigned char POST_ALIGNTO(64) config_area[64];
PRE_ALIGNTO(64) static char POST_ALIGNTO(64) A[N * K * NELEM];  // matrix with N rows, K columns. Each with size NELEM. tmm1.
PRE_ALIGNTO(64) static char POST_ALIGNTO(64) B[K * M * NELEM];  // tmm0.
PRE_ALIGNTO(64) static char POST_ALIGNTO(64) B2[K * M * NELEM]; // Another tmm0, used when CalcResultWithB2 is true.

// tmm2. will contain result of AMX instruction being performed on tmm2,tmm1 and tmm0.
PRE_ALIGNTO(64) static int POST_ALIGNTO(64) C[N * M];

PRE_ALIGNTO(64) static int POST_ALIGNTO(64) res[N * M]; // Buffer to contain AMX result

// Contain reference matrix value being computed by emulating what the AMX instruction needs to do
// We compare the real AMX result (res buffer) with this reference
PRE_ALIGNTO(64) static int POST_ALIGNTO(64) ref1[N * M];

extern void Ldtilecfg(unsigned char* config_area) ASMNAME("Ldtilecfg");
extern void TileloaddT0(char* matrix, int stride) ASMNAME("TileloaddT0");
extern void TileloaddT1(char* matrix, int stride) ASMNAME("TileloaddT1");
extern void TileloaddT2(char* matrix, int stride) ASMNAME("TileloaddT2");
extern void TilestoredT2(char* matrix, int stride) ASMNAME("TilestoredT2");
extern void TdpbssdsT2T1T0() ASMNAME("TdpbssdsT2T1T0");

// true if tool will change tile registers. In that case the application is checking the results against B2 matrix
// which contain the expected values in TMM0 which will be modified by the tool
bool CalcResultWithB2 = false;

static inline void add_tile_to_config(int index, unsigned char* config_area, int rows, int cols, int element_size)
{
    int cols_offs = 16;
    int rows_offs = 48;

    config_area[cols_offs + (2 * index)] = cols * element_size;
    config_area[rows_offs + index]       = rows;
}

void init_config()
{
    memset(config_area, 0, sizeof(config_area));

    /* palette */
    config_area[0] = 1;

    /* init 3 tiles */
    add_tile_to_config(0, config_area, K, M, 4); /* B */
    add_tile_to_config(1, config_area, N, K, 4); /* A */
    add_tile_to_config(2, config_area, N, M, 4); /* C */
}

void test()
{
    init_config();

    Ldtilecfg(config_area);

    TileloaddT0(B, 16 * 4);
    TileloaddT1(A, 16 * 4);
    TileloaddT2((char*)C, 16 * 4);

    TdpbssdsT2T1T0();

    TilestoredT2((char*)res, 16 * 4);
}

void calc_ref(int* res)
{
    unsigned int i, n, k, m;

    // calculate res = A*B
    for (n = 0; n < N; n++)
    {
        for (k = 0; k < K; k++)
        {
            for (m = 0; m < M; m++)
            {
                unsigned int aidx = n * NELEM * K + NELEM * k;
                unsigned int bidx = k * NELEM * M + NELEM * m;
                unsigned int cidx = n * M + m;
                int sum           = 0;
                for (i = 0; i < NELEM; i++)
                {
                    if (CalcResultWithB2)
                    { // Tool changed TMM0 values into the value that exist in B2. Compute reference result based on B2.
                        sum += (int)A[aidx + i] * (int)B2[bidx + i];
                    }
                    else
                    {
                        sum += (int)A[aidx + i] * (int)B[bidx + i];
                    }
                }

                res[cidx] += sum;
            }
        }
    }
}

void init()
{
    int i, j;

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < COLSB; j++)
        {
            A[j + COLSB * i] = i;
            B[j + COLSB * i] = i;
            if (CalcResultWithB2) B2[j + COLSB * i] = i;
        }
    }

    if (CalcResultWithB2)
    { // Set different value for B2 (tool which change TMM0 values into these values.
        B2[150] = 0x23;
        B2[287] = 0xB8;
        B2[999] = 0x0;
    }

    memset(C, 0, sizeof(C));
    memset(ref1, 0, sizeof(ref1));

    calc_ref(ref1);
}

// Return 0 if 'refmat' matrix expected result is the the same as the actual result located in 'res' matrix.
// Return > 0 otherwise. The number returned is the number of diffs between the matrixes.
// If 10 diffs were already found, return immediately without checking for more diffs.
int check_test(int* refmat)
{
    int i, nerr = 0;

    for (i = 0; i < N * M; i++)
    {
        if (res[i] != refmat[i])
        {
            fprintf(stderr, "APP - tdpbssd: index: %d res: 0x%x ref: 0x%x\n", i, res[i], refmat[i]);
            nerr++;
        }

        if (nerr == 10)
        {
            fprintf(stderr, "APP - max errors found, exiting...\n");
            return nerr;
        }
    }

    return nerr;
}

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "2") == 0)
        {
            // See documentation of CalcResultWithB2.
            CalcResultWithB2 = true;
        }
    }

    int nerr;

    init();
    test();
    nerr = check_test(ref1);

    return nerr;
}
