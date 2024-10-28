#pragma once

/// @brief Forward declaration in std
namespace std
{
    #ifndef _OPTIONAL_
    template <typename T>
    class optional;  // Forward declaration of std::optional
    #endif
}
namespace sof
{
    template <typename T>
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>) class Node
    {
       public:
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::forward_iterator_tag;

        value_type data;
        Node* next;
        Node(value_type value, Node* nextNode);
        bool operator==(const Node& other) const;
        bool operator!=(const Node& other) const;
    };

    template <typename T>
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>) class Iterator
    {
       public:
        using value_type        = T;
        using Node_t            = Node<value_type>;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
        using iterator_category = std::forward_iterator_tag;

        explicit Iterator(Node_t* node);
        T& operator*() const;
        // Pre-increment
        Iterator& operator++();
        // Post-increment
        Iterator operator++(int);
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

       private:
        Node_t* current;
    };

    /// @brief Linked List class
    /// @tparam T (int, float , string)
    template <typename T>
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>) class List
    {
       public:
        using value_type      = T;
        using Node_t          = Node<value_type>;
        using Iterator        = Iterator<value_type>;
        using reference       = value_type&;
        using const_reference = const value_type&;
        using difference_type = std::ptrdiff_t;
        using pointer         = T*;

        /// @brief Default Constructor List
        List();

        /// @brief Constructor reserving and init
        /// @param size init  size
        /// @param init init value
        List(size_t size, value_type init);

        /// @brief Copy Constructor
        /// @param other other List
        List(const List& other);

        /// @brief Destructor
        ~List();

        /// @brief Copy assignment Operator
        /// @param other other List
        /// @return List
        List operator=(const List& other);

        /// @brief index by value Operator
        /// @param index index you wnat to get
        /// @return underling Type if exist. and assert if index > size_t
        value_type operator[](size_t index) const;

        /// @brief index by reference Operator
        /// @param index index you wnat to set
        /// @return underling Type if exist. and assert if index > size_t
        reference operator[](size_t index);

        /// @brief check is list empty
        /// @return true if empty, else flase
        bool empty() const noexcept;

        /// @brief Get first element
        /// @return a  reference
        reference front();

        /// @brief Get first element
        /// @return a const reference
        const_reference front() const;

        /// @brief return Iterator to begin of List
        /// @return Iterator to begin of List . if list is empty Iterator(nullptr)
        Iterator begin();

        /// @brief return Iterator to end of List
        /// @return Iterator to end of List . if list is empty Iterator(nullptr)
        Iterator end();

        /// @brief inssert back
        /// @param value value of node
        void push_back(value_type value);

        /// @brief bush node befor pos
        /// @param pos pos you want to push befor it
        /// @param value value of node
        void push_befor(size_t pos, value_type value);

        /// @brief bush node after pos
        /// @param pos pos you want to push after it
        /// @param value value of node
        void push_after(size_t pos, value_type value);

        /// @brief Remove last element in list
        void pop();

        /// @brief Remove index the index in param
        /// @param pos Index to remove
        void remove(size_t pos);

        /// @brief Clear all list
        void clear();

        /// @brief Print to stdout str()
        void print() const;

        /// @brief Get list represntaion in strin
        /// @return List to string
        std::string str() const;

        /// @brief Get size of the list
        /// @return size
        size_t size() const noexcept;

        /// @brief Find index of elemnt in list
        /// @param val The value searching for
        /// @return Index of element, range(0, size-1), if std::nullopt
        std::optional<size_t> find(const value_type& val) const;

       private:
        size_t m_size;
        Node_t* Head;
    };

}  // namespace sof