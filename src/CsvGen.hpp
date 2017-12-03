#pragma once

#include <chrono>
#include <iomanip>
#include <map>
#include <queue>
#include <sstream>

struct Keeper
{
  static Keeper* instance() {
    static Keeper ret;
    return &ret;
  }

  void process() {
    while(!mQueue.empty()) {
      std::pair<std::string,std::string> pair = mQueue.front();
      mLatestDetails[pair.first] = pair.second;
      mQueue.pop();
    }

    char delim = ',';
    std::stringstream ss;
    std::map<std::string,std::string>::const_iterator mapItr;

    if (mLatestDetails.size() != mLastWidth)
    {
      ss << std::endl;
      for(mapItr = mLatestDetails.begin(); mapItr != mLatestDetails.end(); ++mapItr) {
        ss << mapItr->first << delim;
      }
      ss << std::endl;

      mLastWidth = mLatestDetails.size();
    }

    for(mapItr = mLatestDetails.begin(); mapItr != mLatestDetails.end(); ++mapItr) {
      ss << mapItr->second << delim;
    }

    std::cout << ss.str() << std::endl;
  }

  void keep(const std::string& inKey, const std::string& inVal) {
    mQueue.push(std::make_pair(inKey,inVal));
  }

  template <typename T>
  void keep(const std::string& inKey, const T& inVal) {
    std::stringstream ss;
    ss << std::setprecision(8) << inVal;
    mQueue.push(std::make_pair(inKey,ss.str()));
  }

protected:
  Keeper()
    : mQueue(),
      mLatestDetails(),
      mLastWidth(0)
  { }

  std::queue<std::pair<std::string,std::string> > mQueue;

  std::map<std::string,std::string> mLatestDetails;
  int mLastWidth;
};

struct FlashTimer {
  FlashTimer(const std::string& inName)
    : mName(inName), mStartTime(getTime()) { }

  ~FlashTimer() {
    Keeper::instance()->keep(mName, getTime()-mStartTime);
    Keeper::instance()->process();
  }

protected:
  inline static int64_t getTime() {
    std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  }

  std::string mName;
  std::clock_t mStartTime;
};

#define KEEP_DATA(KDKEY, KDVAL) { \
  Keeper::instance()->keep(KDKEY, KDVAL); \
  Keeper::instance()->process(); \
}

#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)

#define FLASH_TIMER(FTNAME) FlashTimer COMBINE(Flash_Timer,__LINE__)(FTNAME);
