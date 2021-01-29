#ifndef FP_H
#define FP_H

#include "Defs.h"
#include "Functor_impl.h"
#include "Applicative_impl.h"
#include "Alternative_impl.h"
#include "Monad_impl.h"

#include <functional>

/// Add Generic functions and operators here
/// to forward to the appropriate implementation

// fmap :: (a -> b) -> f a -> f b
template <template <typename> class T, typename U, typename F>
auto fmap(F&& f, T<U> a)
{
  return Functor<T>::fmap(std::forward<F>(f), std::move(a));
}

template <template <typename,typename> class T, typename U, typename V, typename F>
auto fmap(F&& f, T<U,V> a)
{
  return Functor2<T>::fmap(std::forward<F>(f), std::move(a));
}

template <template <typename> class T, typename U, typename F>
auto operator % (F&& f, T<U> a)
{
  return Functor<T>::fmap(std::forward<F>(f), std::move(a));
}

template <template <typename,typename> class T, typename U, typename V, typename F>
auto operator % (F&& f, T<U,V> a)
{
  return Functor2<T>::fmap(std::forward<F>(f), std::move(a));
}

//////////////////////////////////////////////////////////////////

// <*> :: f (a -> b) -> f a -> f b
template <template <typename> class T, typename F, typename U>
auto operator * (T<F> f, T<U> a)
{
  return Applicative<T>::ap(std::move(f), std::move(a));
}

template <template <typename,typename> class T, typename F, typename U, typename V>
auto operator * (T<F,V> f, T<U,V> a)
{
  return Applicative2<T>::ap(std::move(f), std::move(a));
}

// liftA2 :: (a -> b -> c) -> f a -> f b -> f c
template <template <typename> class T, typename F, typename A, typename B>
auto liftA2(F&& f, T<A> a, T<B> b)
{
  return Applicative<T>::liftA2(std::forward<F>(f), std::move(a), std::move(b));
}

template <template <typename,typename> class T, typename F, typename A, typename B, typename V>
auto liftA2(F&& f, T<A,V> a, T<B,V> b)
{
  return Applicative2<T>::liftA2(std::forward<F>(f), std::move(a), std::move(b));
}

// pure :: a -> f a
template <template <typename> class T, typename X>
auto pure(X&& x)
{
  return Applicative<T>::pure(std::forward<X>(x));
}

template <template <typename,typename> class T, typename X>
auto pure(X&& x)
{
  return Applicative2<T>::pure(std::forward<X>(x));
}

//////////////////////////////////////////////////////////////////

// (<|>) :: f a -> f a -> f a
template <template <typename> class T, typename U>
auto operator | (T<U> a, T<U> b)
{
  return Alternative<T>::or_op(std::move(a), std::move(b));
}

template <template <typename,typename> class T, typename U, typename V>
auto operator | (T<U,V> a, T<U,V> b)
{
  return Alternative2<T>::or_op(std::move(a), std::move(b));
}

// empty :: f a
template <template <typename> class T, typename U>
auto empty()
{
  return Alternative<T>::template empty<U>();
}

template <template <typename,typename> class T, typename U>
auto empty()
{
  return Alternative2<T>::template empty<U>();
}

//////////////////////////////////////////////////////////////////

// (>>=) :: m a -> (a -> m b) -> m b
template <template <typename> class T, typename U, typename F>
auto operator >>= (T<U> ma, F&& f)
{
  return Monad<T>::bind(std::move(ma), std::forward<F>(f));
}

template <template <typename,typename> class T, typename U, typename V, typename F>
auto operator >>= (T<U,V> ma, F&& f)
{
  return Monad2<T>::bind(std::move(ma), std::forward<F>(f));
}

// (>>) :: m a -> m b -> m b
template <template <typename> class T, typename U, typename V>
auto operator >> (T<U> ma, T<V> mb)
{
  return Monad<T>::comp(std::move(ma), std::move(mb));
}

template <template <typename,typename> class T, typename U, typename V, typename A>
auto operator >> (T<U, A> ma, T<V, A> mb)
{
  return Monad2<T>::comp(std::move(ma), std::move(mb));
}

// join :: m (m a) -> m a
template <template <typename> class T, typename U>
auto join(T<T<U>> mma)
{
  return Monad<T>::join(std::move(mma));
}

template <template <typename,typename> class T, typename U, typename V>
auto join(T<T<U,V>,V> mma)
{
  return Monad2<T>::join(std::move(mma));
}

//////////////////////////////////////////////////////////////////

template <typename R, typename Arg, typename... Args>
auto curry(std::function<R(Arg, Args...)> f)
{
  if constexpr (sizeof...(Args) == 0)
    return f;
  else
    return [=](auto... xs) {
      return curry(std::function<R(Args...)>{ std::bind_front(f, xs...) } );
    };
}

template <typename F, typename G>
auto operator <=> (F&& f, G&& g)
{
  return [f = std::forward<F>(f), g = std::forward<G>(g)](auto x) {
    return f(g(x));
  };
}

#define · <=>

#endif // FP_H
