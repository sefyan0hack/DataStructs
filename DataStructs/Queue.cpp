#include <iostream>
#include <string>
#include <list>

#include "include/Config.hpp"
#include "include/Queue.hpp"

#define Queue_Init(t) template class sof::Queue<t, std::list<t>>;  // for now list is the container
using namespace sof;

template <typename T, typename Cont>
inline Queue<T, Cont>::Queue() : buffer(Cont())
{
}

template <typename T, typename Cont>
inline Queue<T, Cont>::Queue(size_type size, value_type init)
{
    if (size == 0)
    {
        throw "size should be > 0";
    }

    for (size_type index = 0; index < size; index++)
    {
        buffer.emplace_back(init);
    }
}

template <typename T, typename Cont>
inline Queue<T, Cont>::~Queue()
{
}

template <typename T, typename Cont>
inline Queue<T, Cont>::size_type Queue<T, Cont>::size() const noexcept
{
    return buffer.size();
}

template <typename T, typename Cont>
inline bool Queue<T, Cont>::empty() const noexcept
{
    return buffer.empty();
}

template <typename T, typename Cont>
void Queue<T, Cont>::push(const value_type& value)
{
    buffer.push_back(value);
}

template <typename T, typename Cont>
Queue<T, Cont>::value_type Queue<T, Cont>::operator[](size_type index) const
{
    auto it = buffer.begin();
    std::advance(it, index);
    return *it;
}

template <typename T, typename Cont>
std::string Queue<T, Cont>::str() const
{
    std::string os;
    size_type counter = 0;
    os += "{ ";
    for (const auto& elm : buffer)
    {
        os += "[";
        os += std::to_string(counter++);
        os += "]";
        os += " = ";
        os += std::to_string(elm);
        if (counter != this->size() - 1)
        {
            os += ", ";
        }
    }
    os += " }";
    return os;
}

template <typename T, typename Cont>
void Queue<T, Cont>::pop()
{
    if (not empty())
    {
        buffer.pop_front();
    }
}


template <typename T, typename Cont>
Queue<T, Cont>::Cont_it Queue<T, Cont>::Head()
{
    return buffer.begin();
}

template <typename T, typename Cont>
Queue<T, Cont>::Cont_it Queue<T, Cont>::Tail()
{
    return buffer.end();
}

Queue_Init(int)