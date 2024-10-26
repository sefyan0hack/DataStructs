#pragma once

namespace std
{
    template <typename T>
    class optional;  // Forward declaration of std::optional
}
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
        Queue(size_type size, value_type init);
        ~Queue();

        size_type size() const noexcept;
        bool empty() const noexcept;

        void push(const value_type& value);

        value_type operator[](size_type index) const;
        std::string str() const;

       private:
        size_type Capacity;

        pointer buffer;

        pointer Head;
        pointer Tail;
    };

}  // namespace sof