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

/*! @file
 * This tool check the IARG_REG_REFERENCE and IARG_REG_CONST_REFERENCE API are working for tile registers.
 * The tool is being used with tdpbssd.c application.
 * The tool uses the same input and does the same emulation of the TDPBSSD instruction that the application is doing.
 * This is in order to validate that the tile values Pin provides through IARG_REG_CONST_REFERENCE and such are correct.
 * The tool is being used in several tests. Documentation about each test can be found inside makefiles.tules.
 */

#include <iostream>
#include <fstream>
#include "pin.H"
using std::cerr;
using std::dec;
using std::endl;
using std::hex;
using std::ios;
using std::ofstream;
using std::string;

ofstream OutFile;

KNOB< string > KnobOutputFile(KNOB_MODE_WRITEONCE, "pintool", "o", "amx.out", "specify output file name");

// Test mode
// 1. default           - Verify Pin receive correct tile register values
// 2. modify            - Change tile value and verify correct result received
// 3. modify_tilecfg1   - Change tile config to a valid configuration. Application should fail.
// 4. modify_tilecfg2   - Change tile config to a non-valid configuration. Application should crash with illegal instruction.
KNOB< string > KnobMode(KNOB_MODE_WRITEONCE, "pintool", "mode", "default",
                        "specify test mode (default/modify/modify_tilecfg1/modify_tilecfg2).");

// Verbose mode. on by default
KNOB< BOOL > KnobVerbose(KNOB_MODE_WRITEONCE, "pintool", "verbose", "1", "verbose mode");

//
// Some macros for defining matrixes for tiles below (A,B,C,ref1)
//
#define NELEM 4 /* 4 int8 combine to 1 C type */
#define N 16
#define K 16
#define M 16
#define COLSB NELEM * 16

//
// Below buffers equal to the parallel application buffers (used by the application with the same name)
// We set it the same way they are being set by the application in order to later validated Pin instrumentation API
// such as REG_REFERENCE to REG_TMM0 (for example)
//
// config_area[] contain the application tile configuration register.
PRE_ALIGNTO(64) static unsigned char POST_ALIGNTO(64) config_area[64];
PRE_ALIGNTO(64) static char POST_ALIGNTO(64) A[N * K * NELEM]; // matrix with N rows, K columns. Each with size NELEM. tmm1.
PRE_ALIGNTO(64) static char POST_ALIGNTO(64) B[K * M * NELEM]; // tmm0
PRE_ALIGNTO(64) static int POST_ALIGNTO(64) C[N * M];          // tmm2

PRE_ALIGNTO(64) static int POST_ALIGNTO(64) ref1[N * M];

// This is what the application does:
//
//    init_config();
//
//    Ldtilecfg(config_area);
//
//    TileloaddT0(B, 16*4);
//    TileloaddT1(A, 16*4);
//    TileloaddT2((char*)C, 16*4);
//
//    TdpbssdsT2T1T0();
//
//    TilestoredT2((char*)res, 16*4);
//

// Update tile configuration with a specific (index) tile register information (rows & cols)
static inline void add_tile_to_config(int index, unsigned char* config_area, int rows, int cols, int element_size)
{
    int cols_offs = 16;
    int rows_offs = 48;

    config_area[cols_offs + (2 * index)] = cols * element_size;
    config_area[rows_offs + index]       = rows;
}

// Initialize tile configuration for tmm0, tmm1 and tmm2
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

// Calculate Tdpbssds value of A and B and store in res
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
                    sum += (int)A[aidx + i] * (int)B[bidx + i];

                res[cidx] += sum;
            }
        }
    }
}

// Initialize A and B matrixes + calculate Tdpbssds value of A and B and store in ref1 (as reference)
void Init()
{
    int i, j;

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < COLSB; j++)
        {
            A[j + COLSB * i] = i;
            B[j + COLSB * i] = i;
        }
    }
    if (KnobMode.Value() == "modify")
    {
        B[150] = 0x23;
        B[287] = 0xB8;
        B[999] = 0x0;
    }

    memset(C, 0, sizeof(C));
    memset(ref1, 0, sizeof(ref1));

    calc_ref(ref1);
}

