#include "src/sorter_module/sorter.h"

#include <iostream>

int main(int argc, char **argv)
{
    SorterModule::Sorter* reader = new SorterModule::Sorter("input.bin", "output.bin");

    delete reader;
    return 0;
}
