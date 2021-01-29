#ifndef ALTERNATIVE_IMPL_H
#define ALTERNATIVE_IMPL_H

#include "Applicative_impl.h"

/// Add alternative implementations here

template <>
struct Alternative<std::optional> : Applicative<std::optional> {
  // empty :: f a
  template <typename T>
  static auto empty() -> std::optional<T>
  {
    return std::nullopt;
  }

  // (<|>) :: f a -> f a -> f a
  template <typename T>
  static auto or_op(std::optional<T> a, std::optional<T> b) -> std::optional<T>
  {
    if (a)
      return a;
    return b;
  }
};

template <>
struct Alternative2<std::vector> : Applicative2<std::vector> {
  template <typename T>
  static auto empty() -> std::vector<T>
  {
    return {};
  }

  template <typename T>
  static auto or_op(std::vector<T> a, std::vector<T> const& b) -> std::vector<T>
  {
    for (auto const& i : b)
      a.push_back(i);
    return a;
  }
};

#endif // ALTERNATIVE_IMPL_H
