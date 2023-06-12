#include "src/sorter_module/sorter.h"

#include <iostream>
#include <cassert>

int main(int argc, char **argv)
{
    //assert(argv[0] != nullptr && argv[1] != nullptr); // Check if arguments are passed

    const char* fInput = argv[0];
    const char* fOutput = argv[1];

    SorterModule::Sorter* reader = new SorterModule::Sorter("input.txt", "output.txt");
    
    delete reader;
    return 0;
}
