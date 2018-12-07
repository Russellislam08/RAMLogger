/*
  C++ Continuous RAM Logger
  This program will periodically monitor your RAM consumption
  and log it into a log file.
  This will only work on a Linux system.
  This is a command line tool.
*/
#include <iostream>
#include <stdlib.h>

// Header file which contains the Logger class
#include "logger.h"

using namespace std;

int main(const int argc, const char* const argv[]){
  // Create the logger
  Logger testLogger(atof(argv[1]), argv[2]);

  // Start the logger
  cout << "Starting logger..." << endl;
  testLogger.logger();
  
  return 0;
}
