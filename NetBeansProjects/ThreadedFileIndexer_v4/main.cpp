/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */

/* What happened? 
 * - Started basically from scratch => rewritten almost all the project
 * 
 * - Working with pointers to Vectors, Maps, or Arrays WAS A BITTTTTTTTTTTTTTTT hard. It simply did not work no matter
 *   how much time and techniques I used. I gave up on using pointers to link memory locations. So many issues arised 
 *   from syntax errors to basically nothing new but with more lines of code... 
 * 
 * - New way I created: have each worker take as many a .txt files as they can process, go though it removing any number,
 *   punctuations, etc. then once its done and there are no more files to process, then and ONLY THEN will the worker
 *   LOCK itself with the Searcher. The Searcher will take all the words the Worker has stored, and at the same time memory 
 *   will be freed. Then the worker will UNLOCK and disappear. 
 * 
 * - I was going to create a Worker class deconstructor, however, I free most of the memory when I take the data from 
 *   the Worker and move it to teh Searcher. Hence there is barely anything to delete aside from a few ints.
 * 
 * - Added '-help' command
 * 
 * - FIXED THE BUG CAUSING THE PROGRAM TO CRASH IF THE USER INPUTS TOO MANY THREADS TO CREATE!!
 * 
 * - Put some error handlers in place
 *      1) limit thread amount creation ( >1000 )
 *      2) if the user enters an unexpected input, the program will notify user
 * 
 * - Used Git
 * 
 * - Added more stats at the end of program run
 * 
 * - 
 * 
 *   */

/* TO DO: */
// 1- UPDATE SEARCH PRINTTXTPATHS TO NOT POP OFF [COMPLETED]
// 2- ADD WAY TO KEEP TRACK OF UNUSED WORKERS [COMPLETED]
// 3- RESOLVE WHERE TO PUT WORKERFUNCTION AND MAKE IT WORK PROPERLY [COMPLETED]
// 4- FIX GETTING TXT FILE FROM SEARCHBOI NOT UPDATING SEARCHERBOI IN WORKERTHREAD GETTXTPATH FNC [COMPLETED]
// 5- CREATE FOUND .TXT FILE COUNTER [COMPLETED]
// 6- STORE THE ADDRESS OF THE COMPLETED MAP IN THE BIGLYQ [REEEEEEEEEEEEEEEEEEEEEEEEEJECTEDDDDDDDD]
// 7- IMPORTANT: MAKE SURE THREAD LOOPS UNTIL THERE ARE NO MORE FILES => FIX LOGIC IN WORKERFUNCTION [COMPLETED]
// 8- DEVISE NEW WAY TO STORE WORDS AND HOW MANY TIMES THEY APPEARED [COMPLETED]
// 


/* My Libraries */
#include "Search.h"
#include "WorkerThreads.h"

/* Global Variables */
Search SearcherBoi;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;                             //Lock/Unlock Threadsint UnusedWorkers = 0;                                                      //Keeps track of unused workers 



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
    if(WorkerBoi.DidWork == 0)
    {
        SearcherBoi.UnusedWorkers++;
    }
    else
    {
        SearcherBoi.StoreCompletedVecs(WorkerBoi.WorkerVec);
    }
    pthread_mutex_unlock( &mutex1 );
    
}


int main(int argc, char *argv[])
{
    SearcherBoi.GetUserArgs(argv);                                              //Gets user input args
    
    path P(SearcherBoi.SearchPath);                                             //Converts the user input path to Boost Filesystem path type
    
    SearcherBoi.GetTXTPaths(P, ".txt");                                         //Uses Boost Library to get all .txt file and stores their paths in a vector
    
    SearcherBoi.CreateThreads();                                                //Creates threads based on user input
    
    SearcherBoi.WaitForChildren();
    
    SearcherBoi.SortCompletedVecs();

    
    
    cout << "Number of .txt files found: " << SearcherBoi.Openedtxtfiles << endl;
    cout << "Threads created: " << SearcherBoi.ThreadCount << endl;
    cout << "Threads not used: " << SearcherBoi.UnusedWorkers << endl;
}