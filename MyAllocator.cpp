#include <iostream>
#include <vector>
#include <memory>

// TRUE custom allocator - manages its own memory pool
template<typename T>
class MyAllocator {
private:
    // Our memory pool - pre-allocated chunk
    static char* pool;
    static size_t pool_size;
    static char* next_free;  // Points to next available memory

    static const size_t POOL_SIZE = 1024; // 1KB pool

    // Initialize pool on first use
    static void init_pool() {
        if (!pool) {
            pool = static_cast<char*>(std::malloc(POOL_SIZE));
            next_free = pool;
            pool_size = POOL_SIZE;
            std::cout << "Created memory pool of " << POOL_SIZE << " bytes\n";
        }
    }

public:
    using value_type = T;

    MyAllocator() = default;

    template<typename U>
    MyAllocator(const MyAllocator<U>&) {}

    // THIS IS THE CUSTOM PART - allocate from our pool, not system
    T* allocate(size_t n) {
        init_pool();

        size_t bytes_needed = n * sizeof(T);

        // Check if we have enough space in our pool
        if (next_free + bytes_needed > pool + pool_size) {
            std::cout << "Pool exhausted! Falling back to malloc\n";
            return static_cast<T*>(std::malloc(bytes_needed));
        }

        // Give memory from our pool
        T* result = reinterpret_cast<T*>(next_free);
        next_free += bytes_needed;

        std::cout << "Allocated " << bytes_needed << " bytes from pool\n";
        std::cout << "Pool usage: " << (next_free - pool) << "/" << pool_size << " bytes\n";

        return result;
    }

    // IMPORTANT: Pool allocator can't free individual pieces!
    // This is a limitation of simple pool allocators
    void deallocate(T* ptr, size_t n) {
        // Check if pointer is from our pool
        char* char_ptr = reinterpret_cast<char*>(ptr);
        if (char_ptr >= pool && char_ptr < pool + pool_size) {
            std::cout << "Deallocation request for pool memory (ignored - pool doesn't support individual frees)\n";
        }
        else {
            std::cout << "Freeing non-pool memory\n";
            std::free(ptr);
        }
    }

    // Reset entire pool (custom function)
    static void reset_pool() {
        if (pool) {
            next_free = pool;
            std::cout << "Pool reset - all memory available again\n";
        }
    }

    static void cleanup() {
        if (pool) {
            std::free(pool);
            pool = nullptr;
            std::cout << "Pool destroyed\n";
        }
    }
};

// Initialize static members
template<typename T>
char* MyAllocator<T>::pool = nullptr;

template<typename T>
size_t MyAllocator<T>::pool_size = 0;

template<typename T>
char* MyAllocator<T>::next_free = nullptr;

// Required comparison operators
template<typename T, typename U>
bool operator==(const MyAllocator<T>&, const MyAllocator<U>&) {
    return true;
}

template<typename T, typename U>
bool operator!=(const MyAllocator<T>&, const MyAllocator<U>&) {
    return false;
}