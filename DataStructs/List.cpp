#include <cassert>
#include <cstring>
#include <iostream>
#include <optional>
#include <sstream>
#include <type_traits>
#include "include/List.hpp"

#define __TEMPL           \
    template <typename T> \
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>)
#define INL_TEMPL __TEMPL inline

#define List_Init(t)             \
    template class sof::List<t>; \
    template class sof::Node<t>; \
    template class sof::Iterator<t>

using namespace sof;

#pragma region List::Node < T>

INL_TEMPL
Node<T>::Node(value_type value, Node *nextNode) : data(value), next(nextNode) {}

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
    for (size_t i = 0; i < size; i++)
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
        for (size_t i = 0; i < this->m_size; i++)
        {
            (*this)[i] = other[i];
        }
    }
    else if (this->m_size < other.m_size)
    {
        size_t i;
        for (i = 0; i < this->m_size; i++)
        {
            (*this)[i] = other[i];
        }
        for (size_t j = i; j < other.m_size; j++)
        {
            this->push_back(other[j]);
        }
    }
    else
    {
        size_t i;
        size_t this_size = this->m_size;
        for (i = 0; i < other.m_size; i++)
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

INL_TEMPL
List<T>::value_type List<T>::operator[](size_t index) const
{
    assert(index < m_size);

    Node<T> *current = Head;
    for (size_t i = 0; i < index; i++)
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
    for (size_t i = 0; i < index; i++)
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
    Node<T> *n = new Node<T>(value, nullptr);
    if (Head == nullptr)
    {
        Head = n;
    }
    else
    {
        Node<T> *c = Head;
        while (c->next != nullptr)
        {
            c = c->next;
        }
        c->next = n;
    }
    m_size++;
};

INL_TEMPL
void List<T>::push_befor(size_t pos, value_type value)
{
    assert(pos < m_size);
    Node<T> *n = new Node<T>(value, nullptr);
    if (pos == 0)
    {
        n->next = Head;
        Head    = n;
    }
    else
    {
        Node<T> *c = Head;
        for (size_t i = 0; i < pos - 1; i++)
        {
            c = c->next;
        }
        Node<T> *tmp = c->next;
        c->next      = n;
        n->next      = tmp;
    }
    m_size++;
}

INL_TEMPL
void List<T>::push_after(size_t pos, value_type value)
{
    assert(pos < m_size);
    Node<T> *n = new Node<T>(value, nullptr);
    if (pos == 0)
    {
        n->next = Head;
        Head    = n;
    }
    else
    {
        Node<T> *c = Head;
        for (size_t i = 0; i < pos; i++)
        {
            c = c->next;
        }
        Node<T> *tmp = c->next;
        c->next      = n;
        n->next      = tmp;
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
        Node<T> *c = Head;
        for (size_t i = 0; i < m_size - 2; i++)
        {
            c = c->next;
        }
        delete c->next;
        c->next = nullptr;
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
        Node<T> *c = Head;
        for (size_t i = 0; i < pos - 1; i++)
        {
            c = c->next;
        }
        Node<T> *tmp = c->next;
        c->next      = c->next->next;
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
    Node<T> *c = Head;
    size_t i   = 0;
    while (c != nullptr)
    {
        oss << "[" << i << "] = " << c->data;
        if (i < m_size - 1)
        {
            oss << ", ";
        }
        c = c->next;
        i++;
    }
    oss << " }";
    return oss.str();
}

INL_TEMPL
std::optional<size_t> List<T>::find(const value_type &val) const
{
    for (size_t i = 0; i < m_size; i++)
    {
        if ((*this)[i] == val)
        {
            return i;
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
    if (this->empty())
        throw "Linked List is empty";
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
    if (this->empty())
        throw "Linked List is empty";
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