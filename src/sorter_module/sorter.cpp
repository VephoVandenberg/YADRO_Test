#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include "../tape/tape.h"

#include "min_heap.h"
#include "sorter.h"

using namespace SorterModule;

const char *g_configPath = "tape_config.json";
constexpr int g_sizeOfRun = 32;

Sorter::Sorter(const char *fInput, const char *fOutput)
    : m_inTape(fInput, TapeModule::Mode::Read)
    , m_outTape(fOutput, TapeModule::Mode::Write)
{
    readConfig();
    externalSort();
}

void Sorter::readConfig()
{
    // Future updates
}

void Sorter::externalSort()
{
    createInitialRuns();
    mergeFiles();
}

void Sorter::createInitialRuns()
{
    if (!m_inTape.isOpen()) { return; }

    bool eof = false;
    unsigned int iTempFile = 0;
    while (!eof)
    {
        std::vector<int> runData;
        for (unsigned int i = 0; i < g_sizeOfRun; i++)
        {
            int data;
            m_inTape.read(data);
            if (m_inTape.isEOF())
            {
                eof = true;
                break;
            }
            m_inTape.moveBackward();
            m_inTape.moveForward();
            std::cout << data << std::endl;
            runData.push_back(data);
        }
        m_tempTapes.push_back(
            TapeModule::Tape("tmp/" + std::to_string(iTempFile) + ".bin", TapeModule::Mode::Write));
        mergeSort(runData, 0, runData.size() - 1);
        for (auto el : runData)
        {
            m_tempTapes.back().write(el);
            m_tempTapes.back().moveBackward(); 
            m_tempTapes.back().moveForward();
        }
        iTempFile++;
    }
    std::cout << std::endl << std::endl;
}

void Sorter::mergeFiles()
{
    std::vector<MinHeapNode> nodes;
    std::vector<std::ifstream> tapes;
    unsigned int i;

    for (i = 0; i < m_tempTapes.size(); i++)
    {
        m_tempTapes[i].reload();
        m_tempTapes[i].toRead();

        if(m_tempTapes[i].getTapeLength() == 0)
        {
            break;
        }

        MinHeapNode node;
        m_tempTapes[i].read(node.element);
        m_tempTapes[i].moveBackward();
        m_tempTapes[i].moveForward();
        node.index = i;
        nodes.push_back(node);
    }

    MinHeap heap(nodes);

    int count = 0;
    while (count != i)
    {
        MinHeapNode root = heap.getMin();

        std::cout << root.element << std::endl;

        m_outTape.write(root.element);
        m_outTape.moveBackward();
        m_outTape.moveForward();

        m_tempTapes.at(root.index).read(root.element);
        m_tempTapes.at(root.index).moveBackward();
        m_tempTapes.at(root.index).moveForward();
        if (m_tempTapes.at(root.index).isEOF())
        {
            root.element = INT32_MAX;
            count++;
        }
    
        heap.replaceMin(root);
    }
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
    if (low < high) 
    {
        int mid = low + (high - low) / 2;
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);

        merge(array, low, mid, high);
    }
}
