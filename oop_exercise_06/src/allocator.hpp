#pragma once
#include <iostream>
#include <memory>
#include <queue>

template<class T, size_t BLOCK_COUNT = 100>
class myallocator {
    private:
        T* blocks;
        std::queue<T*> f_blocks;
    public:
        using value_type = T;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;

        myallocator() {
            static_assert(BLOCK_COUNT>0);
            blocks = (pointer)malloc(sizeof(value_type)*BLOCK_COUNT);
            for(size_t i = BLOCK_COUNT; i >= 0; i--)
            {
                f_blocks.push(blocks + i*sizeof(value_type));
            }        
        }
        ~myallocator(){
            free(blocks);
        }
            
        template<typename U>
        struct rebind {
            using other = myallocator<U>;
        };

        T* allocate(size_t n) {
            if(f_blocks.empty())
            {
                throw "my segment fault";
            }
            for(size_t i = 0; i < n; ++i)
            {
                return f_blocks.pop();
            }
        }

        void deallocate(T* pointer,  size_t n) {
            f_blocks.push(pointer);
        }


        template<typename U, typename ...Args>
        void construct(U *p, Args &&...args) {
            new (p) U(std::forward<Args>(args)...);
        }

        void destroy(pointer p) {
            p->~T();
        }

};