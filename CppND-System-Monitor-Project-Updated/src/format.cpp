#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) 
{ 
    //Source: StackOverFlow
    int hh = seconds / 3600;
    int mm = (seconds % 3600) / 60;
    int ss = (seconds % 3600) % 60;

    char timestring[9];
    sprintf(timestring, "%02d:%02d:%02d", hh, mm, ss);

    return string(timestring);


}