#include <optional>
#include <vector>
#include <sstream>
#include "include/Stack.hpp"

#define __TEMPL           \
    template <typename T> \
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>)
#define INL_TEMPL __TEMPL inline

#define Stack_Init(t) template class sof::Stack<t>

using namespace sof;

INL_TEMPL
Stack<T>::Stack() : m_max_size(static_cast<size_type>(-1)) {}

INL_TEMPL
Stack<T>::Stack(size_type max_size) : m_max_size(max_size) {}

INL_TEMPL
Stack<T> Stack<T>::operator=(const Stack &other)
{
    return Stack(other);
}

INL_TEMPL
Stack<T>::Stack(const Stack &other)
{
    if (other.m_container.empty())
    {
        Stack(other.m_max_size);
    }
    else
    {
        this->m_max_size = other.m_max_size;
        std::copy(other.m_container.begin(), other.m_container.end(), this->m_container.begin());
    }
}

INL_TEMPL
void Stack<T>::push(const value_type &val)
{
    if (m_max_size == m_container.size())
        throw std::exception("Stack OverFlow");
    m_container.emplace_back(val);
}

INL_TEMPL
Stack<T>::value_type Stack<T>::pop()
{
    auto& cont = this->m_container;

    value_type x = cont.back();
    cont.pop_back();
    return x;
}

INL_TEMPL
Stack<T>::const_reference Stack<T>::peek() const
{
    return this->m_container.back();
}

INL_TEMPL
Stack<T>::size_type Stack<T>::size() const
{
    return this->m_container.size();
}

INL_TEMPL
Stack<T>::size_type Stack<T>::max_size() const
{
    return this->m_max_size;
}

INL_TEMPL
std::string Stack<T>::str() const
{
    std::stringstream stream;
    stream << "{ ";
    for (const auto &item : m_container)
    {
        stream << item;
        if (&item != &m_container.back())
            stream << ", ";
    }
    stream << " }";
    return stream.str();
}
Stack_Init(int);