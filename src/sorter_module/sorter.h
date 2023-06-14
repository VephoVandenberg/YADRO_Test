#pragma once

#include <chrono>
#include <vector>
#include <fstream>

#include "../tape/tape.h"

namespace SorterModule
{
    class Sorter 
    {
    public:
        Sorter(const char *fInput, const char *fOutput);

        Sorter() = default;
        ~Sorter() = default;

        Sorter(const Sorter&) = delete;
        Sorter& operator=(const Sorter&) = delete;
        Sorter(Sorter&&) = delete;
        Sorter& operator=(Sorter&&) = delete;

    private:
        void readConfig();
        void merge(std::vector<int>& array, int low, int mid, int high);
        void mergeSort(std::vector<int>& array, int low, int high);

        void externalSort();
        void createInitialRuns();
        void mergeFiles();

        TapeModule::Tape m_inTape;
        TapeModule::Tape m_outTape;
        std::vector<TapeModule::Tape> m_tempTapes;      
    };
}