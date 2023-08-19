/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <iostream>

#include <chrono>

using namespace std;


int main(int argc, char **argv)
{

    int n = 1000000;

    // BEING HOTPATH CODE
    auto start = chrono::high_resolution_clock::now();

    int *nums = new int[10];

    for(int i = 0; i < 1000000; i++) {}

    delete nums;

    // END HOTPATH CODE
    auto stop = chrono::high_resolution_clock::now();

    auto totalTime = chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "The hotpath took a total time of: " << totalTime.count() << " microseconds!" << endl;

    cout << "By not allocating the memory in the hot path, we save precious time doing the same work!" << endl;

    return 0;

}
