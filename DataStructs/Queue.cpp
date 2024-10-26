#include <iostream>
#include <string>

#include "include/Config.hpp"
#include "include/Queue.hpp"

#define Queue_Init(t) template class sof::Queue<t>;
using namespace sof;

template <typename T>
inline Queue<T>::Queue()
    : Capacity(32), buffer(new T[Capacity * sizeof(value_type)]), Head(&buffer[0]), Tail(Head - 1)
{
}

template <typename T>
inline Queue<T>::Queue(size_type size, value_type init) : Capacity(128)
{
    if (size == 0)
    {
        throw "size should be > 0";
    }

    while (Capacity < size)
    {
        Capacity += Capacity / 2;
    }

    buffer = new T[Capacity * sizeof(value_type)];
    Head   = &buffer[0];
    Tail   = &buffer[size - 1];

    for (size_type i = 0; i < size; i++)
    {
        buffer[i] = init;
    }
}

template <typename T>
inline Queue<T>::~Queue()
{
    if (buffer != nullptr)
        delete[] buffer;
}

template <typename T>
inline Queue<T>::size_type Queue<T>::size() const noexcept
{
    return Head == Tail ? 0 : Tail - Head + 1;
}

template <typename T>
inline bool Queue<T>::empty() const noexcept
{
    return size() == 0;
}

template <typename T>
void Queue<T>::push(const value_type& value)
{
    auto size = this->size();

    if (Capacity < size)
    {
        Capacity += Capacity / 2;
        pointer tmp = buffer;
        buffer      = new T[Capacity * sizeof(value_type)];
        memcpy(buffer, tmp, size - 1);
        Head = &buffer[0];
        Tail = size - 1 < 0 ? Head - 1 : &buffer[size - 1];

        if (buffer != tmp)
        {
            delete[] tmp;
        }
    }

    Tail++;
    *Tail = value;
}

template <typename T>
Queue<T>::value_type Queue<T>::operator[](size_type index) const
{
    return buffer[index];
}

template <typename T>
std::string Queue<T>::str() const {
    std::string os;
    auto size = this->size();
    os += "{ ";
    for(size_type i = 0; i < size; i++){
        os+= "[";
        os+= std::to_string(i);
        os+= "]";
        os+= " = ";
        os+= std::to_string(buffer[i]);
        if( i != size - 1) {
            os+= ", ";
        }
    }
    os += " }";
    return os;
}
Queue_Init(int)