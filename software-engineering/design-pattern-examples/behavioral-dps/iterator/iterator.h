/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

using namespace std;

class IntegerIterator
{

public:

    unique_ptr<int[]> currentInteger;

    int currentPosition;

    IntegerIterator(unique_ptr<int[]> integer)
    {

        currentInteger = move(integer);

        currentPosition = 0;

    }

    IntegerIterator(const IntegerIterator& other){}

    ~IntegerIterator() {}

    IntegerIterator operator++(int)
    {

        IntegerIterator temp = *this;

        currentPosition++;

        return temp;

    }

    IntegerIterator operator--(int)
    {

        IntegerIterator temp = *this;

        currentPosition--;

        return temp;

    }

    int operator*()
    {

        return currentInteger[currentPosition];

    }

};

#endif // ITERATOR_H