/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <vector>
#include <iostream>

#include "iterator.h"

using namespace std;

int main(void)
{

    unique_ptr<int[]> myArray(new int[6]);

    for (int i = 0; i < 6; i++)
        myArray[i] = i + 1;

    Iterator<int> myIterator(move(myArray));

    for (int i = 0; i < 6; i++) {

        cout << *myIterator << endl;

        myIterator++;
    
    }

    return 0;

}