#ifndef SETUP_HPP
#define SETUP_HPP

//basic io,string modification, and system call functions
#include <iostream>
#include <ncurses.h>
#include <string>

#include <array> // safer array modifications

#include <thread> // threads
#include <atomic> // thread variables
#include <chrono> // wait function
#include <mutex> // safer array access

using namespace std;
void printGrid(char grid[20][10]);
void drop(char grid[20][10]);
void resetGrid(char grid[20]);

void initNcurses();

void mov(char grid[20][10]);
void shiftLeft();
void shiftRight();

extern atomic<int> pattern[10];
extern atomic<bool> run;
extern mutex grid_mutex;

#endif

                    
