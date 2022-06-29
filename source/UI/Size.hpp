//! @date 5/10/21
//! @author David Spry

#pragma once

#include "Point.hpp"

namespace ds::ui {

//! @struct A two-component vector representing a size, (w, h).

template <typename T>
using Size = Point<T>;

}