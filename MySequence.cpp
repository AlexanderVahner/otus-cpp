#include <iostream>
#include <memory>
#include <cstdlib>

template <typename T, typename TAlloc = std::allocator<T>>
class MySequence {

private:
    using AllocTraits = std::allocator_traits<TAlloc>;

    TAlloc alloc;
    T* data;
    T* seeker;
    size_t capacity;
    size_t size;


public:
    MySequence() : alloc(TAlloc()), data(nullptr), capacity(0), size(0), seeker(nullptr)
    {
    }

    ~MySequence()
    {
        clear();
        AllocTraits::deallocate(alloc, data, capacity);
    }

    void reserve(size_t new_capacity)
    {
        if (new_capacity <= capacity) return;

        std::cout << "Resizing the sequence from " << capacity << " to " << new_capacity << "..." << std::endl;

        T* new_data = AllocTraits::allocate(alloc, new_capacity);
        if (data)
        {
            std::copy(data, data + size, new_data);
            AllocTraits::deallocate(alloc, data, capacity);
        }
        data = new_data;
        capacity = new_capacity;
    }

    void append(const T& value)
    {
        std::cout << "Appending an item to the sequence... " << std::endl;
        if (size >= capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }

        *(data + size) = value;
        size++;
        std::cout << "New sequence size is "<< size << std::endl;
    }

    void seek_start()
    {
        seeker = data;
    }

    T* next()
    {
        if (!seeker)
        {
            return seeker;
        }

        T* result = seeker;

        seeker = seeker + 1 >= data + size
            ? nullptr
            : seeker + 1;

        return result;
    }

    void clear() {
        size = 0;
    }

    size_t get_size() { return size; }
    size_t get_capacity() { return capacity; }
};
