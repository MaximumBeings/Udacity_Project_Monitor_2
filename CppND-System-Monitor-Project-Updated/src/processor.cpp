#include "processor.h"
#include "linux_parser.h"
#include <thread>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {


        long PrevIdle = LinuxParser::IdleJiffies() ;
        long PrevNonIdle = LinuxParser::ActiveJiffies();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        long Idle = LinuxParser::IdleJiffies() ;
        long NonIdle = LinuxParser::ActiveJiffies();
        long PrevTotal = PrevIdle + PrevNonIdle;
        long Total = Idle + NonIdle;
        // differentiate: actual value minus the previous one
        long int totald = Total - PrevTotal;
        long int idled = Idle - PrevIdle;

        //(totald - (idle - previdle)) / totald * 100)
        float CPU_Percentage;
        CPU_Percentage = ((totald - idled)*1.0)/(totald*1.0);

        //https://stackoverflow.com/questions/1343890/how-do-i-restrict-a-float-value-to-only-two-places-after-the-decimal-point-in-c
        double scale = 0.01;  // i.e. round to nearest one-hundreth
        CPU_Percentage = (int)(CPU_Percentage / scale) * scale;
        return CPU_Percentage;





}