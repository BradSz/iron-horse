#include <list>
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <thread>
#include <unistd.h>

#include <iron/core.h>

#include "CsvGen.hpp"
#include <iron/core/TQueue.hpp>

struct rez {
  rez (int64_t inX=0, int64_t inY=0) : X(inX), Y(inY) {}

  int64_t X, Y;
};

struct ringer
{
  ringer(int64_t inMin, int64_t inMax) : Min(inMin), Max(inMax) {
    if (inMax <= inMin) {
      std::cout << "throw here maybe" << std::endl;
    }
  }
  virtual ~ringer() {}

  inline int64_t bandwidth() const { return Max - Min; }

  std::list<rez> compute(int64_t inStart, int64_t inEnd) const
  {
    std::list<rez> ret;

    rez res(inStart, inEnd);

    while (res.X < Min)   res.X += bandwidth(); // Increase X to correct min val
    while (res.Y < res.X) res.Y += bandwidth(); // Increase Y to correct min val

    res.X = ((res.X-Min)   % bandwidth()) + Min;
    res.Y = ((res.Y-Min)   % bandwidth()) + Min;

    if (res.Y < res.X) {
      ret.push_back(rez(res.X, Max));
      ret.push_back(rez(Min, res.Y));
    } else {
      ret.push_back(res);
    }

    return ret;
  }

  int64_t Min, Max;
};

void csver()
{
  FLASH_TIMER("FromStart");
  KEEP_DATA("2-Taco", 12);
  KEEP_DATA("2-Taco", 11);
  KEEP_DATA("2-Taco", 13);
  KEEP_DATA("3-Truck", "Wheels");
  KEEP_DATA("2-Taco", "Tires");
  KEEP_DATA("3-Truck", "Fortune");
  KEEP_DATA("1-Axe", "Flash");
  KEEP_DATA("3-Truck", "Trailer");

  FLASH_TIMER("BeforeSleep");

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void queuer()
{
  TQueue<std::string> tq(2);

  std::vector<std::string> popped(10);
  std::cout <<"True:  " << tq.push_back("ASDF")         << std::endl;
  std::cout <<"True:  " << tq.push_back("JKL;", 10)     << std::endl;
  std::cout <<"False: " << tq.push_back("QWER", 10)     << std::endl;
  std::cout <<"True:  " << tq.pop_front(popped[0])      << std::endl;
  std::cout <<"True:  " << tq.pop_front(popped[1])      << std::endl;
  std::cout <<"False: " << tq.pop_front(popped[2], 10)  << std::endl;

  for (auto x : popped) std::cout << x << std::endl;
}

int main(int argc, char** argv)
{
  // ringer r(-5, 20);
  //
  // std::list<rez>::const_iterator itr;
  // std::list<rez> vals = r.compute(15, 25);
  // for (itr = vals.begin(); itr != vals.end(); ++itr)
  // {
  //   std::cout << "X: " << itr->X << " Y:" << itr->Y << std::endl;
  // }
  //
  // csver();

  queuer();

  return 0;
}
