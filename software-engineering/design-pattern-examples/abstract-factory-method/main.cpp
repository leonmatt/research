# include "store.h"

int main(void)
{

    // Applicane Store
    Store *AS = getStore("Furniture");

    // Furniture Store
    Store *FS = getStore("Furniture");

    // Release Stores
    delete AS;
    delete FS;

}