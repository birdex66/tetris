#ifndef SETUP_HPP
#define SETUP_HPP

//basic io,string modification, and system call functions
#include <iostream>
#include <ncurses.h>
#include <string>
#include <bits/stdc++.h>


#include <array> // safer array modifications
#include <vector> // holds all block combos

#include <thread> // threads
#include <atomic> // thread variables
#include <chrono> // wait function
#include <mutex> // safer array access

using namespace std;
void initalizePattern(int patternIndex);
void printGrid(const char grid[23][10]);
void drop(char grid[23][10]);
void resetGridRow(char grid[23]);
void resetGrid(char grid[23][10]);

void initNcurses();
void mov(char grid[23][10]);
void refreshGrid(char grid[23][10]);

void rotate(const int change);
void rotateRight();
void shiftLeft();
void shiftRight();

extern atomic<bool> run;
extern mutex grid_mutex;
extern atomic<int> curBlock[4][10];


// I Blocks

static int I_blockDef[4][10] = {
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int I_blockVert1[4][10] = {
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0}
};

static int I_blockHori[4][10] = {
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,1,1,1,1,0,0,0}
};

static int I_blockVert2[4][10] = {
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,1,0,0,0,0,0,0}
};


// J Blocks

static int J_blockDef[4][10] = {
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int J_blockVert1[4][10] = {
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0}
};

static int J_blockHori[4][10] = {
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int J_blockVert2[4][10] = {
                            {0,0,0,0,0,1,0,0,0,0},
                            {0,0,0,0,0,1,0,0,0,0},
                            {0,0,0,0,0,1,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0}
};


// L Blocks

static int L_blockDef[4][10] = {
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int L_blockVert1[4][10] = {
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0}
};

static int L_blockHori[4][10] = {
                            {0,0,0,1,1,1,1,0,0,0},
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int L_blockVert2[4][10] = {
                            {0,0,0,0,0,1,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,0,1,0,0,0}
};

// O Blocks

static int O_blockDef[4][10] = {
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};


// S Blocks

static int S_blockDef[4][10] = {
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,1,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int S_blockVert[4][10] = {
                            {0,0,0,1,0,0,0,0,0,0},
                            {0,0,0,1,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

// T Blocks

static int T_blockDef[4][10] = {
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,1,1,1,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int T_blockVert1[4][10] = {
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int T_blockHori[4][10] = {
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,1,1,1,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int T_blockVert2[4][10] = {
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,1,1,0,0,0,0,0},
                            {0,0,0,0,1,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

// Z Blocks

static int Z_blockDef[4][10] = {
                            {0,0,0,0,1,1,0,0,0,0},
                            {0,0,0,0,0,1,1,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};

static int Z_blockVert[4][10] = {
                            {0,0,0,0,0,0,1,0,0,0},
                            {0,0,0,0,0,1,1,0,0,0},
                            {0,0,0,0,0,1,0,0,0,0},
                            {0,0,0,0,0,0,0,0,0,0}
};




//static int (*allBlocks[7])[4][10] = {&I_blockDef,&J_blockDef,&L_blockDef,&O_blockDef,&S_blockDef,&T_blockDef,&Z_blockDef};


static int (*IBlocks[4])[4][10] = {&I_blockDef,&I_blockVert1,&I_blockHori,&I_blockVert2};
static int (*JBlocks[4])[4][10] = {&J_blockDef,&J_blockVert1,&J_blockHori,&J_blockVert2};
static int (*LBlocks[4])[4][10] = {&L_blockDef,&L_blockVert1,&L_blockHori,&L_blockVert2};
static int (*OBlocks[1])[4][10] = {&O_blockDef};
static int (*SBlocks[2])[4][10] = {&S_blockDef,&S_blockVert};
static int (*TBlocks[4])[4][10] = {&T_blockDef,&T_blockVert1,&T_blockHori,&T_blockVert2};
static int (*ZBlocks[2])[4][10] = {&Z_blockDef,&Z_blockVert};

static vector<vector<int (*)[4][10]>> allBlocks = {
    {IBlocks[0],IBlocks[1],IBlocks[2],IBlocks[3]}, // Pattern 0: I Blocks
    {JBlocks[0],JBlocks[1],JBlocks[2],JBlocks[3]}, // Pattern 1: J Blocks
    {LBlocks[0],LBlocks[1],LBlocks[2],LBlocks[3]}, // Pattern 2: L Blocks
    {OBlocks[0]},                                  // Pattern 3: O Blocks
    {SBlocks[0],SBlocks[1]},                       // Pattern 4: S Blocks
    {TBlocks[0],TBlocks[1],TBlocks[2],TBlocks[3]}, // Pattern 5: T Blocks
    {ZBlocks[0],ZBlocks[1]}                        // Pattern 6: Z Blocks
};



//extern atomic<int> nextBlock
//extern atomic<int> curBlock

#endif

                    
