/* 
 * File:   WorkerThreads.cpp
 * Author: k5m
 * 
 * Created on November 2, 2017, 11:41 PM
 */

#include "WorkerThreads.h"



/***************************************************************************
 * Takes in a .txt file path string input, cleans it and stores each
 * individual word in a vector to be used later
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

            WorkerVec.push_back(Word);
        }
    }
}




/***************************************************************************
 * DEBUGGING FUNCTION
 * Prints the contents of the current Worker thread vector
 ****************************************************************************/
void WorkerThread::PrintVec()
{      
    if(DidWork == 1)
    {
        int Count = 1;

        for(int i=0; i<WorkerVec.size(); i)                                   //Prints the words, starting with the most used
        {                                    
            cout << Count << " - " << WorkerVec[i] << endl;
            ++i;
            Count++;
        }
    
    }
    
    else if(DidWork == 0)
    {
        cout << "This thread did not do shit" << endl;
    }
}