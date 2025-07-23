#include <iostream>

template<typename T>
class HwAllocator {

private:
    // Our memory pool - pre-allocated chunk
    char* pool = nullptr;
    size_t pool_size = 0;
    char* next_free = nullptr;

    size_t POOL_SIZE = 1024; // 1KB pool

    // Initialize pool on first use
    void init_pool() {
        if (!pool) {
            pool = static_cast<char*>(std::malloc(POOL_SIZE));
            next_free = pool;
            pool_size = POOL_SIZE;
            std::cout << "Created memory pool of " << POOL_SIZE << " bytes\n";
        }
    }

    // Reset entire pool (custom function)
    void reset_pool() {
        if (pool) {
            next_free = pool;
            std::cout << "Pool reset - all memory available again\n";
        }
    }

    void cleanup() {
        if (pool) {
            std::cout << "\nCleaning up...\n";
            std::free(pool);
            pool = nullptr;
            std::cout << "Pool destroyed\n";
        }
    }

public:
    using value_type = T;

    HwAllocator(){
        init_pool();
    }

    ~HwAllocator(){
        cleanup();
    }


    template<typename U>
    HwAllocator(const HwAllocator<U>&) {}

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
        } else {
            std::cout << "Freeing non-pool memory\n";
            std::free(ptr);
        }
    }
};

template<typename T, typename U>
bool operator==(const HwAllocator<T>&, const HwAllocator<U>&) {
    return true;
}

template<typename T, typename U>
bool operator!=(const HwAllocator<T>&, const HwAllocator<U>&) {
    return false;
}
