#pragma once
/// @brief Forward declaration in std
namespace std {
    template <typename T>
    class optional;  // Forward declaration of std::optional
}

/// @brief Linked List class 
/// @tparam T (int, float , string)
template<typename T> requires (!std::is_same_v<T, const char*>) 
class List
{
    public:
    using value_type = T;
    using reference	= value_type&;
    using const_reference = const value_type&;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;

    struct Node
    {
        value_type data;
        Node* next;
        Node(value_type value, Node* nextNode);
    };

    class Iterator {
        private:
            Node* current;
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
        public:
            explicit Iterator(Node* node);

            T& operator*() const;

            // Pre-increment
            Iterator& operator++();

            // Post-increment
            Iterator operator++(int);
            bool operator==(const Iterator& other) const;
            bool operator!=(const Iterator& other) const;
    };
public:
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

    /// @brief inssert at given pos
    /// @param pos position to inssert in
    /// @param value value of node
    void push_at(size_t pos, value_type value);

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
    Node* Head;
};

