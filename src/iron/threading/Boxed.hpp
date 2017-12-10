#pragma once

#include <iron/core.h>

namespace iron {

template<typename T> class view;
template<typename T> class mut;

template <typename T>
struct box {
    typedef view<T> view_type;
    typedef mut<T>  mut_type;

    box(const T& inT)
      : mMutex(), mData(new T(inT)) { }

    view<T> view() { return view<T>(this); }

    mut_type mut() { return mut_type(this); }

    std::shared_ptr<T> clone() const {
      return std::shared_ptr<T>(new T(*mData));
    }

  protected:
    friend view_type;
    friend mut_type;

    mutable boost::shared_ptr<iron::Mutex> mMutex;
    boost::shared_ptr<T>                   mData;
};

template <typename T>
struct view : private std::shared_ptr<const T> {
    view(box<T>& inBox)
      : std::shared_ptr<const T>(*(inBox.mData)),
        mReadLock(*(inBox.mMutex)) { }

    std::shared_ptr<const T> clone() const {
          return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<const T>::get;
    using std::shared_ptr<const T>::operator*;
    using std::shared_ptr<const T>::operator->;

  private:
    iron::ReadLock mReadLock;
};

template <typename T>
struct mut : protected std::shared_ptr<T> {
    mut(box<T>& inMagic)
      : std::shared_ptr<T>(*(inBox.mData)),
        mWriteLock(*(inBox.mMutex)) { }

    std::shared_ptr<T> clone() const {
      return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<T>::get;
    using std::shared_ptr<T>::operator*;
    using std::shared_ptr<T>::operator->;

  private:
    iron::WriteLock mWriteLock;
};

} /* iron */
