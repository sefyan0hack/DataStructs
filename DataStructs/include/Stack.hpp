#pragma once

/// @brief Forward declaration in std
namespace std
{
    template <typename T>
    class optional;  // Forward declaration of std::optional
}
namespace sof
{
    template <typename T>
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>) class Stack
    {
       public:
        using value_type      = T;
        using reference       = value_type&;
        using size_type       = size_t;
        using const_reference = const value_type&;
        using pointer         = T*;

       public:
        Stack();
        Stack(size_type max_size);
        Stack(const Stack& other);
        Stack operator=(const Stack& other);

       public:
        void push(const value_type& val);
        value_type pop();
        const_reference peek() const;
        size_type size() const;
        size_type max_size() const;

       public:
        std::string str() const;

       private:
        std::vector<value_type> m_container;
        size_type m_max_size;
    };

}  // namespace sof