/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */


/* TO DO: */
// 1- UPDATE SEARCH PRINTTXTPATHS TO NOT POP OFF [COMPLETED]
// 2- ADD WAY TO KEEP TRACK OF UNUSED WORKERS []
// 3- RESOLVE WHERE TO PUT WORKERFUNCTION AND MAKE IT WORK PROPERLY [COMPLETED]
// 4- FIX GETTING TXT FILE FROM SEARCHBOI NOT UPDATING SEARCHERBOI IN WORKERTHREAD GETTXTPATH FNC [COMPLETED]
// 5- CREATE FOUND .TXT FILE COUNTER [COMPLETED]
// 6- STORE THE ADDRESS OF THE COMPLETED MAP IN THE BIGLYQ []
// 7- IMPORTANT: MAKE SURE THREAD LOOPS UNTIL THERE ARE NO MORE FILES => FIX LOGIC IN WORKERFUNCTION []
// 8- 
// 


/* My Libraries */
#include "Search.h"
#include "WorkerThreads.h"

/* Global Varibles */
Search SearcherBoi;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;                             //Lock/Unlock Threads


//vector<uintptr_t> MapPtr;

//    pthread_mutex_lock( &mutex1 );                                              //LOCKKKKKKKK
//    pthread_mutex_unlock( &mutex1 );                                            //UNLOCKKKKKKK


void* WorkerFunction(void *arg)
{
    WorkerThread WorkerBoi;
                 
    /* Locks the current thread to finish this task, because each thread will 
     * access the Vector that stores the .txt files paths and take only 1 file. 
     * However, ADD FEATURE HERE */
    
    pthread_mutex_lock( &mutex1 ); 
    while((SearcherBoi.TXTVec.empty() == 0))
    {
        string txtpath = SearcherBoi.PopOneTXTPath();
        pthread_mutex_unlock( &mutex1 );
        WorkerBoi.WorkOnTXTFile(txtpath);
    }
    
    if((SearcherBoi.TXTVec.empty() == 1))
    {
        pthread_mutex_unlock( &mutex1 );
    }
}


int main(int argc, char *argv[])
{
    SearcherBoi.GetUserArgs(argv);                                              //Gets user input args
    
    path P(SearcherBoi.SearchPath);                                             //Converts the user input path to Boost Filesystem path type
    
    SearcherBoi.GetTXTPaths(P, ".txt");                                         //Uses Boost Library to get all .txt file and stores their paths in a vector
    
    SearcherBoi.CreateThreads();                                                //Creates threads based on user input
    
    SearcherBoi.WaitForChildren();
    
    
    
    
    cout << "Number of .txt files found: " << SearcherBoi.Openedtxtfiles << endl;
    cout << "Threads created: " << SearcherBoi.ThreadCount << endl;
    
}
