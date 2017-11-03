/* 
 * File:   main.cpp
 * Author: k5m
 *
 * Created on November 1, 2017, 10:09 PM
 */

/* My Libraries */
#include "Search.h"



int main(int argc, char *argv[])
{
    Search SearcherBoi;
    
    SearcherBoi.GetUserArgs(argv);
    
    path P(SearcherBoi.SearchPath);
    
    SearcherBoi.GetTXTPaths(P, ".txt", v);
    
    SearcherBoi.PrintArgs();
    SearcherBoi.PrintTXTPaths();
    
}
