#pragma once

#define __TEMPL           \
    template <typename T> \
    requires(!std::is_pointer_v<T> || !std::is_reference_v<T>)
#define INL_TEMPL __TEMPL inline
