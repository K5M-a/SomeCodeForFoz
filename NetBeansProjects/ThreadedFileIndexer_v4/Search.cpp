/* 
 * File:   Search.cpp
 * Author: k5m
 * 
 * Created on November 1, 2017, 10:12 PM
 */

#include "Search.h"


void Search::GetUserArgs(char *argv[])
{
    string cond1 = "-t";
    
    if(argv[1] == cond1)
    {
        ThreadCount = atoi(argv[2]);
        SearchPath = argv[3];
    }
    
    else
    {
        ThreadCount = 3;
        SearchPath = argv[1];
    }
}

void Search::GetTXTPaths(const path& root, const string& ext, vector<path>& ret)
{   
    if(!exists(root) || !is_directory(root)) return;

    recursive_directory_iterator it(root);
    recursive_directory_iterator endit;

    while(it != endit)
	{
        if(is_regular_file(*it) && it->path().extension() == ext)
		ret.push_back(it->path());
        ++it;
    }
}