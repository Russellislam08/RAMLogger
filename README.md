# RAMLogger
A continuous memory usage logger using C++ for a Linux system

## What is this?
This is a command line tool which will periodically log your current physical memory usage into a log file. The purpose of thisis so that one can gauge how much memory they use over a certain period of time with certain conditions.

## Why Did I Make This?
I was in the market for purchasing a new laptop as my current one, the one I used to write this, is in a very bad condition and warrants a replacement. However, the particular laptop I was looking at purchasing did not have user upgradeable memory.
This meant that the configuration I buy now is permanent and cannot be changed. Since the memory was not upgradeable, I had to decide just how much I actually require. But to do so, I needed to know just how much of my system RAM do I actually use. 
So, I decided to write a little program that would run in the background while I'm using my system under typical conditions and monitor how much memory I am using. At the end, this helped me figure out how much memory I would require in my future system but also made me more wary about just how much memory I use, even though it might not feel like a lot.

## How to use this
Just simply clone the repository to your system. (This will only work on a Linux system as it reads system files. I used this on a machine running Ubuntu 18.04).
Next, compile the main.cpp file using g++ and execute the compiled file. The file requires two command line arguments when executing:
- The first argument is the interval size. This determines how often the logger will log to a specified log file. This is measured in seconds. For example, a value of '60' will make the program log in intervals of 60 seconds.
- The second argument is the path to the file which the program will log to. This can be relative or absolute and does not require a file extension.
Once you're done, simply press ctrl+c to terminate the program.
