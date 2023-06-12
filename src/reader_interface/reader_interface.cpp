#include <iostream>
#include <string>
#include <chrono>
#include <fstream>

#include "reader_interface.h"

using namespace SorterModule;

const std::string g_configPath = "tape_config.json";

Reader::Reader(const char *fInput, const char *fOutput)
{
    readConfig();
}

void Reader::readConfig()
{
    
}

void Reader::merge(std::vector<int>& array, int low, int mid, int high)
{
    int n1 = mid - low;
    int n2 = high - mid + 1;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
    {
        L[i] = array[low + i];
    }

    for (int j = 0; j < n2; j++)
    {
        R[j] = array[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] < R[j])
        {
            array[k++] = L[i++]; 
        }
        else 
        {
            array[k++] = R[j++];
        }
    }

    while (i < n1)
    {
        array[k++] = L[i++];
    }

    while (j < n1)
    {
        array[k++] = R[j++];
    }
}

void Reader::mergeSort(std::vector<int>& array, int low, int high)
{
    if (low == high) { return; }

    int mid = low + (high - low) / 2;
    mergeSort(array, low, mid);
    mergeSort(array, mid + 1, high);

    merge(array, low, mid, high);
}
