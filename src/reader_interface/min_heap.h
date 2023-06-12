#pragma once

#include <vector>

namespace SorterModule
{
    struct MinHeapNode
    {
        int element;
        int index;
        int iNextEl;
    };

    class MinHeap
    {
    public:
        MinHeap(std::vector<MinHeapNode>& heap);
        
        void heapify(int i);
        void replaceMin(MinHeapNode node);

        inline int left(int i) const { return 2 * i + 1; }
        inline int right(int i) const { return 2 * i + 2; }
        inline MinHeapNode getMin() const { return m_heap.front(); }

        MinHeap() = default;
        ~MinHeap() = default;
        MinHeap(MinHeap&&) = default;
        MinHeap& operator=(MinHeap&&) = default;

        MinHeap(const MinHeap&) = delete;
        MinHeap& operator=(const MinHeap&) = delete;

    private:
        std::vector<MinHeapNode> m_heap;
    };
} 
