/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

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
    
        while(v.empty() == 0)
        {
            path BoostPath = v.back();					//Takes the filepath from the back of the vector
            v.pop_back();
            string filepathString = BoostPath.string();
            cout << ".txt file found: " << filepathString << endl;
        }
        
        if(v.empty()){
            cout << "Boi we out" << endl;
        }
    
}
