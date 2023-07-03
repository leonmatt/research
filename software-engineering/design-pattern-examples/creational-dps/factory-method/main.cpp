/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

# include "vehicle.h"

int main(void)
{

    // Vehicle for short distances
    Vehicle *VSD = getVehicle(1.0);

    // Vehicle for medium distances
    Vehicle *VMD = getVehicle(5.0);

    // Vehicle for long distances
    Vehicle *VLD = getVehicle(1000.0);

    // Release vehicles
    delete VSD;
    delete VMD;
    delete VLD;

    return 0;

}