/* 
 * File:   WorkerThreads.h
 * Author: k5m
 *
 * Created on November 2, 2017, 11:41 PM
 */

#ifndef WORKERTHREADS_H
#define WORKERTHREADS_H

#include <iostream>
#include <string>
#include "boost/filesystem.hpp"
#include <pthread.h>
#include <fstream>
#include <map>

using namespace std;
using namespace boost::filesystem;



class WorkerThread
{       
public:
    int FilesLeft = 1;                                                          //Keeps track if the queue has files left 
    int DidWork = 0;                                                            //Keeps track of the Thread if it did process a .txt file or not
    
    typedef map<string,int> ThreadMap;						//Change? Word and Count Map
    ThreadMap WorkerMap;
    
    void WorkOnTXTFile(string txtpath);
    void CompletedMap();
    
    
    /* Debugging Purposes */
    void PrintMap();

};

#endif /* WORKERTHREADS_H */