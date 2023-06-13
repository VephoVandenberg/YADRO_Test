#pragma once

#include <chrono>
#include <vector>
#include <fstream>

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

        void externalSort(const char *fInput, const char *fOutput);
        void createInitialRuns(const char *fInput);
        void mergeFiles(const char *fOutput);

        std::vector<std::string> m_tapeNames;
    };
}