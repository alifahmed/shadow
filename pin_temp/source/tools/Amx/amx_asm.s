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

#include <asm_macros.h>

.text

// void Ldtilecfg(unsigned char *config_area)
DECLARE_FUNCTION_AS(Ldtilecfg)
Ldtilecfg:

    BEGIN_STACK_FRAME

    mov       PARAM1, SCRATCH_REG1
    
    lea (SCRATCH_REG1), GAX_REG
    
    /* tileconfig [rax] */
    .byte 0xC4, 0xE2, 0x78, 0x49, 0x00

    END_STACK_FRAME

    ret


// void TileloaddT0(char *matrix, int stride)
DECLARE_FUNCTION_AS(TileloaddT0)
TileloaddT0:

    BEGIN_STACK_FRAME

    mov       PARAM1, SCRATCH_REG1
    mov       PARAM2, SCRATCH_REG2
    
    mov SCRATCH_REG2, GDX_REG
    lea (SCRATCH_REG1), GAX_REG
    
    /* tileloadd t0, [RAX + 1*RDX] */
    .byte 0xC4, 0xE2, 0x7B, 0x4B, 0x04, 0x10

    END_STACK_FRAME

    ret

// void TileloaddT1(char *matrix, int stride)
DECLARE_FUNCTION_AS(TileloaddT1)
TileloaddT1:

    BEGIN_STACK_FRAME

    mov       PARAM1, SCRATCH_REG1
    mov       PARAM2, SCRATCH_REG2
    
    mov SCRATCH_REG2, GDX_REG
    lea (SCRATCH_REG1), GAX_REG
    
    /* tileloadd t1, [RAX + 1*RDX] */
    .byte 0xC4, 0xE2, 0x7B, 0x4B, 0x0C, 0x10

    END_STACK_FRAME

    ret

// void TileloadT2(char *matrix, int stride)
DECLARE_FUNCTION_AS(TileloaddT2)
TileloaddT2:

    BEGIN_STACK_FRAME

    mov       PARAM1, SCRATCH_REG1
    mov       PARAM2, SCRATCH_REG2
    
    mov SCRATCH_REG2, GDX_REG
    lea (SCRATCH_REG1), GAX_REG
    
    /* tileloadd t2, [RAX + 1*RDX] */
    .byte 0xC4, 0xE2, 0x7B, 0x4B, 0x14, 0x10

    END_STACK_FRAME

    ret

// void TilestoredT2(char *matrix, int stride)
DECLARE_FUNCTION_AS(TilestoredT2)
TilestoredT2:

    BEGIN_STACK_FRAME

    mov       PARAM1, SCRATCH_REG1
    mov       PARAM2, SCRATCH_REG2
    
    mov SCRATCH_REG2, GDX_REG
    lea (SCRATCH_REG1), GAX_REG
    
    /* tilestored [RAX + 1*RDX], t2 */
    .byte 0xC4, 0xE2, 0x7A, 0x4B, 0x14, 0x10

    END_STACK_FRAME

    ret


// void TdpbssdsT2T1T0()
DECLARE_FUNCTION_AS(TdpbssdsT2T1T0)
TdpbssdsT2T1T0:

    BEGIN_STACK_FRAME
    
    /* tdpbssd t2, t1, t0 */
    .byte 0xC4, 0xE2, 0x7B, 0x5E, 0xD1

    END_STACK_FRAME

    ret
