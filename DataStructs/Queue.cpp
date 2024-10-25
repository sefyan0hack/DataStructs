#include "include/Config.hpp"
#include "include/Queue.hpp"

#define Queue_Init(t) template class sof::Queue<t>;
using namespace sof;

template <typename T>
inline Queue<T>::Queue()
    : Capacity(32),
      m_size(0),
      buffer(new T[Capacity * sizeof(value_type)]),
      Head(&buffer[0]),
      Tail(Head)
{
}

template <typename T>
inline Queue<T>::Queue(size_type size, const value_type& init) : Capacity(128), m_size(size)
{
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