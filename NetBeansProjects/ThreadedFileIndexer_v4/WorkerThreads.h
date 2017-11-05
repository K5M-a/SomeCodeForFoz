/* 
 * File:   WorkerThreads.h
 * Author: k5m
 *
 * Created on November 2, 2017, 11:41 PM
 */

#ifndef WORKERTHREADS_H
#define WORKERTHREADS_H

#include <string>
#include "boost/filesystem.hpp"
#include <pthread.h>


using namespace std;
using namespace boost::filesystem;


class WorkerThread
{   
    
public:
    string TXTPath;
    
    void GetTXTPath(vector<path> TxtVector);
    
};

#endif /* WORKERTHREADS_H */
