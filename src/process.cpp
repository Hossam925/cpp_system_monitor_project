#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<int> cpuNumbers = LinuxParser::CpuUtilization(pid_);
    utime_     = cpuNumbers[13];
    stime_     = cpuNumbers[14];
    cutime_    = cpuNumbers[15];
    cstime_    = cpuNumbers[16];
    starttime_ = cpuNumbers[21];
    Hertz_     = sysconf(_SC_CLK_TCK);
    long uptime = UpTime();
    double total_time = utime_ + stime_ + cutime_ + cstime_;

    double seconds = uptime - (starttime_ / Hertz_);
    double cpu_usage = (total_time / Hertz_) / seconds;
    return cpu_usage; 
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_);}

// TODO: Return this process's memory utilization
string Process::Ram() { 
    string sram = LinuxParser::Ram(pid_);
    ram_ = std::stoi(sram);  
    return sram; 
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process & a)  { return (ram_>a.ram_); }