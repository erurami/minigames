
#pragma once

#define RM_MIDDLESQUARE 0
#define RM_LCG          1

void SetRamdomSeed(unsigned long seed);
int  SetRandomMethod(int method, unsigned long seed);

unsigned long RandomNumber(void);

#include "RandomUtil.ipp"

