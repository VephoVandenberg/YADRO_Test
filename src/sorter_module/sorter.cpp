#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "../tape/tape.h"

#include "min_heap.h"
#include "sorter.h"

using namespace SorterModule;

const char *g_configPath = "tape_config.json";
constexpr int g_sizeOfRun = 64;

Sorter::Sorter(const char *fInput, const char *fOutput)
{
    readConfig();
    externalSort(fInput, fOutput);
}

void Sorter::readConfig()
{
    // Future updates
}

void Sorter::externalSort(const char *fInput, const char *fOutput)
{
    createInitialRuns(fInput);
    mergeFiles(fOutput);
}

void Sorter::createInitialRuns(const char *fInput)
{
    std::ifstream input(fInput);
    if (!input.is_open()) { return; }

    bool eof = false;
    unsigned int iTempFile = 0;
    while (!eof)
    {
        std::vector<int> runData;
        for (unsigned int i = 0; i < g_sizeOfRun; i++)
        {
            if (input.peek() == EOF)
            {
                eof = true;
                break;
            }

            int data;
            input >> data;
            runData.push_back(data);
        }
        m_tapeNames.push_back("tmp/" + std::to_string(iTempFile) + ".txt");
        mergeSort(runData, 0, runData.size() - 1);
        std::ofstream tempTape(m_tapeNames.back());
        for (auto el : runData)
        {
            tempTape << el << "\n";
        }
        iTempFile++;
    }
    input.close();
}

void Sorter::mergeFiles(const char *fOutput)
{
    std::ofstream output(fOutput);

    std::vector<MinHeapNode> nodes;
    std::vector<std::ifstream> tapes;
    unsigned int i;

    for (i = 0; i < m_tapeNames.size(); i++)
    {
        tapes.push_back(std::ifstream(m_tapeNames[i]));
        MinHeapNode node;
        tapes[i] >> node.element;
        node.index = i;
        nodes.push_back(node);
    }

    MinHeap heap(nodes);
        std::cout << i << std::endl;

    int count = 0;
    while (count != i)
    {
        MinHeapNode root = heap.getMin();
        output << root.element << "\n";
        std::this_thread::sleep_for(std::chrono::nanoseconds(30));
        if (!(tapes.at(root.index) >> root.element))
        {
            root.element = INT32_MAX;
            count++;
        }

        heap.replaceMin(root);
    }
    for (auto& tape : tapes)
    {
        tape.close();
    }

    output.close();
}

void Sorter::merge(std::vector<int>& array, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (unsigned int i = 0; i < n1; i++)
    {
        L[i] = array[low + i];
    }

    for (unsigned int j = 0; j < n2; j++)
    {
        R[j] = array[mid + j + 1];
    }

    int i = 0;
    int j = 0;
    int k = low;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
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

    while (j < n2)
    {
        array[k++] = R[j++];
    }
}

void Sorter::mergeSort(std::vector<int>& array, int low, int high)
{
    if (low == high) { return; }

    int mid = low + (high - low) / 2;
    mergeSort(array, low, mid);
    mergeSort(array, mid + 1, high);

    merge(array, low, mid, high);
}
