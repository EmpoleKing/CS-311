#ifndef COMPACT_QUEUE_H
#define COMPACT_QUEUE_H

#include <iostream>

using namespace std;

template<typename T>
class compact_queue
{
    T* data;
    bool full = false;
    size_t start = 0, last = 0; // last points to an empty spot
    size_t datasize;

    public:
        compact_queue(size_t size)
        {
            datasize = size;
            data = new T[size];
        }

        void enqueue(T item)
        {
            if (full)
            {
                T* new_data = new T[datasize * 2];
                for (size_t ndi = 0; ndi < datasize; ++ndi)
                {
                    new_data[ndi] = data[(ndi + start) % datasize];
                }
                delete[] data;
                data = new_data;
                last = datasize;
                start = 0;
                datasize = datasize * 2;
                full = false;
            }
            data[last] = item;
            last++;
            if (last == datasize)
                last = 0;
            if (last == start)
                full = true;
        }

        size_t size()
        {
            if (last > start)
                return last - start;
            if (full)
                return datasize;
            if (start > last)
                return datasize - start + last;
            return 0; // start and last are the same, full is false
        }

        void sort()
        {
            bool changed = true;
            size_t idx, idxplus;
            while (changed)
            {
                changed = false;
                for (auto& i : size() - 1)
                {
                    if (start < last)
                    {
                        idx = i + start;
                        idxplus = idx + 1;
                    }
                    else if (last <= start)
                    {
                        idx = i + start % datasize;
                        idxplus = (idx + 1) % datasize;
                    }
                    if (data[idx] > data[idxplus])
                    {
                        T temp = data[idx];
                        data[idx] = data[idxplus];
                        data[idxplus] = temp;
                        changed = true;
                    }
                }
            }
        }

        void printQueue(ostream& os) const
        {
            for (const auto& item : *this)
            {
                os << item << " ";
            }
        }

        bool empty()
        {
            return start == last && !full;
        }

        T dequeue()
        {
            if (full)
                full = false;
            return data[start++];
        }

        T* begin() const
        {
            return &data[start];
        }

        T* end() const
        {
            return &data[last];
        }

        ~compact_queue()
        {
            delete[] data;
        }
};

#endif