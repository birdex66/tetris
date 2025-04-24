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
void printGrid(int grid[20][10]);
void drop(int grid[20][10]);
void resetGrid(int grid[20]);

void initNcurses();

void mov(int grid[20][10]);
void shiftLeft();
void shiftRight();

atomic<int> pattern[10];
atomic<bool> run(true);
mutex grid_mutex;


int main(){

    int grid[20][10] = {0};

standby:
    run.store(true);
    resetGrid(grid[19]);
    
    initNcurses();
    clear();
    
    printw("Ready? (press any key)");
    refresh();
    getch();
    
    nodelay(stdscr, TRUE);
    timeout(5);
    
    int init[10] = {0,0,0,1,1,1,1,0,0,0};
    for(int k=0; k<10; ++k) pattern[k].store(init[k]);

    thread worker(drop,grid);
    thread listen(mov,grid);
    worker.join();
    listen.join();

    //cout << "\nbye bye\n";
    nodelay(stdscr, FALSE);
    printw("Replay? (y/n)");
    refresh();
    char inp = getch();
    if(inp == 'y') goto standby;
    endwin();
    return 0;
}

void initNcurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);
}

void drop(int grid[20][10]){
    while(run.load()){
        for(int i=0; i<20; ++i){
            unique_lock<mutex> lock(grid_mutex);
            for(int j=0; j<10; ++j) if(pattern[j].load()>0) grid[i][j] = 1; 
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(800));
            if(i!=19) resetGrid(grid[i]);
        }
        run.store(false);
        this_thread::sleep_for(chrono::milliseconds(900));
    }
}

void resetGrid(int grid[]){
    for(int j=0; j<10; ++j){
        grid[j] = 0;
    }
}

void printGrid(int grid[20][10]){
    clear();
    string quickGrid = "";
    for(int i=0; i<20; ++i){
        for(int j=0; j<10; ++j) quickGrid.append(to_string(grid[i][j]));
        quickGrid.append("\n");
    }
    printw("%s",quickGrid.c_str());
    refresh();
}

static int index;

void mov(int grid[20][10]){
    index = 3;
    while(run.load()){
        char input = getch();
        if(input == 'a' && index > 0) shiftLeft();
        else if(input == 'd' && index < 6) shiftRight();
        printGrid(grid);
    }
}

void shiftLeft(){
    for(int i=0; i<9; ++i) pattern[i].store(pattern[i+1].load()); 
    pattern[9].store(0);
    --index;
}

void shiftRight(){
    for(int i=9; i>0; --i) pattern[i].store(pattern[i-1].load()); 
    pattern[0].store(0);
    ++index;
}




