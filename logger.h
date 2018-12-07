/*
  logger.h
  Header file which contains the logger class and a helper function
*/
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <time.h>

// Helper functions which allow to read /proc/meminfo file for necessary info
#include "readproc.h"

#ifndef LOGGER
#define LOGGER

using namespace std;

// Helper function which is used to get current timestamp
const string currentDateTime(){
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);

  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

class Logger{
  public:
    // Constructor
  	Logger(int interval, string path);

    // Main class function which runs the logger
    void logger();
  
  protected:
    // Class Functions
    void createInitialFile();
  	void periodicLog();
  	void logMemoryUsage();
  
    // Class Variables
  	int interval;
  	string path;
  	ofstream myFile;

};

Logger::Logger(int interval, string path){
  this->interval = interval;
  this->path = path;
}

void Logger::logger(){
  /* This is the main function which is called.
     The initial file gets created, or appended to if it already exists.
     After that, the logger will periodically log to the file the 
     current amount of free and physical memory available
  */
  this->createInitialFile();
  this->periodicLog();
}

void Logger::createInitialFile(){
  /* Initially creates the file */
  myFile.open(path, std::ios_base::app);
  myFile << "============================================\n";
  myFile << "RAM Logger Start Time: " << currentDateTime() << "\n";
  myFile << "============================================\n";
  myFile.close();
}

void Logger::logMemoryUsage(){
  /* Write to the file current amount of memory used and memory available,
     along with a timestamp 
  */

  float scalingFactor = 1000;
  int totalMemory = GetMemTotal();
  int availableMemory = GetMemAvail();
  int memoryUsed = totalMemory - availableMemory;

  myFile.open(path, std::ios_base::app);
  myFile << "[" << currentDateTime() << "]" << " ";
  myFile << "Physical Memory Used: " << memoryUsed/scalingFactor << "mb";
  myFile << " | ";
  myFile << "Physical Memory Available: " << availableMemory/scalingFactor << "mb\n";
  myFile.close();
}

void Logger::periodicLog(){
  /* Periodically logs to the file
     Uses the interval passed in as a command line argument
  */
  while (true){
    this->logMemoryUsage();
    sleep(interval);
  }
}

#endif
