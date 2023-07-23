#!/bin/bash

#
# Copyright (C) 2023 Matthew Leon
# SPDX-License-Identifier: BSD-3-Clause
#

# Compile the code
make

# Run the server in the network ns
sudo ip netns exec net0 ./client config.txt