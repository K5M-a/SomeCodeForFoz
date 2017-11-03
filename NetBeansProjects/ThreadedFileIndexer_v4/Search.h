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

/* Global Variables */
typedef vector<path> vec;   	//Vector to store txt file paths
vec v;


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
    void PrintTXTPaths()
    {
        while(v.empty() == 0)
        {
            path BoostPath = v.back();					//Takes the filepath from the back of the vector
            v.pop_back();
            string filepathString = BoostPath.string();
            cout << ".txt file found: " << filepathString << endl;
        }
        
        if(v.empty()){
            cout << "Boi we out" << endl;
        }
        
    };
    
};




#endif /* SEARCH_H */