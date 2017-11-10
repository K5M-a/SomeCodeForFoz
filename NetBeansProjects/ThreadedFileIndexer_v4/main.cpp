/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */


/* TO DO: */
// 1- UPDATE SEARCH PRINTTXTPATHS TO NOT POP OFF [COMPLETED]
// 2- ADD WAY TO KEEP TRACK OF UNUSED WORKERS [COMPLETED]
// 3- RESOLVE WHERE TO PUT WORKERFUNCTION AND MAKE IT WORK PROPERLY [COMPLETED]
// 4- FIX GETTING TXT FILE FROM SEARCHBOI NOT UPDATING SEARCHERBOI IN WORKERTHREAD GETTXTPATH FNC [COMPLETED]
// 5- CREATE FOUND .TXT FILE COUNTER [COMPLETED]
// 6- STORE THE ADDRESS OF THE COMPLETED MAP IN THE BIGLYQ []
// 7- IMPORTANT: MAKE SURE THREAD LOOPS UNTIL THERE ARE NO MORE FILES => FIX LOGIC IN WORKERFUNCTION [COMPLETED]
// 8- DEVISE NEW WAY TO STORE WORDS AND HOW MANY TIKES THEY APPEARED []
// 9- 
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
    WorkerThread WorkerBoi;                                                     //Creates a WorkerThread 
    
    while((WorkerBoi.FilesLeft == 1))                                           //While WorkerBoi can still take in files
    {
        string txtpath = "NULL";                                                //Default string txt path naming, used for errors
        pthread_mutex_lock( &mutex1 );                                          //LOCKSSSSS the pthreads
        if((SearcherBoi.TXTVec.empty() == 0))                                   //If SearcherBoi still has txt files in its queue
        {
            txtpath = SearcherBoi.PopOneTXTPath();                              //Takes one .txt path and removes it from SearcherBoi queue
            WorkerBoi.DidWork = 1;                                              //Used for debugging, checks if the WorkerBoi did actual work and not waste time procrastinating like I always do wtf man 
        }
        else
        {
            WorkerBoi.FilesLeft = 0;                                            //If SearcherBoi has files left, set this to 0 
        }
        pthread_mutex_unlock( &mutex1 );                                        //UNLOCKSSSSSSSSSSSS pthreads
        
        WorkerBoi.WorkOnTXTFile(txtpath);                                       //Here is where the REAL operation on the txt files is done
    }
    
    pthread_mutex_lock( &mutex1 );
    WorkerBoi.PrintMap();
    pthread_mutex_unlock( &mutex1 );
    
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
