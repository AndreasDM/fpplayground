#ifndef DEFS_H
#define DEFS_H

template <template <typename> class>
struct Functor;

template <template <typename> class>
struct Applicative;

template <template <typename> class>
struct Alternative;

template <template <typename> class>
struct Monad;

///////////////////////////////////////////

#include <memory>
template <template <typename E, typename = std::allocator<E>> class>
struct Functor2;

template <template <typename E, typename = std::allocator<E>> class>
struct Applicative2;

template <template <typename E, typename = std::allocator<E>> class>
struct Alternative2;

template <template <typename E, typename = std::allocator<E>> class>
struct Monad2;


#endif // DEFS_H
