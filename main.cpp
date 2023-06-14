#include "src/sorter_module/sorter.h"

#include <iostream>

int main(int argc, char **argv)
{
    SorterModule::Sorter* reader = new SorterModule::Sorter("input.txt", "output.txt");
    
    delete reader;
    return 0;
}
