/* 
 * File:   Search.cpp
 * Author: k5m
 * 
 * Created on November 1, 2017, 10:12 PM
 */
#include "Search.h"
	
extern void* WorkerFunction(void *arg);
extern pthread_mutex_t mutex1;




/***************************************************************************
 * Gets the user cmd line arguments and stores them in SearchPath 
 * and ThreadCount 
 ***************************************************************************/
void Search::GetUserArgs(char *argv[])
{
    string cond0 = "-help";
    string cond1 = "-t";
    
    
    if(argv[1] == cond0)                                                      
    {
        cout << "*******************************" << endl;
        cout << "*                             *" << endl;
        cout << "*    Threaded File Indexer    *" << endl;
        cout << "*     by Khalid AlAwadhi      *" << endl;
        cout << "*                             *" << endl;
        cout << "*******************************" << endl << endl;
        
        cout << "How to use: " << endl;
        cout << "1) $ /filepath\t <= will create 3 threads by default and search for .txt files in the specified location in addition to any sub-directories" << endl;
        cout << "2) $ -t 8 /filepath\t <= '-t' lets the program know that the user will input the number of threads they want to create, and the following number is how many threads to create followed by the path to start searching for .txt files." << endl;
        exit(1);
    }
    
    
    
    if(argv[1] == cond1)                                                        //if the user inputs "-t"
    {
        ThreadCount = atoi(argv[2]);
        if(ThreadCount > 1000)
        {
            cout << "ERROR: Max number of threads exceeded, limit of threads is 1000" << endl;
            exit(1);
        }
        SearchPath = argv[3];
    }
    
    else                                                                        //else the program will use 3 as the number of threads to create
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
    /* These lines of code handle fining the .txt files and storing them in a
     * path type vector */
    typedef vector<path> vec;                                                   //Path type Vector to store txt file paths
    vec PathVec;
    
    if(!exists(root) || !is_directory(root))
    { 
        cout<<"ERROR! Expected file path. Type in '-help' to learn how to use this program" << endl; 
        exit(1);
    }

    recursive_directory_iterator it(root);
    recursive_directory_iterator endit;

    while(it != endit)
    {
        if(is_regular_file(*it) && it->path().extension() == ext)
		PathVec.push_back(it->path());
        ++it;
    }
    
    /* These lines convert the path type vector to a string type vector */
    while(PathVec.empty() == 0)
    {
        path BoostPath = PathVec.back();					//Takes the filepath from the back of the vector
        PathVec.pop_back();                                                     //Dec vector by 1
        string txtlocation = BoostPath.string();                                //COnverts Boost path type to a string 
        
        TXTVec.push_back(txtlocation);                                          //Pushes it to TXTVec 
        Openedtxtfiles++;                                                       //Keeps track of how many .txt files were found 
    }
}




/***************************************************************************
 * Pops off one file path from the TXT Vector 
 ***************************************************************************/
string Search::PopOneTXTPath()
{
    string CurrentFile = TXTVec.back();					
    TXTVec.pop_back();
    return CurrentFile;
}



/***************************************************************************
 * Creates threads based on user input or default number
 ***************************************************************************/
void Search::CreateThreads()
{
    
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
 * TEST
 ***************************************************************************/
void Search::AddCompletedAddress()
{
//    CompletedWorkerMaps.push_back(Address);
}




/***************************************************************************
 * TEST
 ***************************************************************************/
void Search::CombineMapsAndResult()
{
  /*  typedef map<string,int> FinalMap;						//Word and Count Map
    FinalMap* BiglyVec = CompletedWorkerMaps.back();
   
    
    vector< pair<string,int> > WorkerMapVector;
    
    
    copy(BiglyVec.begin(), BiglyVec.end(), back_inserter(WorkerMapVector));   //Copies the values from map to vectors 

    int Count = 1;
    
    for(int i=0; i<WorkerMapVector.size(); i)                                   //Prints the words, starting with the most used
    {                                    
        cout << Count << " - " << WorkerMapVector[i].first << "\t" << WorkerMapVector[i].second << endl;
        ++i;
        Count++;
    } */
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