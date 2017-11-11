#pragma once

#include <iron/core.h>

template <typename T>
class TQueue {
public:
  TQueue(uint64_t maxSize=std::numeric_limits<uint64_t>::max())
    : MaxSize(maxSize), mPushedNotifier(), mPoppedNotifier(), mMutex(), mQueue() {}

  virtual ~TQueue() {}


  bool push_back(const T& t, uint64_t timeout=std::numeric_limits<uint64_t>::max()) {
    std::unique_lock<std::mutex> padlock(mMutex);

    if (mPoppedNotifier.wait_for(padlock, std::chrono::milliseconds(timeout), [this] { return mQueue.size() < MaxSize; })) {
      mQueue.push_back(t);

      padlock.unlock();
      mPushedNotifier.notify_one();
      return true;
    }
    else { return false; }
  }

  bool pop_front (T& t, uint64_t timeout=std::numeric_limits<uint64_t>::max()) {
    std::unique_lock<std::mutex> padlock(mMutex);

    if (mPushedNotifier.wait_for(padlock, std::chrono::milliseconds(timeout), [this] { return !mQueue.empty(); })) {
      t = mQueue.front();
      mQueue.pop_front();

      padlock.unlock();
      mPoppedNotifier.notify_one();
      return true;
    }
    else { return false; }
  }

  bool empty() { return mQueue.empty(); }
  bool size()  { return mQueue.size();  }

  uint64_t MaxSize;

private:
  std::condition_variable mPushedNotifier;
  std::condition_variable mPoppedNotifier;
  std::mutex              mMutex;
  std::deque<T>           mQueue;
};
