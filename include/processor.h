#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <vector>
#include <cstdlib>
// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  // TODO: Declare any necessary private members
 private:
    float usertime_ ;
    float nicetime_ ;
    float idealtime_ = 0;
    float systemalltime_;
    float virtualtime_;
    float totaltime_ = 0;
    std::vector<int> cpu_times;
    friend class System;
};

#endif