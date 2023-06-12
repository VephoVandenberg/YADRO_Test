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

    if (i < m_heap.size() && m_heap[l].element < m_heap[i].element)
    {
        iSmallest = l;
    }

    if (r < m_heap.size() && m_heap[r].element < m_heap[iSmallest].element)
    {
        iSmallest = r;
    }

    if (iSmallest != i)
    {
        std::swap(m_heap[i], m_heap[iSmallest]);
    }
}

void MinHeap::replaceMin(MinHeapNode node)
{
    m_heap[0] = node;
    heapify(0);
}
