#pragma once

#include <type_traits>

template<class Derived, class Base>
concept Implements = std::is_base_of_v<Base, Derived>;
