/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */

/* My Libraries */
#include "Search.h"

/* Global Variables */
typedef vector<path> vec;   	//Vector to store txt file paths
vec v;

int main(int argc, char *argv[])
{
    Search SearcherBoi;
    
    SearcherBoi.GetUserArgs(argv);
    
    path P(SearcherBoi.SearchPath);
    
    SearcherBoi.GetTXTPaths(P, ".txt", v);
    
    SearcherBoi.CreateThreads();
    
    
    
}
