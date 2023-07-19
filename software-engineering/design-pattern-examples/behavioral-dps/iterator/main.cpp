/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <vector>
#include <iostream>

using namespace std;

int main(void)
{

    // Simple vector of integers
    vector<int> myIntVector;

    // Push some values into the vector
    for (int i = 0; i < 10; i++)
        myIntVector.push_back(i);

    // Dump the values using an iterator
    for (vector<int>::iterator i = myIntVector.begin(); i != myIntVector.end(); i++)
        cout << *i << endl;

    return 0;

}