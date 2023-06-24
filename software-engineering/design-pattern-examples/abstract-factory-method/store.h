/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef STORE_H
#define STORE_H

#include <string>

#include <iostream>

using namespace std;

// Abstract Store Class
class Store
{

public:

    string storeType;

private:

};

// Concreate Store Class for furniture
class FurnitureStore : public Store
{

public:

    FurnitureStore(string type)
    {
        storeType = type;
    }

    ~FurnitureStore() {}

};

// Concreate Store Class for appliances
class ApplianceStore : public Store
{

public:

    ApplianceStore(string type)
    {
        storeType = type;
    }
    ~ApplianceStore() {}

};


// Function for allocating a concreate Vehicle class
Store *getStore(string typeOfStore)
{
    Store *ret = NULL;

    if (typeOfStore.compare("Furniture")) {
        ret = new FurnitureStore(typeOfStore);
    }

    else if (typeOfStore.compare("Appliance")) {
        ret = new ApplianceStore(typeOfStore);
    }

    return ret;

}

#endif // STORE_H