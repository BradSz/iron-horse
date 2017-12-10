#pragma once

#include <iron/core.h>

namespace iron {

template <typename T>
struct boxed_magic {
    boxed_magic(const T& inT)
      : mux(), tux(new T(inT)) { }

  protected:
    boost::shared_ptr<iron::Mutex> mux;
    boost::shared_ptr<T>           tux;

    std::shared_ptr<T> clone() const {
      return std::shared_ptr<T>(new T(*tux));
    }
};

template <typename T>
struct mut : protected std::shared_ptr<T> {
    mut(boxed_magic<T>& inMagic)
      : std::shared_ptr<T>(inMagic.mux.second),
        mPadlock(inMagic.mux.first) { }

    std::shared_ptr<T> clone() const {
      return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<T>::get;
    using std::shared_ptr<T>::operator*;
    using std::shared_ptr<T>::operator->;

    iron::WriteLock mPadlock;
};

template <typename T>
struct box : private std::shared_ptr<T> {
    box(boxed_magic<T>& inMagic)
      : std::shared_ptr<const T>(inMagic.mux.second),
        mPadlock(inMagic.mux.first) { }

    std::shared_ptr<T> clone() const {
          return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<T>::get;
    using std::shared_ptr<T>::operator*;
    using std::shared_ptr<T>::operator->;

    iron::ReadLock mPadlock;
};

} /* iron */
