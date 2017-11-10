/* 
 * File:   WorkerThreads.cpp
 * Author: k5m
 * 
 * Created on November 2, 2017, 11:41 PM
 */

#include "WorkerThreads.h"



/***************************************************************************
 * Takes in a .txt file path string input and gets the words and the number
 * of times each word was used 
 ****************************************************************************/
void WorkerThread::WorkOnTXTFile(string txtpath)
{
    if(txtpath != "NULL"){
        ifstream file;                                                                      //File class
        file.open(txtpath.c_str());                                                         //Opens file based on txtpath

        string Word;
        while (file >> Word)
        {
            Word.erase(remove_if(Word.begin(), Word.end (), ::ispunct), Word.end ());	//Removes punctuations from the word

            Word.erase(remove_if(Word.begin(), Word.end (), ::isdigit), Word.end ());	//Removes any numbers

            transform(Word.begin(), Word.end(), Word.begin(), ::tolower);		//Transforms the word to lower-case

            ++WorkerMap[Word];
        }
    }
}




/***************************************************************************
 * Stores the address of the completed Worker thread map
 ****************************************************************************/
void WorkerThread::CompletedMap()
{ 

  
 // for(int i = 0; < i < )
    
    /* using memcpy to copy structure: */
 // memcpy ( &BiglyQ, &WorkerMap, sizeof(WorkerMap) );
  
    /* BACKUP
     * 
     *     
    ThreadMap* pmap = &WorkerMap;
    
    cout << pmap << endl;
     * 
     * ////////////////////////
     * 
    uintptr_t MapAddress = (uintptr_t)&WorkerMap;
    return MapAddress;
     */
}



/***************************************************************************
 * DEBUGGING FUNCTION
 * Prints the map of the current thread
 ****************************************************************************/
void WorkerThread::PrintMap()
{      
    if(DidWork == 1){
    vector< pair<string,int> > WorkerMapVector;
    
    copy(WorkerMap.begin(), WorkerMap.end(), back_inserter(WorkerMapVector));   //Copies the values from map to vectors 
 //   sort(WorkerMap.begin(), WorkerMap.end(), val_gt);                           //Sorts the words in the vector by the second value instead of key
	
    int Count = 1;
    
    for(int i=0; i<WorkerMapVector.size(); i)                                   //Prints the words, starting with the most used
    {                                    
        cout << Count << " - " << WorkerMapVector[i].first << "\t" << WorkerMapVector[i].second << endl;
        ++i;
        Count++;
    }
    
    
    cout << "Map Address is: " << &WorkerMap << endl;
    }
    else if(DidWork == 0){
        cout << "This thread did not do shit" << endl;
    }
}