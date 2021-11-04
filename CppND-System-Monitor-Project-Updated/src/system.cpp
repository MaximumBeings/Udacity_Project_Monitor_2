#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() {
  return cpu_;

}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
vector<Process> ptrVec{};

  vector<int> fileDirecs = LinuxParser::Pids();
  for (int i: fileDirecs)
    {

    Process procProc(i);
     //Process *procProc = new Process;

    // procProc.setUser();
    // procProc.setCommand();
    // procProc.CpuUtilization();
    // procProc.setRam();
    // procProc.setUpTime();

  std::string r = procProc.getRam();
  std::string c = procProc.getCommand();
  std::string u = procProc.getUser();

  if(!r.empty() & !c.empty() & !u.empty()){
   ptrVec.emplace_back(procProc);
  }



    }
    processes_ = ptrVec;


  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
    string kernel = LinuxParser::Kernel() ;
    return kernel;

}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() {

  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/meminfo"};
  string MemTotal, MemFree,checkTest, checkTest2;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    { std::istringstream linestream(line);
    linestream >> checkTest >> checkTest2 ;
    int res = checkTest.compare("MemTotal:");
    if (res == 0)
      {
      MemTotal = checkTest2;
      }

    int res2 = checkTest.compare("MemFree:");
    if (res2 == 0)
      {
      MemFree = checkTest2;
      }
    }
  }
  float v = std::stof(MemTotal);
  float v2 = std::stof(MemFree);
  float v3 = (v - v2)/v;
  return v3;



}

// TODO: Return the operating system name
std::string System::OperatingSystem() {
    string operatingSystem = LinuxParser::OperatingSystem();
    return operatingSystem;

}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() {
    int runningProcess = LinuxParser::RunningProcesses();
    return runningProcess;

}

// TODO: Return the total number of processes on the system
int System::TotalProcesses() {
    int totalProcess = LinuxParser::TotalProcesses();
    return totalProcess;

}

// TODO: Return the number of seconds since the system started running
long int System::UpTime()
{
    long timeUp = LinuxParser::UpTime();
    return timeUp;
}




