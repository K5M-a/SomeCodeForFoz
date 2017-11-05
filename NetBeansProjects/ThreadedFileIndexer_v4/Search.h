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
    string SearchPath;
    int ThreadCount;
    
    typedef vector<path> vec;   	//Vector to store txt file paths
    vec TxtPathVec;

    
    void GetUserArgs(char**);                                                   //Gets the user cmd line argumengts and stores them in SearchPath and ThreadCount
    void GetTXTPaths(const path& root, const string& ext);                      //Gets and stores full .txt file paths found in a vector
    void CreateThreads();                                                       //Creates threads based on user input
    
    /* Under-construction */
    void CreateBIGLYQ();                                                        //Should create a huge Q that stores all the Worker threads Maps
    void DoMethOnBIGLYQ();                                                      //Should sort through all the Maps in the BIGLYQ and show top 10 words
    
    
    /* Debugging Purposes */
    //Prints the user input arguments 
    void PrintArgs()
    {
        cout << "Search path entered is: " << SearchPath << endl;
        cout << "Threads intended to create: " << ThreadCount << endl;
    };
    
    
    // Prints the .txt file paths stored in the vector and pops them off
    void PrintTXTPaths()
    {
        while(TxtPathVec.empty() == 0)
        {
            path BoostPath = TxtPathVec.back();					//Takes the filepath from the back of the vector
            TxtPathVec.pop_back();
            string filepathString = BoostPath.string();
            cout << ".txt file found: " << filepathString << endl;
        }
        
    };
    
};




#endif /* SEARCH_H */