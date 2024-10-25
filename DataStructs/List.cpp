#include <cassert>
#include <cstring>
#include <iostream>
#include <optional>
#include <sstream>
#include <type_traits>
#include "include/Config.hpp"
#include "include/List.hpp"

#define List_Init(t)             \
    template class sof::List<t>; \
    template class sof::Node<t>; \
    template class sof::Iterator<t>

using namespace sof;

#pragma region List::Node < T>

INL_TEMPL
Node<T>::Node(value_type value, Node *nextNode) : data(std::move(value)), next(nextNode) {}

INL_TEMPL
bool Node<T>::operator==(const Node<T> &other) const
{
    return this->data == other.data;
}

INL_TEMPL
bool Node<T>::operator!=(const Node<T> &other) const
{
    return this->data != other.data;
}
#pragma endregion

#pragma region List::Iterator

INL_TEMPL
Iterator<T>::Iterator(Node<T> *node) : current(node) {}

INL_TEMPL
T &Iterator<T>::operator*() const
{
    return current->data;
}

INL_TEMPL
Iterator<T> &Iterator<T>::operator++()
{
    current = current->next;
    return *this;
}

INL_TEMPL
Iterator<T> Iterator<T>::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

INL_TEMPL
bool Iterator<T>::operator==(const Iterator &other) const
{
    return current == other.current;
}

INL_TEMPL
bool Iterator<T>::operator!=(const Iterator &other) const
{
    return current != other.current;
}
#pragma endregion

#pragma region List
INL_TEMPL
List<T>::List() : m_size(0), Head(nullptr) {}

INL_TEMPL
List<T>::List(size_t size, value_type init) : List()
{
    for (size_t index = 0; index < size; index++)
    {
        this->push_back(init);
    }
}

INL_TEMPL
List<T>::List(const List &other)
{
    if (other.Head)
    {
        this->Head            = new Node<T>{other.Head->data, nullptr};
        Node<T> *current      = this->Head;
        m_size                = 1;
        Node<T> *otherCurrent = other.Head->next;
        while (otherCurrent)
        {
            m_size++;
            current->next = new Node<T>{otherCurrent->data, nullptr};
            current       = current->next;
            otherCurrent  = otherCurrent->next;
        }
    }
    else
    {
        this->m_size = 0;
        this->Head   = nullptr;
    }
}

INL_TEMPL
List<T>::~List()
{
    if (m_size > 0)
    {
        clear();
    }
}

INL_TEMPL
List<T> List<T>::operator=(const List &other)
{
    if (this->m_size == other.m_size)
    {
        for (size_t index = 0; index < this->m_size; index++)
        {
            (*this)[index] = other[index];
        }
    }
    else if (this->m_size < other.m_size)
    {
        size_t index;
        for (index = 0; index < this->m_size; index++)
        {
            (*this)[index] = other[index];
        }
        for (size_t jindex = index; jindex < other.m_size; jindex++)
        {
            this->push_back(other[jindex]);
        }
    }
    else
    {
        size_t index;
        size_t this_size = this->m_size;
        for (index = 0; index < other.m_size; index++)
        {
            (*this)[index] = other[index];
        }
        for (size_t jindex = index; jindex < this_size; jindex++)
        {
            this->pop();
        }
    }
    return *this;
}

INL_TEMPL
List<T>::value_type List<T>::operator[](size_t index) const
{
    assert(index < m_size);

    Node<T> *current = Head;
    for (size_t Iindex = 0; Iindex < index; Iindex++)
    {
        current = current->next;
    }

    return current->data;
}

INL_TEMPL
List<T>::reference List<T>::operator[](size_t index)
{
    assert(index < m_size);

    Node<T> *current = Head;
    for (size_t Iindex = 0; Iindex < index; Iindex++)
    {
        current = current->next;
    }

    return current->data;
}

INL_TEMPL
bool List<T>::empty() const noexcept
{
    return m_size == 0;
}

