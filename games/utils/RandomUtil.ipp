
#pragma once

#include <stdlib.h>
#include <stdio.h>

int _k_RandomGenerateMethod = RM_MIDDLESQUARE;
unsigned long _k_RandomSeed = 0;


// TODO : better pseudorandom algolisms.

// prototypes ====================================

// middlesquare ------------
#define _MIDDLESQUARE_MAXCHECKZERODEPTH 100
bool _MiddlesquareIsBadSeed(unsigned long seed);
unsigned long _MiddleSquare(void);

// ===============================================



int SetRandomMethod(int method, unsigned long seed)
{
    _k_RandomGenerateMethod = method;

    int retval = 0;
    switch (_k_RandomGenerateMethod)
    {

        case RM_MIDDLESQUARE:
            _k_RandomSeed = ((seed << 1) >> 1) + 0x8000;
            if (_MiddlesquareIsBadSeed(_k_RandomSeed) == true)
            {
                retval = 1;
            }
            break;

    }

    return retval;
}




unsigned long RandomNumber(void)
{
    switch (_k_RandomGenerateMethod)
    {
        case RM_MIDDLESQUARE:
            return _MiddleSquare();

        default:
            printf("randomUtil error : unknown generation method\n");
            exit(1);
            return 0;
    }
}



// definitions ===================================

// middlesquare ----------------------------------

unsigned long _MiddleSquare(void)
{
    unsigned long long square = (unsigned long long)_k_RandomSeed * (unsigned long long)_k_RandomSeed;
    square >>= 16;
    _k_RandomSeed = (unsigned long)square;
    return (unsigned long)square;
}

bool _MiddlesquareIsBadSeed(unsigned long seed)
{
    unsigned long seed_before = _k_RandomSeed;
    _k_RandomSeed = seed;

    bool is_bad_seed = false;

    for (int i = 0; i < _MIDDLESQUARE_MAXCHECKZERODEPTH; i++)
    {
        if (RandomNumber() == 0)
        {
            is_bad_seed = true;
            break;
        }
    }

    _k_RandomSeed = seed_before;
    return is_bad_seed;
}


#include "RandomUtil.hpp"

