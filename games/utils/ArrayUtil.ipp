
#pragma once

#include "ArrayUtil.hpp"


void Alloc2dArray(int ***pArray, int size1, int size2, int resetTo)
{
    *pArray = new int* [size1];
    for (int i = 0; i < size1; i++)
    {
        (*pArray)[i] = new int [size2](resetTo);
    }
}

void Free2dArray(int ***pArray, int size1, int size2)
{
    for (int i = 0; i < size1; i++)
    {
        delete [] (*pArray)[i];
    }
    delete [] *pArray;
}


