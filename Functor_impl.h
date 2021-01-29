#ifndef FUNCTOR_IMPL_H
#define FUNCTOR_IMPL_H

#include "Defs.h"
#include <type_traits>

/// Add Functor Implementations here

#include <optional>
template <>
struct Functor<std::optional> {
  // fmap :: (a -> b) -> f a -> f b
  template <typename F, typename A>
  static auto fmap(F&& f, std::optional<A> a) -> std::optional<std::result_of_t<F(A)>>
  {
    if (a)
      return f(a.value());
    return {};
  }
};

#include <vector>
template <>
struct Functor2<std::vector> {
  template <typename F, typename A>
  static auto fmap(F&& f, std::vector<A> v) -> std::vector<std::result_of_t<F(A)>>
  {
    std::vector<std::result_of_t<F(A)>> res;
    res.reserve(v.size());
    for (auto const& i : v)
      res.emplace_back(f(i));
    return res;
  }
};

#endif // FUNCTOR_IMPL_H
