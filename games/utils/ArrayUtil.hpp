
#pragma once



// (*pArray)[size1][size2];
void Alloc2dIntArray(int ***pArray, int size1, int size2, int resetTo = 0);
void Free2dIntArray(int ***pArray, int size1, int size2);

// TODO :
// This will only support expanding the first dimention.
void Expand2dIntArray_FromTo(int ***pArray, int oldSize1, int oldSize2, int newSize1, int resetTo);

#include "ArrayUtil.ipp"

