#pragma once
#include <list>

namespace sof
{
    template < typename T, typename Cont = std::list<int> >
    class Queue
    {
       public:
        using value_type      = T;
        using reference       = value_type&;
        using size_type       = Cont::size_type;
        using const_reference = const value_type&;
        using pointer         = T*;
        
        using Cont_it         = Cont::iterator;


        Queue() = default;
        Queue(size_type size, value_type init);
        ~Queue() = default;

        size_type size() const noexcept;
        bool empty() const noexcept;
        void clear();

        void enqueue(const value_type& value);
        value_type dequeue();

        std::string str() const;
        void print() const;

       private:
        size_type Capacity;
        Cont buffer;

        value_type operator[](size_type index) const;
        
    };

}  // namespace sof