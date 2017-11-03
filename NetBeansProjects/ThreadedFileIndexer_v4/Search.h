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


using namespace std;
using namespace boost::filesystem;




class Search
{   
public:
    string SearchPath;
    int ThreadCount;
    
    void GetUserArgs(char**);
    void GetTXTPaths(const path& root, const string& ext, vector<path>& ret);  //Gets and stores full .txt file paths found in a vector - Found online, slightly modified
    void CreateThreads();
    void CreateBIGLYQ();
    void DoMethOnBIGLYQ();
    
    
    /* Debugging Purposes */
    
    //Prints the user input arguments 
    void PrintArgs()
    {
        cout << "Search path entered is: " << SearchPath << endl;
        cout << "Threads intended to create: " << ThreadCount << endl;
    };
    
    
    // Prints the .txt file paths stored in the vector and pops them off
    void PrintTXTPaths(vector<path> vecboost)
    {
        while(vecboost.empty() == 0)
        {
            path BoostPath = vecboost.back();					//Takes the filepath from the back of the vector
            vecboost.pop_back();
            string filepathString = BoostPath.string();
            cout << ".txt file found: " << filepathString << endl;
        }
        
    };
    
};




#endif /* SEARCH_H */