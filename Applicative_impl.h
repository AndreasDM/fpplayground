#ifndef APPLICATIVE_IMPL_H
#define APPLICATIVE_IMPL_H

#include "Defs.h"
#include "Functor_impl.h"

/// Add Applicative implementations here

template <>
struct Applicative<std::optional> : Functor<std::optional> {
  // pure :: a -> f a
  template <typename T>
  static auto pure(T a) -> std::optional<T>
  { return a; }

  // <*> :: f (a -> b) -> f a -> f b
  template <typename T, typename F>
  static auto ap(std::optional<F> f, std::optional<T> a) -> std::optional<std::result_of_t<F(T)>>
  {
    if (f)
      return fmap(f.value(), a);
    return {};
  }

  // liftA2 :: (a -> b -> c) -> f a -> f b -> f c
  template <typename T, typename U, typename F>
  static auto liftA2(F&& f, std::optional<T> a, std::optional<U> b) -> std::optional<std::result_of_t<F(T,U)>>
  {
    if (a && b)
      return f(a.value(), b.value());
    return {};
  }
};

template <>
struct Applicative2<std::vector> : Functor2<std::vector> {
  template <typename T>
  static auto pure(T t) -> std::vector<T>
  {
    return {std::move(t)};
  }

  template <typename T, typename F>
  static auto ap(std::vector<F> const& fs, std::vector<T> const& a) -> std::vector<std::result_of_t<F(T)>>
  {
    std::vector<std::result_of_t<F(T)>> res;
    for (auto const& f : fs)
      for (auto const& i : a)
        res.emplace_back(f(i));
    return res;
  }

  template <typename T, typename U, typename F>
  static auto liftA2(F&& f, std::vector<T> a, std::vector<U> b) -> std::vector<std::result_of_t<F(T,U)>>
  {
    std::vector<std::result_of_t<F(T,U)>> res;
    for ([[maybe_unused]]auto const& i : a)
      for ([[maybe_unused]]auto const& j : b)
        res.emplace_back(f(a, b));
    return res;
  }
};

#endif // APPLICATIVE_IMPL_H
