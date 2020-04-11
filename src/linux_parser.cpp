#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel,version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line,key,value;
  vector<float> mem{0,0};
  float MemoryUtilization;
  std::ifstream myfile(kProcDirectory+kMeminfoFilename);
  if(myfile.is_open()){
    for(int i=0;i<2;i++){
      std::getline(myfile,line);
      std::istringstream myline(line);
      myline>>key>>value;
      mem[i] = std::stoi(value);
    }
    MemoryUtilization = (mem[0]-mem[1])/mem[0];
  }
  return MemoryUtilization; 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  float uptime=0;
  std::ifstream myfile(kProcDirectory+kUptimeFilename);
  if(myfile.is_open()){
    std::getline(myfile,line);
    std::istringstream linestream(line);
    linestream>>uptime;
  }
  //std::cout<<uptime<<std::endl;
  return uptime; 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<int> LinuxParser::CpuUtilization() {
  string line,temp;
  int value;
  vector<int> cpu_values; 
  std::ifstream myfile(kProcDirectory+kStatFilename);
  if(myfile.is_open()){
    std::getline(myfile,line);
    std::istringstream lineStream(line);
    lineStream>>temp;
    while(lineStream>>value){cpu_values.push_back(value);}
  }
  
  return cpu_values; 
}


vector<int> LinuxParser::CpuUtilization(int pid) {
  string line,temp;
  int value;
  string pid_path = to_string(pid);
  vector<int> cpu_values; 
  std::ifstream myfile(kProcDirectory+pid_path+kStatFilename);
  if(myfile.is_open()){
    std::getline(myfile,line);
    std::istringstream lineStream(line);
    while(lineStream>>value){cpu_values.push_back(value);}
  }
  
  return cpu_values; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line,key;
  int value;
  std::ifstream myfile(kProcDirectory+kStatFilename);
  if(myfile.is_open()){
    while(std::getline(myfile,line)){
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      if(key == "processes")
        return value;
    }
  }
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line,key;
  int value;
  std::ifstream myfile(kProcDirectory+kStatFilename);
  if(myfile.is_open()){
    while(std::getline(myfile,line)){
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      if(key == "procs_running")
        return value;
    }
  }
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string pid_path = to_string(pid);
  string line;
  std::ifstream myfile(kProcDirectory+pid_path+kCmdlineFilename);
  if(myfile.is_open()){
    std::getline(myfile,line);
  }
  return line; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string pid_path = to_string(pid);
  string line,key;
  int value;
  std::ifstream myfile(kProcDirectory+pid_path+kStatusFilename);
  if(myfile.is_open()){
    while(std::getline(myfile,line)){
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      if(key == "VmSize:"){
        value /= 1024;
        return to_string(value);
      } 
    }
  }
  return to_string(value); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string pid_path = to_string(pid);
  string line,key,value;
  std::ifstream myfile(kProcDirectory+pid_path+kStatusFilename);
  if(myfile.is_open()){
    while(std::getline(myfile,line)){
      std::istringstream lineStream(line);
      lineStream >> key >> value;
      if(key == "Uid:"){
        return value;
      }
    }
  }
  return value; 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string line,key,user;
  int value;
  std::ifstream myfile(kPasswordPath);
  if(myfile.is_open()){
    while(std::getline(myfile,line)){
      std::replace(line.begin(),line.end(),':',' ');
      std::istringstream lineStream(line);
      lineStream >> user >> key >> value;
      if(value == pid){
        return user;
      }
    }
  }
  return user; 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string pid_path = to_string(pid);
  string line,key,clock_ticks;
  long time;
  std::ifstream myfile(kProcDirectory+pid_path+kStatFilename);
  if(myfile.is_open()){
    std::getline(myfile,line);
      std::istringstream lineStream(line);
      for(int i=0;i<22;i++){
        lineStream >> clock_ticks;
      }
    time = std::stol(clock_ticks)/sysconf(_SC_CLK_TCK);
  }
  return time; 
}