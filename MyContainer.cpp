// C++ program to implement a custom container class template with basic operations.
#include <iostream>
#include <iterator>
#include <stdexcept>
using namespace std;

// Custom container class template
template <class T, class Allocator = allocator<T>>
class MyContainer{
public:

    // Allocator type used for memory management
    using allocator_type = Allocator;

    // Reference type to the container's elements
    using reference = T &;

    // Constant reference type to the container's elements
    using const_reference = const T &;

    // Type for difference between iterator positions
    using difference_type = ptrdiff_t;

    // Iterator class for the custom container
    class iterator{
    public:
        // Type definitions for the iterator

        // Category tag for random access iterators
        using iterator_category = random_access_iterator_tag;

        // Type for difference between iterators
        using difference_type = ptrdiff_t;

        // Pointer type to the element
        using pointer = T *;
        // Reference type to the element
        using reference = T &;

        // Constructor to initialize the iterator with a pointer to an element
        iterator(pointer ptr) : ptr_(ptr) {
        }

        // Dereference operator to access the element pointed to by the iterator
        reference operator*() const{
            return *ptr_;
        }

        // Arrow operator to access the element's members
        pointer operator->() const{
            return ptr_;
        }

        // Prefix increment operator to move the iterator to the next element
        iterator &operator++(){
            ++ptr_;
            return *this;
        }

        // Postfix increment operator to move the iterator to the next element and return the previous
        // position
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        // Equality operator to compare if two iterators are equal (point to the same element)
        bool operator==(const iterator &other) const{
            return ptr_ == other.ptr_;
        }

        // Inequality operator to compare if two iterators are not equal (point to different elements)
        bool operator!=(const iterator &other) const{
            return ptr_ != other.ptr_;
        }

    private:
        pointer ptr_; // Pointer to the element the iterator currently points to
    };

    // Default constructor to create an empty container
    MyContainer() : data_(nullptr), size_(0), capacity_(0){
    }

    // Copy constructor to create a container as a copy of another container
    MyContainer(const MyContainer &other) : size_(other.size_), capacity_(other.capacity_){

        // Allocate memory for the elements
        data_ = allocator_type().allocate(capacity_);
        // Copy elements from the other container
        copy(other.data_, other.data_ + size_, data_);
    }

    // Destructor to clean up the allocated memory when the container is destroyed
    ~MyContainer(){
        // Deallocate the allocated memory
        allocator_type().deallocate(data_, capacity_);
    }

    // Member function to add a new element at the end of the container
    void push_back(const T &value){
        if (size_ == capacity_){

            // If the container is full, allocate more memory
            size_t new_capacity = capacity_ ? 2 * capacity_ : 1;
            T *new_data = allocator_type().allocate(new_capacity);
            copy(data_, data_ + size_, new_data);
            allocator_type().deallocate(data_, capacity_);
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_++] = value;
    }

    // Member function to remove the last element from the container
    void pop_back(){
        // Only remove if the container is not empty
        if (size_ > 0){
            --size_;
        }
    }

    // Member function to access an element at a given index with bounds checking
    reference at(size_t index){
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Const version of the 'at' function to access elements in a read-only context
    const_reference at(size_t index) const{
        if (index >= size_){

            // Throw an exception if the index is invalid
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // Member function to get the number of elements currently in the container
    size_t size() const{
        return size_;
    }

    // Member function to check if the container is empty
    bool empty() const{
        return size_ == 0;
    }

    // Member function to get an iterator pointing to the first element of the container
    iterator begin(){
        return iterator(data_);
    }

    // Member function to get an iterator pointing to the end (one past the last element) of the container
    iterator end(){
        return iterator(data_ + size_);
    }

private:
    // Pointer to the container's elements
    T *data_;

    // Number of elements in the container
    size_t size_;

    // Allocated capacity of the container
    size_t capacity_;
};

// Main function to test the custom container
int main()
{
    MyContainer<int> container;
    container.push_back(1);
    container.push_back(2);
    container.push_back(3);

    // Output the elements in the container after adding them
    cout << "Container elements after push_back operations: ";
    for (auto it = container.begin(); it != container.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    // Remove the last element from the container
    container.pop_back();

    // Output the elements in the container after removing the last one
    cout << "Container elements after pop_back operation: ";
    for (auto it = container.begin(); it != container.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    // Test accessing elements with bounds checking using the 'at' function
    try{
        cout << "Element at index 1: " << container.at(1) << endl;
        cout << "Element at index 2: " << container.at(2) << endl;
    }
    catch (const out_of_range &e){
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
