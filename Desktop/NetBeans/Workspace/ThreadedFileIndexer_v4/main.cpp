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





/*
 * 
 */
int main(int argc, char *argv[])
{
    Search SearcherBoi;
    
    SearcherBoi.GetUserArgs(argv);
    
    path P(SearcherBoi.SearchPath);
    
    SearcherBoi.GetTXTPaths(P, ".txt", v);
    

    
}

