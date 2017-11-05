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


using namespace std;
using namespace boost::filesystem;




class Search
{   
public:
    string SearchPath;                                                          //Stores user input path
    int ThreadCount;                                                            //Stores number of Threads to be created
    pthread_t threads[1000];                                                    //Initialize pthreads
    vector<string> TXTVec;                                                      //String type vector that stores all .txt file paths

    
    void GetUserArgs(char**);     
    void GetTXTPaths(const path& root, const string& ext);                      
    void CreateThreads();
    string PopOneTXTPath();
    void WaitForChildren();   
    
    /* Under-construction */
    void CreateBIGLYQ();                                                        //Should create a huge Q that stores all the Worker threads Maps
    void DoMethOnBIGLYQ();                                                      //Should sort through all the Maps in the BIGLYQ and show top 10 words
    
    
    /* Debugging Purposes */
    void PrintArgs();
    void PrintTXTVector();
    
};




#endif /* SEARCH_H */