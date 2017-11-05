/* 
 * File:   Search.cpp
 * Author: k5m
 * 
 * Created on November 1, 2017, 10:12 PM
 */

/***************************************************************************
* GENERIC DESCRIPTION 
****************************************************************************/

#include "Search.h"
	
extern void* WorkerFunction(void *arg);



/***************************************************************************
 * Gets the user cmd line arguments and stores them in SearchPath 
 * and ThreadCount 
 ***************************************************************************/
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




/***************************************************************************
 * Gets and stores full .txt file paths found in a string type vector 
 ***************************************************************************/
void Search::GetTXTPaths(const path& root, const string& ext)
{   
    typedef vector<path> vec;                                                   //Path type Vector to store txt file paths
    vec PathVec;
    
    if(!exists(root) || !is_directory(root)) return;

    recursive_directory_iterator it(root);
    recursive_directory_iterator endit;

    while(it != endit)
    {
        if(is_regular_file(*it) && it->path().extension() == ext)
		PathVec.push_back(it->path());
        ++it;
    }
    
    while(PathVec.empty() == 0)
    {
        path BoostPath = PathVec.back();					//Takes the filepath from the back of the vector
        PathVec.pop_back();
        string txtlocation = BoostPath.string();
        
        TXTVec.push_back(txtlocation);
    }
}




/***************************************************************************
 * TEST
 ***************************************************************************/
string Search::PopOneTXTPath()
{
    string CurrentFile = TXTVec.back();					
    TXTVec.pop_back();
    return CurrentFile;
}



/***************************************************************************
 * Creates threads based on user input 
 ***************************************************************************/
void Search::CreateThreads()
{
 //   pthread_t threads = malloc(sizeof(pthread_t) * ThreadCount); Possibly fixes the many threads crash bug?
    
    for( int i = 0; i < ThreadCount; i++ )
    {	
        int ThreadError = pthread_create(&threads[i], NULL, WorkerFunction, NULL);
        
        if(ThreadError)
	{
            cout << "Error:unable to create thread," << ThreadError << endl;
        }
    }
}

/***************************************************************************
* Waits until all child threads are done proccessing 
****************************************************************************/
void Search::WaitForChildren()
{
    for (int i = 0; i < ThreadCount; i++)
    {
        pthread_join(threads[i], NULL);  
    }
}



/***************************************************************************
* DEBUGGING FUNCTION
* Prints the input user arguments
****************************************************************************/
void Search::PrintArgs()
{
        cout << "Search path entered is: " << SearchPath << endl;
        cout << "Threads intended to create: " << ThreadCount << endl;
};



/***************************************************************************
* DEBUGGING FUNCTION
* Prints the .txt file paths stored in the TXT vector 
****************************************************************************/
void Search::PrintTXTVector()
{
    for(int i = 0; i < TXTVec.size(); i++)
    {
        cout << "File found: " << TXTVec[i] << endl;
    }
}