void checkVsExpected(UINT8* lRef, PIN_WIDE_REGISTER* tmm)
{
    int i, nerr = 0;

    //    OutFile << endl;
    //    OutFile << REG_StringShort(tmmDestReg)
    //    OutFile << endl;

    for (i = 0; i < (N * K * NELEM); i++)
    {
        if (tmm->byte[i] != lRef[i])
        {
            fprintf(stderr, "tdpbssd: index: %d res: 0x%.2x ref: 0x%.2x\n", i, tmm->byte[i], lRef[i]);
            nerr++;
        }

        if (nerr == 10)
        {
            fprintf(stderr, "max errors found, exiting...\n");
            ASSERT(0, "max errors found, aborting...");
        }
    }

    if (nerr)
    {
        ASSERT(0, "Errors found, aborting\n");
        ;
    }
}

// Check tmm0 value received against reference matrix B
void CheckTMM0(ADDRINT* ip, PIN_WIDE_REGISTER* tmm0, ADDRINT* secondIp)
{
    int i, nerr = 0;

    // Extra verification for some bug I saw.
    ASSERTX(*ip == *secondIp);

    //    OutFile << endl;
    //    OutFile << REG_StringShort(tmmDestReg)
    //    OutFile << endl;

    for (i = 0; i < (N * K * NELEM); i++)
    {
        if (tmm0->byte[i] != B[i])
        {
            fprintf(stderr, "tdpbssd: index: %d res: 0x%.2x ref: 0x%.2x\n", i, tmm0->byte[i], B[i]);
            nerr++;
        }

        if (nerr == 10)
        {
            fprintf(stderr, "max errors found, exiting...\n");
            ASSERT(0, "max errors found, aborting...");
        }
    }

    if (nerr)
    {
        ASSERT(0, "Errors found, aborting\n");
        ;
    }
}

// Check tmmDestReg value received against reference matrix ref1 (which contain the result of TDPBSSDS on A & B
void CheckResult(ADDRINT* ip, PIN_WIDE_REGISTER* tmmDestReg, PIN_WIDE_REGISTER* tmm0)
{
    int i, nerr = 0;

    if (KnobMode.Value() == "modify")
    {
        // Verify tmm0 register was change correctly by this tool in ModifyTMM0
        ASSERTX(tmm0->byte[150] == 0x23);
        ASSERTX(tmm0->byte[287] == 0xB8);
        ASSERTX(tmm0->byte[999] == 0x0);
    }

    //    OutFile << endl;
    //    OutFile << REG_StringShort(tmmDestReg)
    //    OutFile << endl;

    for (i = 0; i < N * M; i++)
    {
        if (tmmDestReg->s_dword[i] != ref1[i])
        {
            fprintf(stderr, "tdpbssd: index: %d res: 0x%.8x ref: 0x%.8x\n", i, tmmDestReg->s_dword[i], ref1[i]);
            nerr++;
        }

        if (nerr == 10)
        {
            fprintf(stderr, "max errors found, exiting...\n");
            ASSERT(0, "max errors found, aborting...");
        }
    }

    if (nerr)
    {
        ASSERT(0, "Errors found, aborting\n");
        ;
    }
}

// Return reference matrix pointer based of Pin tile register received: REG_TMM0->B, REG_TMM1->A, REG_TMM2->ref1)
UINT8* GetRef(REG tileReg) { return (UINT8*)((tileReg == REG_TMM0) ? B : (tileReg == REG_TMM1) ? A : (char*)ref1); }

// Check all tile values against A, B and ref1. (tmm0->B, tmm1->A, tmm2->ref1).
// tile0 can be tmm0/tmm1/tmm2. tileReg0 specify which REG_TMM* was passed.
// Checking correct value is recieved for differen order (tmm0,tmm1,tmm2 / tmm2,tmm1,tmm0 / ...)
void CheckAll(REG tileReg0, PIN_WIDE_REGISTER* tile0, REG tileReg1, PIN_WIDE_REGISTER* tile1, REG tileReg2,
              PIN_WIDE_REGISTER* tile2)
{
    checkVsExpected(GetRef(tileReg0), tile0);
    checkVsExpected(GetRef(tileReg1), tile1);
    checkVsExpected(GetRef(tileReg2), tile2);
}

