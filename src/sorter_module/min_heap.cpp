#include <algorithm>

#include "min_heap.h"

using namespace SorterModule;

MinHeap::MinHeap(std::vector<MinHeapNode>& heap)
    : m_heap(heap)
{
    int i = (m_heap.size() - 1) / 2;
    while (i >= 0)
    {
        heapify(i);
        i--;
    }
}
        
void MinHeap::heapify(int i)
{
    int l = left(i);
    int r = right(i);
    int iSmallest = i;

    if (l < m_heap.size() && m_heap.at(l).element < m_heap.at(i).element)
    {
        iSmallest = l;
    }

    if (r < m_heap.size() &&  m_heap.at(r).element < m_heap.at(iSmallest).element)
    {
        iSmallest = r;
    }

    if (iSmallest != i)
    {
        std::swap(m_heap.at(i), m_heap.at(iSmallest));
        heapify(iSmallest);
    }
}

void MinHeap::replaceMin(MinHeapNode node)
{
    m_heap[0] = node;
    heapify(0);
}
