#pragma once

#include <iron/core.h>

template <typename T>
class TQueue {
  typedef boost::shared_mutex Mutex;
  typedef boost::shared_lock<Mutex> ReadLock;
  typedef boost::unique_lock<Mutex> WriteLock;
public:
  TQueue(uint64_t maxSize=std::numeric_limits<uint64_t>::max())
    : MaxSize(maxSize), mQueue(), mMutex(), mPushedNotifier(), mPoppedNotifier() {}

  virtual ~TQueue() {}

  bool push_back(const T& t, uint64_t inTimeoutMs=std::numeric_limits<uint64_t>::max()) {
    WriteLock padlock(mMutex);

    auto timeout       = boost::chrono::milliseconds(inTimeoutMs);
    auto checkHasSpace = [this] { return mQueue.size() < MaxSize; };

    if (mPoppedNotifier.wait_for(padlock, timeout, checkHasSpace)) {
      mQueue.push_back(t);

      padlock.unlock();
      mPushedNotifier.notify_one();
      return true;
    }
    else { return false; }
  }

  bool pop_front (T& t, uint64_t inTimeoutMs=std::numeric_limits<uint64_t>::max()) {
    WriteLock padlock(mMutex);

    auto timeout      = boost::chrono::milliseconds(inTimeoutMs);
    auto checkHasItem = [this] { return !mQueue.empty(); };

    if (mPushedNotifier.wait_for(padlock, timeout, checkHasItem)) {
      t = mQueue.front();
      mQueue.pop_front();

      padlock.unlock();
      mPoppedNotifier.notify_one();
      return true;
    }
    else { return false; }
  }

  bool empty() const { ReadLock padlock(mMutex); return mQueue.empty(); }
  bool size()  const { ReadLock padlock(mMutex); return mQueue.size();  }

  uint64_t MaxSize;

private:
  std::deque<T>                 mQueue;
  mutable Mutex                 mMutex;
  boost::condition_variable_any mPushedNotifier;
  boost::condition_variable_any mPoppedNotifier;
};
