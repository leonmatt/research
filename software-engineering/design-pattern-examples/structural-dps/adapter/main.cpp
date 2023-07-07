/*
Copyright (C) 2023 Matthew Leon
SPDX-License-Identifier: BSD-3-Clause
*/

#include <iostream>

#include "client.h"
#include "adapter.h"

using namespace std;

int main(void)
{
    // Create the Target
    Target *originalTarget = new Target();

    // Create the Target Adapter
    TargetAdapter *targetAdapter = new TargetAdapter(originalTarget);

    // Create the Client
    Client *client = new Client("1337");

    // Send the data from the client to the target using the adapter
    client->transferDataToTarget(targetAdapter);

    // Print out the data from the Target to make sure it was received
    cout << "DATA RECEIVED BY TARGET: " << originalTarget->getData() << endl;

    delete originalTarget;
    delete targetAdapter;
    delete client;

    // Create the Target
    Target *originalTarget = new Target();

    // Create the Target Adapter
    TargetAdapter *targetAdapter = new TargetAdapter(originalTarget);

    // Create the Client
    Client *client = new Client("1337");

    // Send the data from the client to the target using the adapter
    client->transferDataToTarget(targetAdapter);

    // Print out the data from the Target to make sure it was received
    cout << "DATA RECEIVED BY TARGET: " << originalTarget->getData() << endl;

    delete originalTarget;
    delete targetAdapter;
    delete client;

    // Create the Target
    Target *originalTarget = new Target();

    // Create the Target Adapter
    TargetAdapter *targetAdapter = new TargetAdapter(originalTarget);

    // Create the Client
    Client *client = new Client("1337");

    // Send the data from the client to the target using the adapter
    client->transferDataToTarget(targetAdapter);

    // Print out the data from the Target to make sure it was received
    cout << "DATA RECEIVED BY TARGET: " << originalTarget->getData() << endl;

    delete originalTarget;
    delete targetAdapter;
    delete client;

    // Create the Target
    Target *originalTarget = new Target();

    // Create the Target Adapter
    TargetAdapter *targetAdapter = new TargetAdapter(originalTarget);

    // Create the Client
    Client *client = new Client("1337");

    // Send the data from the client to the target using the adapter
    client->transferDataToTarget(targetAdapter);

    // Print out the data from the Target to make sure it was received
    cout << "DATA RECEIVED BY TARGET: " << originalTarget->getData() << endl;

    delete originalTarget;
    delete targetAdapter;
    delete client;

    return 0;

}