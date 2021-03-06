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
    int Top = 10;                                                               //Stores top how many words to display (Default is top 10 words)
    pthread_t threads[1000];                                                    //Initialize a limit of 1000 pthreads
    vector<string> TXTVec;                                                      //String type vector that stores all .txt file paths
    vector<string> CompletedWorkerVecs;                                         //Stores all the data from every Worker word vector
    int UnusedWorkers = 0;                                                      //Keeps track of unused Worker Threads

    
    void GetUserArgs(char**);     
    void GetTXTPaths(const path& root, const string& ext);                      
    void CreateThreads();
    string PopOneTXTPath();
    void WaitForChildren(); 
    void StoreCompletedVecs(vector<string>& vec);
    void SortCompletedVecs();                                              
    
    
    /* Debugging Purposes */
    void PrintArgs();
    void PrintTXTVector();
    
};




#endif /* SEARCH_H */