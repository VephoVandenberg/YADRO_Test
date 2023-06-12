#pragma once

#include <chrono>
#include <vector>

namespace SorterModule
{
    class Reader 
    {
    public:
        Reader(const char *fInput, const char *fOutput);

        Reader() = default;
        ~Reader() = default;

        Reader(const Reader&) = delete;
        Reader& operator=(const Reader&) = delete;
        Reader(Reader&&) = delete;
        Reader& operator=(Reader&&) = delete;

    private:
        void readConfig();
        void merge(std::vector<int>& array, int low, int mid, int high);
        void mergeSort(std::vector<int>& array, int low, int high);
    };
}