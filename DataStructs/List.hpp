#include <iostream>

template<typename T>
class List
{
    public:
    using value_type = T;
    using reference	= value_type&;
    using const_reference = const value_type&;

    struct Node
    {
        value_type data;
        Node* next;
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
    bool empty() const noexcept {
        return m_size == 0;
    }
    reference front(){
        return Head->data;
    }
    const_reference front() const{    
        return Head->data;
    }
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
    void print() const {
        std::cout << str() << std::endl;
    }
    std::string str() const{
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

