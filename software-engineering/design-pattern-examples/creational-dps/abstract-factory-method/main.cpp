/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include "store.h"

int main(void)
{

    // Appliance Store/Factory
    ApplianceStore *AS = (ApplianceStore *)getStore("Application");
 
    // Furniture Store/Factory
    FurnitureStore *FS = (FurnitureStore *)getStore("Furniture");

    // Get a Television from the Appliance Factory
    Appliance *myTV = AS->getAppliance("Television");

    // Get a Couch from the Furniture Factory
    Furniture *myCouch = FS->getFurniture("Couch"); 

    // Release Products
    delete myTV;
    delete myCouch;

    // Release Stores
    delete AS;
    delete FS;

    return 0;

}