#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"


#include <experimental/filesystem>
namespace fs = std::experimental::filesystem ;

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
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

//BONUS: Update this to use std::filesystem
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

// vector <int> LinuxParser::Pids() {
// vector <int> pids;
// const std::string kProcDirectory {"/proc/"};
// fs::path currentPath {kProcDirectory};
// std::vector < fs::directory_entry > dir_entries {};

// fs::directory_iterator begin {currentPath};
// fs::directory_iterator end {};
// while (begin != end) {
//   auto de = * begin++;
//   string filename(de.path().filename());
//   if (std::all_of(filename.begin(), filename.end(), isdigit)) {
//     int pid = stoi(filename);
//     pids.push_back(pid);
//   }
// }

// return pids;

// }

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
 

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

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string upTime;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open())
  {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime;
  }
  float v = std::stof(upTime);
  return v; 
  
  }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  
  // TODO: Read and return the number of jiffies for the system
  // TODO: Read and return the number of jiffies for the system
  //https://superuser.com/questions/88820/how-to-obtain-the-current-number-of-jiffies-since-reboot-in-linux
  //https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};
  string cpu, item;
  string line;
  long temp;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    //std::cout << cpu << std::endl;
    int res = cpu.compare("cpu");
    if (res == 0){
      std::string token;
      while (linestream >> token) {
      temp += std::stof(token);
      //std::cout << token <<std::endl;
      //std::cout << temp <<std::endl;
          }
      }
  }

  return temp;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
   
  //https://man7.org/linux/man-pages/man5/proc.5.html
  // Numner 22
  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};

  std::string s = std::to_string(pid);

  string cpu, item;
  string line;
  long temp;
  int count = 0;
  std::ifstream stream(kProcDirectory + s + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
      std::string token;
      while (count < 22) {
      linestream >> token;
      if (std::all_of(token.begin(), token.end(), isdigit))
      {
        temp = std::stof(token);
      }

      count += 1;
          }
      }
  return temp;

   }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() 
{ 


  // TODO: Read and return the number of active jiffies for the system
// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
//https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux

  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};

  std::string cpu, token;
  std::string line;
  //long temp;
  //int count = 0;
  long user1, nice, system1, irq, softirq, steal;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    linestream >> token;
    user1 = std::stof(token);

    linestream >> token;
    nice = std::stof(token);

    linestream >> token;
    system1 = std::stof(token);

    linestream >> token;
    //idle = std::stof(token);

    linestream >> token;
    //iowait = std::stof(token);

    linestream >> token;
    irq = std::stof(token);

    linestream >> token;
    softirq = std::stof(token);

    linestream >> token;
    steal = std::stof(token);

    linestream >> token;
    //guest = std::stof(token);

    linestream >> token;
    //guest_nice = std::stof(token);

      }

  //long idles = idle + iowait;
  long nonIdles = user1 + nice + system1 + irq + softirq + steal;
  //long totals = idles + nonIdles;
  return nonIdles;
 }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  

  // TODO: Read and return the number of active jiffies for the system
// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
//https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux


  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};

  std::string cpu, token;
  std::string line;
  //long temp;
  //int count = 0;
  long user1, nice, system1, irq, softirq, steal;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    linestream >> token;
    user1 = std::stof(token);

    linestream >> token;
    nice = std::stof(token);

    linestream >> token;
    system1 = std::stof(token);

    linestream >> token;
    //idle = std::stof(token);

    linestream >> token;
    //iowait = std::stof(token);

    linestream >> token;
    irq = std::stof(token);

    linestream >> token;
    softirq = std::stof(token);

    linestream >> token;
    steal = std::stof(token);

    linestream >> token;
    //guest = std::stof(token);

    linestream >> token;
    //guest_nice = std::stof(token);

      }

  //long idles = idle + iowait;
  long nonIdles = user1 + nice + system1 + irq + softirq + steal;
  //long totals = idles + nonIdles;
  return nonIdles;

 }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  

  vector<string> temp;
  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};
  string cpu, item;
  string line;
  //long temp;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu;
    //std::cout << cpu << std::endl;
    int res = cpu.compare("cpu");
    if (res == 0){
      std::string token;
      while (linestream >> token) {
      temp.push_back(token);
      //std::cout << token <<std::endl;
      //std::cout << temp <<std::endl;
          }
      }
  }

  return temp;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string processes, totalProcess;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> processes >> totalProcess;
      int res = processes.compare("processes");
      if (res == 0)
      {
        break;
      }
    }
    
  }
  int v = std::stof(totalProcess);
  return v;
  }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};
  string procs_running, numOfProcess;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open())
  {
    while (std::getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> procs_running >> numOfProcess;
      int res = procs_running.compare("procs_running");
      if(res == 0)
      {
        break;
      }
    }
  }
  float v = std::stof(numOfProcess);
  return v;
 }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 



  //https://man7.org/linux/man-pages/man5/proc.5.html
  // Numner 22
  const std::string kProcDirectory{"/proc/"};
  const std::string kCmdlineFilename{"/cmdline"};

  std::string s = std::to_string(pid);

  string cpu, item;
  string line;
  std::string temp;
  //int count = 0;
  std::ifstream stream(kProcDirectory + s + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);

      linestream >> temp;
      }
  return temp;

 }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatusFilename{"/status"};
  std::string s = std::to_string(pid);
  string VmSize,checkTest, checkTest2;
  string line;
  std::ifstream stream(kProcDirectory + s +  kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    { std::istringstream linestream(line);
    linestream >> checkTest >> checkTest2 ;
    int res = checkTest.compare("VmSize:");
    if (res == 0)
      {
      VmSize = checkTest2;
      break;
      }

    }
  }

  return VmSize;
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  
  const std::string kProcDirectory{"/proc/"};
  const std::string kStatusFilename{"/status"};
  std::string s = std::to_string(pid);
  string Uid,checkTest, checkTest2;
  string line;
  std::ifstream stream(kProcDirectory + s +  kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    { std::istringstream linestream(line);
    linestream >> checkTest >> checkTest2 ;
    int res = checkTest.compare("Uid:");
    if (res == 0)
      {
      Uid = checkTest2;
      break;
      }
    }
  }
  return Uid;

}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  

  const std::string UidToUse = LinuxParser::Uid(pid);
  const std::string queryToUse{"/etc/passwd"};
  string UserToUse,checkTest, checkTest2;
  string line, substr, firstItem;
  int res;
  std::ifstream stream(queryToUse);
  if (stream.is_open()) {
    while (std::getline(stream, line))
    {
    std::istringstream linestream(line);
    int count = 0;
    while( count < 2 )
        {
            if (count == 0){
              getline( linestream, firstItem, ':' );

            }
              getline( linestream, substr, ':' );
            count = count + 1;
            res = substr.compare(UidToUse);
            if (res == 0)
            {
              break;
            }
            }
      if (res == 0)
            {
              break;
            }
      }
  }
  return firstItem;


 }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  
  const std::string kProcDirectory{"/proc/"};
  const std::string kMeminfoFilename{"/stat"};

  std::string s = std::to_string(pid);

  string cpu, item;
  string line;
  long temp;
  int count = 0;
  std::ifstream stream(kProcDirectory + s + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
      std::string token;
      while (count < 22) {
      linestream >> token;
      if (std::all_of(token.begin(), token.end(), isdigit))
      {
        temp = std::stof(token);
      }

      count += 1;
          }
      }
  return temp;

 }
