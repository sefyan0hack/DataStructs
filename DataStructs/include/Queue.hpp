#pragma once

namespace std
{
    #ifndef _OPTIONAL_
    template <typename T>
    class optional;  // Forward declaration of std::optional
    #endif

    #ifndef _LIST_
    template <class T, class _Alloc = allocator<_Ty>>
    class list;
    #endif
}
namespace sof
{
    template <typename T, typename Cont = std::list<int>>
    class Queue
    {
       public:
        using value_type      = T;
        using reference       = value_type&;
        using size_type       = Cont::size_type;
        using const_reference = const value_type&;
        using pointer         = T*;
        
        using Cont_it         = Cont::iterator;


        Queue();
        Queue(size_type size, value_type init);
        ~Queue();

        size_type size() const noexcept;
        bool empty() const noexcept;

        void push(const value_type& value);
        void pop();

        value_type operator[](size_type index) const;
        std::string str() const;

       private:
        size_type Capacity;

        Cont buffer;

        Cont_it Head();
        Cont_it Tail();
    };

}  // namespace sof