// Another check
void CheckResultBeforeTileStore(UINT8* lRef, PIN_WIDE_REGISTER* tmm) { checkVsExpected(lRef, tmm); }

// Modify tmm0 value
void ModifyTMM0(PIN_WIDE_REGISTER* tmm0)
{
    tmm0->byte[150] = 0x23;
    tmm0->byte[287] = 0xB8;
    tmm0->byte[999] = 0x0;
}

// The running count of instructions is kept here
// make it static to help the compiler optimize docount
static UINT64 icount                   = 0;
static const UINT32 TILE_SIZE          = 1024;
static const UINT32 NUM_QWORD_ELEMENTS = TILE_SIZE / 8;

VOID CheckTileConfig(ADDRINT* ip, PIN_REGISTER* tileConfig)
{
    if (KnobVerbose)
    {
        OutFile << endl;
        OutFile << "Before: " << endl;
        ;
        OutFile << hex << "ip = " << *ip << endl;
        OutFile << dec << "Tile config:" << endl;
        OutFile << "[0]palette: " << (unsigned int)tileConfig->byte[0] << endl;
        OutFile << "[1]starts_row: " << (unsigned int)tileConfig->byte[1] << endl;
    }

    ASSERTX(tileConfig->word[1] == 0);
    ASSERTX(tileConfig->dword[1] == 0);
    ASSERTX(tileConfig->qword[1] == 0);

    if (KnobMode.Value().find("modify_tilecfg") != std::string::npos)
    { // Modify tile configuration register
        if (KnobMode.Value() == "modify_tilecfg2")
        {
            // Modify tile1 rows to 12. This will create a non valid tile for tpsdsss instruction which will crash
            // the application with illegal instruction. A[16, 3] B[8,16] (instead of A[16, 16] B[16,16])
            tileConfig->byte[18] = 12; // tile 1 column [16,3]. Every element in row is four bytes
        }
        else
        { // modify_tilecfg1
            // Modify tile1 rows to 32. This will create a valid tile for tpsdsss which will only make the application fail.
            // A[16, 8] B[8,16] (instead of A[16, 16] B[16,16])
            tileConfig->byte[18] = 32; // tile 1 column [16,8] Every element in row is four bytes
        }
        tileConfig->byte[48] = 8; // tile 0 row  [8,16]
    }

    if (KnobVerbose)
    {
        OutFile << "[16-17]tile0.colsb: " << (unsigned int)tileConfig->word[8] << endl;  // tileConfig->byte[16-17]
        OutFile << "[18-19]tile1.colsb: " << (unsigned int)tileConfig->word[9] << endl;  // tileConfig->byte[18-19]
        OutFile << "[20-21]tile2.colsb: " << (unsigned int)tileConfig->word[10] << endl; // tileConfig->byte[20-21]
        OutFile << "[22-23]tile3.colsb: " << (unsigned int)tileConfig->word[11] << endl; // tileConfig->byte[22-23]
        OutFile << "[24-25]tile4.colsb: " << (unsigned int)tileConfig->word[12] << endl; // tileConfig->byte[24-25]
        OutFile << "[26-27]tile5.colsb: " << (unsigned int)tileConfig->word[13] << endl; // tileConfig->byte[26-27]
        OutFile << "[28-29]tile6.colsb: " << (unsigned int)tileConfig->word[14] << endl; // tileConfig->byte[28-29]
        OutFile << "[30-31]tile7.colsb: " << (unsigned int)tileConfig->word[15] << endl; // tileConfig->byte[30-31]
    }

    ASSERTX(tileConfig->qword[4] == 0);
    ASSERTX(tileConfig->qword[5] == 0);

    if (KnobVerbose)
    {
        OutFile << "[48]tile0.rows: " << (unsigned int)tileConfig->byte[48] << endl;
        OutFile << "[49]tile1.rows: " << (unsigned int)tileConfig->byte[49] << endl;
        OutFile << "[50]tile2.rows: " << (unsigned int)tileConfig->byte[50] << endl;
        OutFile << "[51]tile3.rows: " << (unsigned int)tileConfig->byte[51] << endl;
        OutFile << "[52]tile4.rows: " << (unsigned int)tileConfig->byte[52] << endl;
        OutFile << "[53]tile5.rows: " << (unsigned int)tileConfig->byte[53] << endl;
        OutFile << "[54]tile6.rows: " << (unsigned int)tileConfig->byte[54] << endl;
        OutFile << "[55]tile7.rows: " << (unsigned int)tileConfig->byte[55] << endl;
    }

    ASSERTX(tileConfig->qword[7] == 0);

    if (KnobMode.Value().find("modify_tilecfg") != std::string::npos)
    {
        // We changed tile configuration. So don't check against config_area.
        return;
    }

    // Verify tile config recieved is identical to config_area reference
    for (UINT64 i = 0; i < MAX_QWORDS_PER_PIN_REG; i++)
    {
        ASSERT(tileConfig->qword[i] == ((UINT64*)config_area)[i], "i = " + decstr(i) +
                                                                      ", tileConfig->qword[i] = " + hexstr(tileConfig->qword[i]) +
                                                                      ", config_area[i] = " + hexstr(((UINT64*)config_area)[i]));
    }
}

