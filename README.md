# RAM Logger
A continuous memory usage logger using C++ for a Linux system

## What is This?
This is a command line tool which will periodically log your current physical memory usage into a log file. The purpose of this is so that one can gauge how much memory they use over a certain period of time with certain conditions.

## Why Did I Make This?
I was in the market for purchasing a new laptop as my current one, the one I used to write this, is in a very bad condition and warrants a replacement. However, the particular laptop I was looking at purchasing did not have user upgradeable memory.

This meant that the configuration I buy now is permanent and cannot be changed. Since the memory was not upgradeable, I had to decide just how much I actually require. But to do so, I needed to know just how much of my system RAM do I actually use on a typical basis.

So, I decided to write a little program that would run in the background while I'm using my system under typical conditions and monitor how much memory I am using. At the end, this helped me figure out how much memory I would require in my future system but also made me more wary about just how much memory I use, even though it might not feel like a lot.

## How to Use This
Just simply clone the repository to your system. (This will only work on a Linux system as it reads system files. I used this on a machine running Ubuntu 18.04).

Next, compile the main.cpp file using g++ and execute the compiled file. The file requires two command line arguments when executing:
- The first argument is the interval size. This determines how often the logger will log to a specified log file. This is measured in seconds. For example, a value of '60' will make the program log in intervals of 60 seconds.
- The second argument is the path to the file which the program will log to. This can be relative or absolute and does not require a file extension.

Once you're done, simply press ctrl+c to terminate the program.

## How Did I Get Memory Information?
This was the most difficult part of the program, as there isn't a completely straight forward approach.

There exists a directory on Linux machines which contains system information about running processes, memory information, system runtime etc. This directory is:

    /proc

However, the "proc file system" is special as it is a virtual file system. This means that they are not necessarily "real" files but it contains system runtime information. Since it is not a real file system, it is generally not a good idea to parse files within /proc.

There is a built in C++ library on Linux machines called "sys/sysinfo.h" which should suffice to not have to parse the proc files. This library provides system statistics such as memory and swap memory usage. However, when I tried invoking this library to retrieve the values I required, the numbers given were slightly different than what were shown in the proc files. This is weird because the documentation for sysinfo itself says that all the information can be found within the proc directory. Not only does sysinfo provide numbers which seem off, it also does not provide all the information required. Specifically, it does not provide available memory.

Upon further research, I found out that some Linux commands do indeed parse the files in /proc to get necessary information. Commands such as "top" parse these proc files themselves to get the information they require. Although it is not a good idea in general to parse these files, there exists one file which seems safe to parse as it remains consistent, which is:

    /proc/meminfo 
    
This file contains the main information such as total memory, free memory, available memory etc.

Thus, I created a few functions which parses /proc/meminfo to retrieve the total system memory and the amount of system memory available.
