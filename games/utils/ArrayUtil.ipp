
#pragma once

#include "ArrayUtil.hpp"


void Alloc2dIntArray(int ***pArray, int size1, int size2, int resetTo)
{
    *pArray = new int* [size1];
    for (int i = 0; i < size1; i++)
    {
        (*pArray)[i] = new int [size2]{resetTo};
    }
}

void Free2dIntArray(int ***pArray, int size1, int size2)
{
    for (int i = 0; i < size1; i++)
    {
        delete [] (*pArray)[i];
    }
    delete [] *pArray;
}

void Expand2dIntArray_FromTo(int ***pArray, int oldSize1, int oldSize2, int newSize1, int resetTo)
{
    int** new_pointer_array = new int* [newSize1];

    int i;
    for (i = 0; i < oldSize1; i++)
    {
        new_pointer_array[i] = (*pArray)[i];
    }
    for (; i < newSize1; i++)
    {
        new_pointer_array[i] = new int [oldSize2]{resetTo};
    }


    delete [] (*pArray);

    (*pArray) = new_pointer_array;
}


