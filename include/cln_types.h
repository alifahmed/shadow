#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <unistd.h>
//#include <string>
#include <cmath>
#include <iosfwd>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <stack>
#include <cassert>
#include <sstream>
#include <limits>
#include "pin.H"

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
class InsMem;


/*******************************************************************************
 * Defines
 ******************************************************************************/
#define MAX_STRIDE_BUCKETS  10
#define MIN_SZ              2048
#define MIN_ALIGNMENT       128
#define MAX_SMALL_TILES		  5
#define MAX_ADDRESS_RANGE   (1024ULL*1024ULL*1024ULL*16)
#define HASH_INIT_VALUE     (0xABCDEF94ED70BA3EULL)
#define _tab(x)             setw((x)*4) << " "


/*******************************************************************************
 * Type Defines
 ******************************************************************************/
typedef enum {InsTypeInvalid, InsTypeNormal, InsTypeSingleLoop, InsTypeMultiLoop, InsTypeCondJump, InsTypeRandFunc} InsType;
typedef enum {AccessTypeInvalid, AccessTypeRead, AccessTypeWrite, AccessTypeRMW} AccessType;
typedef enum {PatTypeInvalid, PatTypeConst, PatTypeSmallTile, PatTypeTile, PatTypeRefs, PatTypeDominant, PatTypeRandom, PatLoopIndexed} PatType;


typedef struct {
  AccessType accType;
  UINT32 accSz = 0;
} OpInfo;

typedef std::map<ADDRINT, InsMem*> InfoMap;
