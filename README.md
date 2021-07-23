# windows_ddos

Written and tested on Visual Studio 2019 (Windows 10 x64)

Compile:
 - Any windows C++ compiler that allows you to work with threads
===================================================================

Usage:
dos.exe <ip>:<port>
 
Example:
 - dos.exe 192.168.1.17:8080
 - dos.exe 8.8.8.8:53
====================================================================
 
Number of threads 16 (by default)
Number of connections per thread 32 (by default)

You can change this values by editing these lines in dos.cpp
 - #define THREADS 16
 - #define CONNECTIONS 32
