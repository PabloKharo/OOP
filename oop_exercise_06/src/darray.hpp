#pragma once

#include <memory>
#include <iterator>
#include <string>
#include "allocator.hpp"

template<typename T>
class DarrIterator
{
private:
    T* p;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using reference = T&;
    DarrIterator(T* p) : p(p) {}
    DarrIterator(const DarrIterator& it) : p(it.p) {}

    bool operator!=(DarrIterator const& other) const {
        return p != other.p;
    }
    bool operator==(DarrIterator const& other) const {
        return p != other.p;
    }
    T& operator*() const {
        return *p;
    }
    DarrIterator& operator++() {
        ++p;
        return *this;
    }
};

template <class T, typename allocator = std::allocator<T>>
class DArray{
private:
    std::shared_ptr<T[]> data;
    size_t size;
public:
    using allocator_type = typename allocator::template rebind<T>::other;

    explicit DArray(size_t size_) 
    {
        size = size_;
        data = std::shared_ptr<T[]>(new T[size]);
    }

    T& operator[](size_t i)
    {
        if(i >= 0 && i < size)
            return data[i];
        else
            throw std::out_of_range{"Array index is out of range"};
    }

    T& operator=(DArray<T>& arr)
    {
        auto old_data = data;
        data = std::shared_ptr<T[]>(new T[arr.size]);
        for(size_t i = 0; i < std::min(arr.size, this->size); ++i)
            data[i] = old_data[i];
        size = arr.size; 
    }  

    size_t Size()
    {
        return size;
    }

    void Resize(size_t size_)
    {
        auto new_data = std::shared_ptr<T[]>(new T[size_]);
        for(size_t i = 0; i < std::min(size_, this->size); ++i)
            new_data[i] = data[i];
        data = new_data;
        size = size_;     
    }

    DarrIterator<T> begin()
    {
        return DarrIterator<T>(&data[0]);
    }

    DarrIterator<T> end()
    {
        return DarrIterator<T>(&data[size]);
    }

    const DarrIterator<T> cbegin()
    {
        return DarrIterator<T>(&data[0]);
    }

    const DarrIterator<T> cend()
    {
        return DarrIterator<T>(&data[size]);
    }

    static allocator_type get_allocator()
    {
        static allocator_type allocat;
        return allocat;
    }

    void* operator new(size_t sz){
        return get_allocator().allocate(sizeof(T));
    }
    void operator delete(void* p){
        get_allocator().destroy((T*)p);
        get_allocator().deallocate((T*)p, sizeof(T));
    }
};


