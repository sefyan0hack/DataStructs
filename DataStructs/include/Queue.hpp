#pragma once

namespace sof
{
    template <typename T>
    class Queue
    {
       public:
        using value_type      = T;
        using reference       = value_type&;
        using size_type       = size_t;
        using const_reference = const value_type&;
        using pointer         = T*;

        Queue();
        Queue(size_type size, const value_type& init);
        ~Queue();

       private:
        size_type Capacity;
        size_type m_size;
        
        T* buffer;
        
        T* Head;
        T* Tail;
    };

}  // namespace sof