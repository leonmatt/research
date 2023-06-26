/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#ifndef STORE_H
#define STORE_H

#include <string>

#include <iostream>

#include "appliance.h"
#include "furniture.h"

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

    Furniture *getFurniture(string type)
    {

        Furniture *ret = NULL;

        if (type.compare("Table") == 0) {
            cout << "Getting a Table" << endl;
            ret = new Table();
        }

        else if (type.compare("Couch") == 0) {
            cout << "Getting a Couch" << endl;
            ret = new Couch();
        }

        else if (type.compare("Chair") == 0) {
            cout << "Getting a Chair" << endl;
            ret = new Chair();
        }

        return ret;
    }

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

    Appliance *getAppliance(string type)
    {

        Appliance *ret = NULL;

        if (type.compare("Television") == 0) {
            cout << "Getting a Television" << endl;
            ret = new Television();
        }

        else if (type.compare("Stove") == 0) {
            cout << "Getting a Stove" << endl;
            ret = new Stove();
        }

        else if (type.compare("Refrigerator") == 0) {
            cout << "Getting a Refrigerator" << endl;
            ret = new Refrigerator();
        }

        return ret;
    }

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