INL_TEMPL
void List<T>::push_back(value_type value)
{
    auto *newNode = new Node<T>(value, nullptr);
    if (Head == nullptr)
    {
        Head = newNode;
    }
    else
    {
        Node<T> *current = Head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }
    m_size++;
};

INL_TEMPL
void List<T>::push_befor(size_t pos, value_type value)
{
    assert(pos < m_size);
    auto *newNode = new Node<T>(value, nullptr);
    if (pos == 0)
    {
        newNode->next = Head;
        Head    = newNode;
    }
    else
    {
        Node<T> *current = Head;
        for (size_t index = 0; index < pos - 1; index++)
        {
            current = current->next;
        }
        Node<T> *tmp = current->next;
        current->next      = newNode;
        newNode->next      = tmp;
    }
    m_size++;
}

INL_TEMPL
void List<T>::push_after(size_t pos, value_type value)
{
    assert(pos < m_size);
    auto *newNode = new Node<T>(value, nullptr);
    if (pos == 0)
    {
        newNode->next = Head;
        Head    = newNode;
    }
    else
    {
        Node<T> *current = Head;
        for (size_t index = 0; index < pos; index++)
        {
            current = current->next;
        }
        Node<T> *tmp = current->next;
        current->next      = newNode;
        newNode->next      = tmp;
    }
    m_size++;
}

INL_TEMPL
void List<T>::pop()
{
    if (m_size == 1)
    {
        delete Head;
        Head = nullptr;
    }
    else
    {
        Node<T> *current = Head;
        for (size_t index = 0; index < m_size - 2; index++)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
    }
    m_size--;
}

INL_TEMPL
void List<T>::remove(size_t pos)
{
    assert(pos < m_size);
    if (pos == 0)
    {
        Node<T> *tmp = Head;
        Head         = Head->next;
        delete tmp;
    }
    else
    {
        Node<T> *current = Head;
        for (size_t index = 0; index < pos - 1; index++)
        {
            current = current->next;
        }
        Node<T> *tmp = current->next;
        current->next      = current->next->next;
        delete tmp;
    }
    m_size--;
}

INL_TEMPL
void List<T>::clear()
{
    Node<T> *current = Head;

    while (current != nullptr)
    {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }

    Head   = nullptr;
    m_size = 0;
}

INL_TEMPL
void List<T>::print() const
{
    std::cout << str() << std::endl;
}

INL_TEMPL
std::string List<T>::str() const
{
    std::ostringstream oss;
    oss << "{ ";
    Node<T> *current = Head;
    size_t index   = 0;
    while (current != nullptr)
    {
        oss << "[" << index << "] = " << current->data;
        if (index < m_size - 1)
        {
            oss << ", ";
        }
        current = current->next;
        index++;
    }
    oss << " }";
    return oss.str();
}

INL_TEMPL
std::optional<size_t> List<T>::find(const value_type &val) const
{
    for (size_t index = 0; index < m_size; index++)
    {
        if ((*this)[index] == val)
        {
            return index;
            break;
        }
    }
    return std::nullopt;
}

INL_TEMPL
Iterator<T> List<T>::begin()
{
    return Iterator(Head);
}

INL_TEMPL
Iterator<T> List<T>::end()
{
    return Iterator(nullptr);
}

INL_TEMPL
List<T>::reference List<T>::front()
{
    if (this->empty()){
        throw "Linked List is empty";
    }
    return Head->data;
}

INL_TEMPL
size_t List<T>::size() const noexcept
{
    return m_size;
}

INL_TEMPL
List<T>::const_reference List<T>::front() const
{
    if (this->empty()){
        throw "Linked List is empty";
    }
    return Head->data;
}

#pragma endregion

#pragma region Explicit template instantiation
List_Init(int);
List_Init(short);
List_Init(float);
List_Init(double);
List_Init(std::string);
#pragma endregion

#undef INL_TEMPL
#undef __TEMPL