// Spill intruction file regiser data into log file
VOID AnalyzeTileRegAfter(ADDRINT* ip, PIN_WIDE_REGISTER* tmm, ADDRINT* rax, REG tileReg, BOOL isRead, BOOL isWrite)
{
    OutFile << endl;
    OutFile << REG_StringShort(tileReg) << " " << (isRead ? "READ" : "") << (isWrite ? "WRITE" : "") << endl;
    OutFile << hex << "ip = " << *ip << ", rax = " << *rax << endl;

    OutFile << "After: " << endl;
    const UINT32 elements = NUM_QWORD_ELEMENTS;
    for (UINT32 i = 0; i < elements; i++)
    {
        OutFile << "tile[" << dec << i << "] = 0x" << hex << tmm->qword[i] << ", ";
    }
    OutFile << endl;

    icount++;
}

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID* v)
{
    if (INS_IsAmx(ins))
    {
        if (KnobVerbose)
        {
            OutFile << "      " << hex << INS_Address(ins);
            OutFile << " " << INS_Disassemble(ins);

            OutFile << " reads:";
            for (UINT32 i = 0; i < INS_MaxNumRRegs(ins); i++)
            {
                OutFile << " " << REG_StringShort(INS_RegR(ins, i));
            }
            OutFile << " writes:";
            for (UINT32 i = 0; i < INS_MaxNumWRegs(ins); i++)
            {
                OutFile << " " << REG_StringShort(INS_RegW(ins, i));
            }
            OutFile << endl;
        }

        if (INS_Opcode(ins) == XED_ICLASS_LDTILECFG)
        {
            // Check tile config register against config_area reference value
            INS_InsertCall(
                ins, IPOINT_AFTER, (AFUNPTR)CheckTileConfig, IARG_REG_CONST_REFERENCE, REG_RIP,
                ((KnobMode.Value().find("modify_tilecfg") != std::string::npos) ? IARG_REG_REFERENCE : IARG_REG_CONST_REFERENCE),
                REG_TILECONFIG, IARG_END);
        }

        if (KnobVerbose)
        {
            UINT32 operandCount = INS_OperandCount(ins);
            UINT32 i;

            for (i = 0; i < operandCount; i++)
            {
                if (INS_OperandIsReg(ins, i))
                {
                    REG tileReg = INS_OperandReg(ins, i);

                    if (REG_is_tmm(tileReg))
                    {
                        // This is just for verbose
                        INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)AnalyzeTileRegAfter, IARG_REG_CONST_REFERENCE, REG_RIP,
                                       IARG_REG_CONST_REFERENCE, tileReg, IARG_REG_CONST_REFERENCE, REG_RAX, IARG_UINT32, tileReg,
                                       IARG_BOOL, INS_OperandRead(ins, i), IARG_BOOL, INS_OperandWritten(ins, i), IARG_END);
                    }
                }
            }
        }

        if (INS_Opcode(ins) == XED_ICLASS_TILELOADD)
        {
            REG tmm0Reg = INS_RegW(ins, 0);
            if (tmm0Reg == REG_TMM0)
            {
                if (KnobMode.Value() == "modify")
                {
                    // Change TMM0 value (B0)
                    INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)ModifyTMM0, IARG_REG_REFERENCE, tmm0Reg, IARG_END);
                }
                else if (KnobMode.Value() == "default")
                {
                    // Check TMM0 register against A matrix reference value
                    INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)CheckTMM0, IARG_REG_CONST_REFERENCE, REG_RIP,
                                   IARG_REG_CONST_REFERENCE, tmm0Reg, IARG_REG_CONST_REFERENCE, REG_RIP, IARG_END);
                }
            }
        }

        if (INS_Opcode(ins) == XED_ICLASS_TDPBSSD)
        {
            // Check TMM2 register against ref1 matrix reference value
            // TMM2 contain result of TDPBSSDS instruction on TMM1 and TMM0.
            // ref1 contain result of TDPBSSDS calculation on A and B.
            // TMM2 should be equal to ref1.
            REG tileDestReg = INS_RegW(ins, 0);
            INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)CheckResult, IARG_REG_CONST_REFERENCE, REG_RIP, IARG_REG_CONST_REFERENCE,
                           tileDestReg, IARG_REG_CONST_REFERENCE, REG_TMM0, IARG_END);

            //
            // Now check TMM1, TMM0 and TMM2 values against A, B and ref1 matrixes in different oreders.
            // This is in order to make sure pass the values correctly.
            //

            INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)CheckAll, IARG_UINT32, REG_TMM0, IARG_REG_CONST_REFERENCE, REG_TMM0,
                           IARG_UINT32, REG_TMM1, IARG_REG_CONST_REFERENCE, REG_TMM1, IARG_UINT32, REG_TMM2,
                           IARG_REG_CONST_REFERENCE, REG_TMM2, IARG_END);
            INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)CheckAll, IARG_UINT32, REG_TMM2, IARG_REG_CONST_REFERENCE, REG_TMM2,
                           IARG_UINT32, REG_TMM1, IARG_REG_CONST_REFERENCE, REG_TMM1, IARG_UINT32, REG_TMM0,
                           IARG_REG_CONST_REFERENCE, REG_TMM0, IARG_END);
            INS_InsertCall(ins, IPOINT_AFTER, (AFUNPTR)CheckAll, IARG_UINT32, REG_TMM1, IARG_REG_CONST_REFERENCE, REG_TMM1,
                           IARG_UINT32, REG_TMM2, IARG_REG_CONST_REFERENCE, REG_TMM2, IARG_UINT32, REG_TMM0,
                           IARG_REG_CONST_REFERENCE, REG_TMM0, IARG_END);
        }

        if (INS_Opcode(ins) == XED_ICLASS_TILESTORED)
        {
            // another check
            INS_InsertCall(ins, IPOINT_BEFORE, (AFUNPTR)CheckResultBeforeTileStore, IARG_ADDRINT, (char*)ref1,
                           IARG_REG_CONST_REFERENCE, REG_TMM2, IARG_END);
        }
    }
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID* v)
{
    // Write to a file since cout and cerr maybe closed by the application
    OutFile.setf(ios::showbase);
    OutFile << "Count " << icount << endl;
    OutFile.close();
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    cerr << "This tool counts the number of dynamic instructions executed" << endl;
    cerr << endl << KNOB_BASE::StringKnobSummary() << endl;
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */
/*   argc, argv are the entire command line: pin -t <toolname> -- ...    */
/* ===================================================================== */

int main(int argc, char* argv[])
{
    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    OutFile.open(KnobOutputFile.Value().c_str());

    Init();
    init_config();

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);

    // Start the program, never returns
    PIN_StartProgram();

    return 0;
}
