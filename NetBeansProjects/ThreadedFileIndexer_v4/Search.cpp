/* 
 * File:   Search.cpp
 * Author: k5m
 * 
 * Created on November 1, 2017, 10:12 PM
 */
#include "Search.h"
	
extern void* WorkerFunction(void *arg);
extern pthread_mutex_t mutex1;


/* Returns the greater value in our vector - Found Online, slightly modified */
struct val_greaterthan : binary_function < pair<string,int>, pair<string,int>, bool >{
bool operator() (const pair<string,int>& x, const pair<string,int>& y) const{
return x.second>y.second;}
}val_gt;



/***************************************************************************
 * Gets the user cmd line arguments and stores them in SearchPath 
 * and ThreadCount 
 ***************************************************************************/
void Search::GetUserArgs(char *argv[])
{
    string cond0 = "-help";
    string cond1 = "-t";
    string cond2 = "-top";
    

    if(argv[1] == cond0)                                                      
    {
        cout << "*******************************" << endl;
        cout << "*                             *" << endl;
        cout << "*    Threaded File Indexer    *" << endl;
        cout << "*     by Khalid AlAwadhi      *" << endl;
        cout << "*                             *" << endl;
        cout << "*******************************" << endl << endl;
        
        cout << "How to use: " << endl;
        cout << "1) $ /filepath:" << endl;
        cout << "The above will create 3 threads by default and search for .txt files in the specified location in addition to any sub-directories. It will also display the top 10 most used words." << endl << endl;;
        cout << "2) $ -t 8 /filepath:" << endl;
        cout << "The'-t' lets the program know that the user will input the number of threads they want to create, and the following number is how many threads to create followed by the path to start searching for .txt files." << endl << endl;
        cout << "3) $ -t 8 /filepath -top 12:" << endl;
        cout << "The '-top' argument allows the user to specify the number of most used words to display, it MUST be followed by a number or an error will appear." << endl;
        exit(1);
    }
    
    if(argv[1] != NULL & argv[2] == NULL)                                       //If the user only enters a path with no other args
    {
        ThreadCount = 3;                                                        //Default number of Threads to create is set to 3
        SearchPath = argv[1];                                                   //First arg is expected to be path to search
        Top = 10;                                                               //Default number of top words to display is set to 10
        return;
    }
 
    
    if(argv[1] == cond1 & argv[4] == NULL)                                      //if the user inputs "-t" without "-top" 
    {
        SearchPath = argv[3];                                                   //Takes in the third arg as path to search
        
        ThreadCount = atoi(argv[2]);                                            //Converts the number of threads from char to int
        
        Top = 10;                                                               //Converts from char to int
        
        if(ThreadCount > 1000)                                                  //Handles error
        {
            cout << "ERROR: Max number of threads exceeded, limit of threads is 1000" << endl;
            exit(1);
        }
        return;
    }
    
    
    if(argv[1] == cond1 & argv[4] == cond2 &  argv[5] == NULL)                   //if the user inputs "-t" and "-top" without a number
    {
        cout << "ERROR: Must enter a number of after '-top'" << endl;
        exit(1);
    }
    
    
    if(argv[1] == cond1 & argv[4] == cond2 & argv[5] != NULL)                   //if the user inputs "-t" with "-top" and a number
    {
        SearchPath = argv[3];                                                   //Takes in the third arg as path to search
        
        ThreadCount = atoi(argv[2]);                                            //Converts the number of threads from char to int
        
        Top = atoi(argv[5]);                                                    //Converts from char to int
        
        if(ThreadCount > 1000)                                                  //Handles error
        {
            cout << "ERROR: Max number of threads exceeded, limit of threads is 1000" << endl;
            exit(1);
        }
        return;
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
* Waits until all child threads are done processing 
****************************************************************************/
void Search::WaitForChildren()
{
    for (int i = 0; i < ThreadCount; i++)
    {
        pthread_join(threads[i], NULL);  
    }
}




/***************************************************************************
 * Stores all the processed words from a Worker Thread in one big vector
 ***************************************************************************/
void Search::StoreCompletedVecs(vector<string>& vec)
{
    int VecSize = vec.size();                                                   //Gets the size of the Worker word vector
    for(int i = 0; i < VecSize; i++)                                            //Loops and copies every element  
    {
    CompletedWorkerVecs.push_back(vec[i]);
    vec.pop_back();                                                             //Shrinks our Worker word vector to reduce memory consumption
    }
}




/***************************************************************************
 * Sorts through all the words stored in Searcher's completed vector. 
 ***************************************************************************/
void Search::SortCompletedVecs()
{
    typedef map<string,int> SearcherMap;                                        //Creates a map typedef to store both a string and an int
    SearcherMap WordCount;
    
    int CompSize = CompletedWorkerVecs.size();                                  //Gets the size of our Searcher's completed vector 
    
    for(int i = 0; i < CompSize; i++)                                           
    {
        string Word = CompletedWorkerVecs[i];                                   //Takes one word from Searcher's completed vector
        CompletedWorkerVecs.pop_back();                                         //Pops one element off => saves memory since we do not need it
        ++WordCount[Word];                                                      //Stores the word, and if the word already exists it will increment the count of the word
    }
    
    vector< pair<string,int> > WordsCountV;                                     
    copy(WordCount.begin(), WordCount.end(), back_inserter(WordsCountV));       //Copies the data from Searcher Map to the newly created WordsCount Vector
    sort(WordsCountV.begin(), WordsCountV.end(), val_gt);                       //Sorts the words in the vector by the second value instead of key (which is how many times the word was found)
    
    int TopWords = 1;
    for(int i=0; i < WordsCountV.size(); i)                                     //Prints the words, starting with the most used
    {                                    
        while(TopWords <= Top)                                                   //Top words will be displayed up to the number being compared with in this while loop
        {
            cout << TopWords << " - " << WordsCountV[i].first << "\t" << WordsCountV[i].second << endl;
            ++i;
            TopWords++;
        }
	break;
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
        cout << "Top words to display: " << Top << endl;
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