/* 
 * File:   Search.h
 * Author: k5m
 *
 * Created on November 1, 2017, 10:12 PM
 */

#ifndef SEARCH_H
#define SEARCH_H


#include <iostream>
#include <string>
#include "boost/filesystem.hpp"
#include <iterator>
#include <algorithm>
#include <pthread.h>
#include <map>


using namespace std;
using namespace boost::filesystem;





class Search
{   
public:
    int Openedtxtfiles = 0;                                                     //Keeps track of the number of .txt files opened
    string SearchPath;                                                          //Stores user input path
    int ThreadCount;                                                            //Stores number of Threads to be created
    pthread_t threads[1000];                                                    //Initialize pthreads
    vector<string> TXTVec;                                                      //String type vector that stores all .txt file paths
    
    
  //  typedef map<int> FinalMap;						//Word and Count Map
  //  FinalMap CompletedWorkerMaps;

    
    void GetUserArgs(char**);     
    void GetTXTPaths(const path& root, const string& ext);                      
    void CreateThreads();
    string PopOneTXTPath();
    void WaitForChildren(); 
    
    void AddCompletedAddress();
    void CombineMapsAndResult();                                                
    
    
    /* Debugging Purposes */
    void PrintArgs();
    void PrintTXTVector();
    
};




#endif /* SEARCH_H */