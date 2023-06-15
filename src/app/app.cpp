#include <iostream>

#include "../sorter_module/sorter.h"

#include "app.h"

void printTapeData(const char *path);

void App::runLoop()
{
    SorterModule::Sorter* sorter = new SorterModule::Sorter();
    
    std::cout << "TAPE_SORTER" << std::endl;
    std::cout << "====================================================================" << std::endl;
    std::cout << "This program sorts tapes. Tapes use binary files to store their data." << std::endl;
    std::cout << "====================================================================" << std::endl;

    while (true)
    {
        std::string input;
        std::cout << "1 - Sort tape." << std::endl;
        std::cout << "2 - Print tape." << std::endl;
        std::cout << "3 - Quit." << std::endl;
        std::cout << "Your choise(1 - 3): "; std::cin >> input;

        if (input == "1")
        {
            std::string fIn, fOut;
            std::cout << "============================" << std::endl;
            std::cout << "Your input file: "; std::cin >> fIn;
            std::cout << "Your output file: "; std::cin >> fOut;
            if (sorter->externalSort(fIn.c_str(), fOut.c_str()))
            {
                std::cout << "STATUS::Success " << std::endl;
            }
            else 
            {
                std::cout << "============================" << std::endl;
                std::cout << "STATUS::Failed::(Perhaps your files are not falid.)" << std::endl;
                std::cout << "============================" << std::endl;
            }
        }
        else if (input == "2")
        {
            std::string path;
            std::cout << "Your file to read: "; std::cin >> path;
            std::cout << "============================" << std::endl;
            printTapeData(path.c_str());
            std::cout << "============================" << std::endl;
        }
        else if (input == "3")
        {
            break;
        }
    }

    delete sorter;
}

void printTapeData(const char* path)
{
    std::ifstream tapeFile(path, std::ios::binary);
    if (!tapeFile.is_open()) { return; }

    int data;
    while (tapeFile.read(reinterpret_cast<char*>(&data), sizeof(data)))
    {
        std::cout << data << std::endl;
    }

    tapeFile.close();
}
