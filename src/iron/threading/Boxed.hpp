#pragma once

#include <iron/core.h>

namespace iron {

template <typename T>
struct View : private std::shared_ptr<const T> {
    View(const std::shared_ptr<T>& inData,
         const std::shared_ptr<iron::Mutex>& inMutex)
      : std::shared_ptr<const T>(inData),
        mMutex(inMutex),
        mReadLock(*inMutex) { }

    std::shared_ptr<const T> clone() const {
          return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<const T>::get;
    using std::shared_ptr<const T>::operator *;
    using std::shared_ptr<const T>::operator ->;
    using std::shared_ptr<const T>::operator bool;
    using std::shared_ptr<const T>::use_count;

    void release() {
      std::shared_ptr<const T>::reset();
      mReadLock.unlock();
    }

  protected:
    std::shared_ptr<iron::Mutex> mMutex;
    iron::ReadLock               mReadLock;
};

template <typename T>
struct Mut : private std::shared_ptr<T> {
    Mut(const std::shared_ptr<T>& inData,
        const std::shared_ptr<iron::Mutex>& inMutex)
      : std::shared_ptr<T>(inData),
        mMutex(inMutex),
        mWriteLock(*inMutex) { }

    std::shared_ptr<const T> clone() const {
          return std::shared_ptr<T>(new T(**this));
    }

    using std::shared_ptr<T>::get;
    using std::shared_ptr<T>::operator *;
    using std::shared_ptr<T>::operator ->;
    using std::shared_ptr<T>::operator bool;
    using std::shared_ptr<T>::use_count;

    void release() {
      std::shared_ptr<T>::reset();
      mWriteLock.unlock();
    }

  protected:
    std::shared_ptr<iron::Mutex> mMutex;
    iron::WriteLock              mWriteLock;
};

template <typename T>
struct Box {
    typedef Box <T>  this_type;
    typedef View<T>  view_type;
    typedef Mut <T>   mut_type;

    Box()          : mData(),       mMutex()                  { }

    Box(T* inData) : mData(inData), mMutex(new iron::Mutex()) { }

    ~Box() {
      mMutex.reset();
      mData.reset();
    }

    void reset() {
      mData.reset();
      mMutex.reset();
    }

    void reset(T* t) {
      mData.reset(t);
      mMutex.reset(new iron::Mutex());
    }

    template<typename X>
    static Box<X> fromCopy(const T& inData) {
      return Box<X>(std::shared_ptr<X>(new X(inData)));
    }

    view_type view() const { return view_type(mData, mMutex); }

    mut_type  mut() const { return  mut_type(mData, mMutex); }

    std::shared_ptr<T> clone() const {
      return std::shared_ptr<T>(new T(*mData));
    }

  protected:
    std::shared_ptr<T>           mData;
    std::shared_ptr<iron::Mutex> mMutex;
};

} /* iron */
