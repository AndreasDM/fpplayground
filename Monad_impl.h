#ifndef MONAD_IMPL_H
#define MONAD_IMPL_H

#include "Applicative_impl.h"

/// Add Monad implementations here

template <>
struct Monad<std::optional> : Applicative<std::optional> {
  // (>>=) :: m a -> (a -> m b) -> m b
  template <typename T, typename F>
  static auto bind(std::optional<T> ma, F&& f) -> std::result_of_t<F(T)>
  {
    return join(fmap(f, ma));
  }

  // join :: m (m a) -> m a
  template <typename T>
  static auto join(std::optional<std::optional<T>> a) -> std::optional<T>
  {
    if (a)
      return a.value();
    return {};
  }

  // (>>) :: m a -> m b -> m b
  template <typename T, typename U>
  static auto comp(std::optional<T> ma, std::optional<U> mb) -> std::optional<U>
  {
    return bind(std::move(ma), [mb = std::move(mb)](auto) { return mb; });
  }
};

template <typename T>
auto id(T a)
{
  return a;
}

template <>
struct Monad2<std::vector> : Applicative2<std::vector> {
  template <typename T, typename F>
  static auto bind(std::vector<T> const& ma, F&& f) -> std::result_of_t<F(T)>
  {
    return Monad2<std::vector>::join(fmap(f, ma));
  }

  template <typename T>
  static auto join(std::vector<std::vector<T>> const& a) -> std::vector<T>
  {
    std::vector<T> res;
    for (auto const& i : a)
      for (auto const& j : i)
        res.emplace_back(j);
    return res;
  }

  template <typename T, typename U>
  static auto comp(std::vector<T> const& ma, std::vector<U> const& mb)
  {
    std::vector<U> res;
    for ([[maybe_unused]]auto const& a : ma)
      for (auto const& b : mb)
        res.emplace_back(b);
    return res;
  }
};

#endif // MONAD_IMPL_H
