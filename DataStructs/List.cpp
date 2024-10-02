#include <iostream>
#include <optional>
#include <sstream>
#include <cassert>
#include "include/List.hpp"

#pragma region List::Iterator
template<typename T>
List<T>::Iterator::Iterator(Node* node) : current(node) {}

template<typename T>
T& List<T>::Iterator::operator*() const { return current->data; }

template<typename T>
List<T>::Iterator& List<T>::Iterator::operator++() {
    current = current->next;
    return *this;
}

template<typename T>
List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return current == other.current;
}

template<typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}
#pragma endregion

#pragma region List
template<typename T>
List<T>::List(): m_size(0), Head(nullptr) {}

template<typename T>
List<T>::List(size_t size, value_type init):List(){
    for(size_t i = 0; i < size; i++){
        this->push_back(init);
    }
}

template<typename T>
List<T>::List(const List& other){
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

template<typename T>
List<T>::~List() {
    if(m_size > 0){
       clear();
    }
}

template<typename T>
List<T> List<T>::operator=(const List& other){
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

template<typename T>
List<T>::value_type List<T>::operator[](size_t index) const {
    assert(index < m_size);

    Node* current = Head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

template<typename T>
List<T>::reference List<T>::operator[](size_t index){
    assert(index < m_size);

    Node* current = Head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

template<typename T>
bool List<T>::empty() const noexcept {
    return m_size == 0;
}

template<typename T>
void List<T>::push_back(value_type value){
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

template<typename T>
void List<T>::push_at(size_t pos, value_type value){
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

template<typename T>
void List<T>::pop(){
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

template<typename T>
void List<T>::remove(size_t pos){
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

template<typename T>
void List<T>::clear() {
    Node* current = Head;

    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    
    Head = nullptr;
    m_size = 0;
    
}

template<typename T>
void List<T>::print() const {
    std::cout << str() << std::endl;
}

template<typename T>
std::string List<T>::str() const {
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

template<typename T>
std::optional<size_t> List<T>::find(const value_type& val) const {
    for (size_t i = 0; i < m_size; i++)
    {
        if((*this)[i] == val) {
            return i;
            break;
        }
    }
    return std::nullopt;
}

template<typename T>
List<T>::Iterator List<T>::begin() { return Iterator(Head); }

template<typename T>
List<T>::Iterator List<T>::end() { return Iterator(nullptr); }

template<typename T>
List<T>::reference List<T>::front(){
    if(this->empty())
        throw "Linked List is empty";
    return Head->data;
}

template<typename T>
size_t List<T>::size() const noexcept { return m_size; }

template<typename T>
List<T>::const_reference List<T>::front() const{    
    if(this->empty())
        throw "Linked List is empty";  
    return Head->data;
}

#pragma endregion
// Explicit template instantiation
template class List<int>;