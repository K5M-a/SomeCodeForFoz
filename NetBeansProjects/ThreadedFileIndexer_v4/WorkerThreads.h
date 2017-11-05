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


using namespace std;
using namespace boost::filesystem;


class WorkerThread
{       
public:
    
    void GetTXTPath(string txtpath);                                    //Gets a .txt file path from the Searcher quene if it is not empty  
    
};

#endif /* WORKERTHREADS_H */
