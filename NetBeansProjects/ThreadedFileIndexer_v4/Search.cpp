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


void Search::GetTXTPaths(const path& root, const string& ext)
{   
    if(!exists(root) || !is_directory(root)) return;

    recursive_directory_iterator it(root);
    recursive_directory_iterator endit;

    while(it != endit)
	{
        if(is_regular_file(*it) && it->path().extension() == ext)
		TxtPathVec.push_back(it->path());
        ++it;
    }
}


void Search::CreateThreads()
{
 //   pthread_t threads = malloc(sizeof(pthread_t) * ThreadCount); Possibly fixes the many threads crash bug?
    
    pthread_t threads[ThreadCount];		//Initialize threads
    
    for( int i = 0; i < ThreadCount; i++ )
    {	
        int ThreadError = pthread_create(&threads[i], NULL, WorkerFunction, NULL);
        
        if(ThreadError)
	{
            cout << "Error:unable to create thread," << ThreadError << endl;
        }
    }
}