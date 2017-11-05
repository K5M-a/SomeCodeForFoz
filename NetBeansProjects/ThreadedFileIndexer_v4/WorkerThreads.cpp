/* 
 * File:   WorkerThreads.cpp
 * Author: k5m
 * 
 * Created on November 2, 2017, 11:41 PM
 */

#include "WorkerThreads.h"
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;		//Lock/Unlock Threads


void WorkerThread::GetTXTPath(vector<path> TxtVector)
{ 
    while(TxtVector.empty() == 0)
    {
        pthread_mutex_lock( &mutex1 );				//LOCKKKKKKKK
        path BoostPath = TxtVector.back();					
        TxtVector.pop_back();
        pthread_mutex_unlock( &mutex1 );			//UNLOCKKKKKKK
        
        string TXTPath = BoostPath.string();
    }    
    
 //   if(TxtVector.empty() == 1)
 //   {
        
 //   }
    
}