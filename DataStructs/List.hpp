#include <iostream>
#include <optional>
template<typename T>
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
        explicit Iterator(Node* node) : current(node) {}

        T& operator*() const { return current->data; }

        // Pre-increment
        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        // Post-increment
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
public:
    List(): m_size(0), Head(nullptr) {}
    List(size_t size, value_type init):List(){
        for(size_t i = 0; i < size; i++){
            this->push_back(init);
        }
    }
    List(const List& other){
         if (other.Head) {
            this->Head = new Node{other.Head->data, nullptr};
            Node* current = this->Head;
            m_size = 1;

            Node* otherCurrent = other.Head->next;
            while (otherCurrent) {
                m_size++;
                current->next = new Node{otherCurrent->data, nullptr};
                current = current->next;
                otherCurrent = otherCurrent->next;
            }
        } else {
            this->m_size = 0;
            this->Head = nullptr;
        }
    }
    List operator=(const List& other){
        if(this->m_size == other.m_size){
            for (size_t i = 0; i < this->m_size; i++)
            {
                (*this)[i] = other[i];
            }
        }
        else if(this->m_size < other.m_size){
            size_t i;
            for ( i = 0; i < this->m_size; i++)
            {
                (*this)[i] = other[i];
            }

            for (size_t j = i; j < other.m_size; j++)
            {
                this->push_back(other[j]);
            }
        }
        else{
            size_t i;
            size_t this_size = this->m_size;
            for ( i = 0; i < other.m_size; i++)
            {
                (*this)[i] = other[i];
            }
            for (size_t j = i; j < this_size; j++)
            {
                this->pop();
            }
        }
        return *this;
    }
    ~List() {
        if(m_size > 0){
           clear();
        }
    };
    /// @brief check is list empty 
    /// @return true if empty, else flase
    bool empty() const noexcept {
        return m_size == 0;
    }
    /// @brief Get first element
    /// @return a  reference
    reference front(){
        return Head->data;
    }
    /// @brief Get first element
    /// @return a const reference
    const_reference front() const{    
        return Head->data;
    }
    Iterator begin() { return Iterator(Head); }
    Iterator end() { return Iterator(nullptr); }
    /// @brief inssert back
    /// @param value value of node
    void push_back(value_type value){
        Node *n = new Node {.data = value, .next = nullptr};

        if (Head == nullptr) {
            Head = n;
        } else {
            Node *c = Head;
            while (c->next != nullptr) {
                c = c->next;
            }
            c->next = n;
        }

        m_size++;
    };
    /// @brief inssert at given pos
    /// @param pos position to inssert in
    /// @param value value of node
    void push_at(size_t pos, value_type value){
        assert(pos < m_size);
        Node *n = new Node {.data = value, .next = nullptr};
        if (pos == 0) {
            n->next = Head;
            Head = n;
        } else {
            Node *c = Head;
            for (size_t i = 0; i < pos - 1 ; i++) {
                c = c->next;
            }
            n->next = c->next;
            c->next = n;
        }
        m_size++;
    }
    /// @brief Remove last element in list
    void pop(){
        if (m_size == 1) {
            delete Head;
            Head = nullptr;
        } else {
            Node* c = Head;
            for (size_t i = 0; i < m_size - 2; i++) {
                c = c->next;
            }
            delete c->next;
            c->next = nullptr;
        }
        m_size--;
    }
    /// @brief Remove index the index in param
    /// @param pos Index to remove
    void remove(size_t pos){
        assert(pos < m_size);
        if (pos == 0) {
            Node* tmp = Head;
            Head = Head->next;
            delete tmp;
        } else {
            Node* c = Head;
            for (size_t i = 0; i < pos - 1; i++) {
                c = c->next;
            }
            Node* tmp = c->next;
            c->next = c->next->next;
            delete tmp;
        }
        m_size--;
    }
    /// @brief Clear all list
    void clear() {
        Node* current = Head;
    
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        
        Head = nullptr;
        m_size = 0;
        
    }
    /// @brief Print to stdout str()
    void print() const {
        std::cout << str() << std::endl;
    }
    /// @brief Get list represntaion in strin
    /// @return List to string
    std::string str() const {
        std::ostringstream oss;
        oss << "{ ";
        Node* c = Head;
        size_t i = 0;
        while (c != nullptr) {
            oss << "[" << i << "] = " << c->data;
            if (i < m_size - 1) {
                oss << ", ";
            }
            c = c->next;
            i++;
        }
        oss << " }" ;
        return oss.str();
    }
    /// @brief Get size of the list
    /// @return size
    size_t size() const noexcept { return m_size; }
    value_type operator[](size_t index) const {
        assert(index < m_size);
    
        Node* current = Head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        
        return current->data;
    }
    reference operator[](size_t index){
        assert(index < m_size);
    
        Node* current = Head;
        for (size_t i = 0; i < index; i++) {
            current = current->next;
        }
        
        return current->data;
    }
    /// @brief Find index of elemnt in list
    /// @param val The value searching for
    /// @return Index of element, range(0, size), if std::nullopt
    std::optional<size_t> find(const value_type& val) const {
        for (size_t i = 0; i < m_size; i++)
        {
            if((*this)[i] == val) {
                return i;
                break;
            }
        }
        return std::nullopt;
    }
private:
    void free_node(reference n){
        if(n != nullptr){
            delete n;
        }
    }
private:
    size_t m_size;
    Node* Head;
};

