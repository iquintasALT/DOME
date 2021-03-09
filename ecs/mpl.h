// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstddef>
#include <type_traits>

namespace mpl {

// Compile-time list of types.
template<typename ... Ts>
struct TypeList {
	// Size of the list.
	static constexpr std::size_t size { sizeof...(Ts) };
};

template<typename, typename >
struct IndexOf;

// IndexOf base case: found the type we're looking for.
template<typename T, typename ... Ts>
struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
};

// IndexOf recursive case: 1 + IndexOf the rest of the types.
template<typename T, typename TOther, typename ... Ts>
struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant<std::size_t,
		1 + IndexOf<T, TypeList<Ts...>> { }> {
};
}
