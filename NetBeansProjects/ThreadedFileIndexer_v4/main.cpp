/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */


/* TO DO: */
// 1- UPDATE SEARCH PRINTTXTPATHS TO NOT POP OFF []
// 2- ADD WAY TO KEEP TRACK OF UNUSED WORKERS []
// 3- RESOLVE IWHERE TO PUT WORKERFUNCTION AND MAKE IT WORK PROPERLY []
// 4- 
// 


/* My Libraries */
#include "Search.h"
#include "WorkerThreads.h"

/* Global Varibles */
Search SearcherBoi;

void* WorkerFunction(void *arg)
{
    WorkerThread WorkerBoi;
    
    WorkerBoi.GetTXTPath(SearcherBoi.TxtPathVec);
}


int main(int argc, char *argv[])
{

    
    SearcherBoi.GetUserArgs(argv);          //Gets user input args
    
    path P(SearcherBoi.SearchPath);         //Converts the user input path to Boost Filesystem path type
    
    SearcherBoi.GetTXTPaths(P, ".txt");     //Uses Boost Library to get all .txt file and stores their paths in a vector
    
    SearcherBoi.CreateThreads();            //Creates threads based on user input
    
 //   SearcherBoi.PrintTXTPaths();            //Debugging purposes - Prints all the .txt files found 
    
    
}
