#!/bin/bash

# Set up network namespaces
sudo ip netns add nic1
sudo ip netns add nic2

# Bring the interface up
sudo ip link set enp1s0f0 up
sudo ip link set enp2s0f0 up

# Set up interface 1
sudo ip link set dev enp1s0f0 netns nic1
sudo ip netns exec nic1 ip link set enp1s0f0 up
sudo ip netns exec nic1 ifconfig enp1s0f0 10.0.1.5
sudo ip netns exec nic1 ip route add 10.0.1.6/32 via 10.0.1.5


# Set up interface 2
sudo ip link set dev enp2s0f0 netns nic2
sudo ip netns exec nic2 ip link set enp2s0f0 up
sudo ip netns exec nic2 ifconfig enp2s0f0 10.0.1.6
sudo ip netns exec nic2 ip route add 10.0.1.5/32 via 10.0.1.6

