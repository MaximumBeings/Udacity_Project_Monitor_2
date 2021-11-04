#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
#include <thread>
#include <unistd.h>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {

 public:
    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp


 Process(int pid) : Pid_(pid){
 setUser();
 setCommand();
 setRam();
 setUtil();
 setUpTime();

 }
 // TODO: Declare any necessary private members
 // Setters

 void setUser(){
 User_  = LinuxParser::User(Pid_);
 if (User_.length() > 6){
     User_ = User_.substr (0,6);
 }
 }

 void setCommand(){
 Command_ = LinuxParser::Command(Pid_);
 if (Command_.length() > 30){
     Command_ = Command_.substr (0,30);
 }
 }

 void setRam()
 {
  std::string noValueChecker = "";
  std::string temp  = LinuxParser::Ram(Pid_);

  if (!temp.empty()) {
  int num1 = std::stoi(temp);
  int num2 = num1/1024;
  std::string temp2 = std::to_string(num2);
  Ram_ = temp2;
  }
  else{
   Ram_ = noValueChecker;
  }


 }

  void setUtil()
    {
     long BeForeJiffies = LinuxParser::ActiveJiffies(Pid_);
     std::this_thread::sleep_for(std::chrono::milliseconds(10));
     long AfterJiffies = LinuxParser::ActiveJiffies(Pid_);
     long TotalJiffies = BeForeJiffies + AfterJiffies;
     CpuUtilization_  =  ( AfterJiffies- BeForeJiffies) / TotalJiffies;

     //CpuUtilization_ = LinuxParser::ActiveJiffies(Pid_);

    }

 void setUpTime()
    {
      UpTime_ = LinuxParser::UpTime()-(LinuxParser::UpTime(Pid_)/sysconf(_SC_CLK_TCK));
    }

 //Getters
 std::string getUser()
    {
      return User_ ;
    }

    std::string getCommand()
    {
      return Command_;
    }

    float getUtil()
    {
      return CpuUtilization_;
    }

     std::string getRam()
    {
      return Ram_ ;
    }

 private:
     int Pid_;
     std::string User_;
     std::string Command_;
     float CpuUtilization_;
     std::string Ram_;
     long UpTime_;
};

#endif