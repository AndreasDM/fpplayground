#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <any>
#include <functional>

template <template <typename...> class T>
concept IsFunctor = requires (T<std::any> t, std::function<std::any(std::any)> f)
{
  fmap(f, t);
};


template <template <typename...> class T>
concept HasAp =
  requires ( T<std::any> t
           , T<std::function<std::any(std::any)>> u
           )
{
  u * t;
};

template <template <typename...> class T>
concept HasLiftA2 =
  requires ( std::function<std::any(std::any, std::any)> g
           , T<std::any> t
           )
{
  liftA2(g, t, t);
};

template <template <typename...> class T>
concept IsApplicative =
  requires (std::any x)
{
  pure<T>(x);
  requires IsFunctor<T> && HasAp<T> && HasLiftA2<T>;
};

template <template <typename...> class T>
concept IsMonad =
  requires ( std::function<T<std::any>(std::any)> f
           , T<std::any> x
           , std::any a
           )
{
  requires IsApplicative<T>;
  x >>= f;
  x >> x;
};

#endif // CONCEPTS_H
