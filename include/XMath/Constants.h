#pragma once
#include <type_traits>

template<typename Real> constexpr Real defaultEps() {
    if constexpr (std::is_same_v<float, Real>)
        return 0.0001f;
    else
        return 0.0000001;
}