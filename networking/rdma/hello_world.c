#include "hello_world.h"

int main(int argc, char *argv[], char *env[])
{
    int ndevs = 0;
    struct ibv_device** dev_list = ibv_get_device_list(&ndevs);

    printf("Device List is at: %p\n", (void *)dev_list);
    printf("Devices found: %d\n", ndevs);
    return 0;
}