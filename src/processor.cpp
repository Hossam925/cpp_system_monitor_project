#include "processor.h"
#include <iostream>
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {

    usertime_      = cpu_times[kUser_]   - cpu_times[kGuest_];
    nicetime_      = cpu_times[kNice_]   - cpu_times[kGuestNice_];
    idealtime_     = (cpu_times[kIdle_]  + cpu_times[kIOwait_]);
    systemalltime_ = cpu_times[kSystem_] + cpu_times[kIRQ_]+cpu_times[kSoftIRQ_];
    virtualtime_   = cpu_times[kGuest_]  + cpu_times[kGuestNice_];
    totaltime_ = (usertime_+nicetime_+idealtime_+systemalltime_+virtualtime_);
    float precent = (totaltime_-idealtime_)/totaltime_;

    return precent; 
}