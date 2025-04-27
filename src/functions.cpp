#include "setup.hpp"

atomic<int> curBlock[4][10];
atomic<bool> run(true);
atomic<bool> paus(false);

mutex grid_mutex;
static int stp;
static int indL;
static int indR;

static int curRow;
static int curCol;

void initNcurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);
}

void initalizePattern(int patternIndex){
    if(patternIndex == 0) stp = 21;
    else stp = 20;

    indL = 100;
    indR = -100;

    for(int i=0; i<4; ++i){
        for(int j=0; j<10; ++j){
            int fer = (*allBlocks[patternIndex])[i][j];
            curBlock[i][j].store(fer);//(*allBlocks[patternIndex])[i][j]);
            if(fer == 1 && j < indL) indL = j;
            if(fer  == 1 && j > indR) indR = j;
        }
    }
}

void drop(char grid[23][10]){
    while(run.load()){
        bool backout = false;
        curRow = 0;
        for(int i=0; i<20; ++i){
            while(paus.load()){
                this_thread::sleep_for(chrono::milliseconds(200));
                paus.store(false);
            }
            unique_lock<mutex> lock(grid_mutex);
            for(int j=0; j<4; ++j){
                for(int k=0,curCol=0; k<10; ++k,++curCol){
                    if(i+j <= stp ){
                        if(curBlock[j][k].load()>0) grid[i+j][k] = 'X'; 
                        else grid[i+j][k] = ' '; 
                    }else{
                        backout = true;
                        break;
                    }
                }
                if(backout) break;
            }
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(800));
            if(backout) break;
            if(i!=19) resetGrid(grid[i]);
            ++curRow;
        }
        run.store(false);
        this_thread::sleep_for(chrono::milliseconds(1500));
    }
}

void resetGrid(char grid[]){
    for(int j=0; j<10; ++j){
        grid[j] = ' ';
    }
}

void printGrid(const char grid[20][10]){
    clear();
    //string quickGrid = "";
    for(int i=0; i<20; ++i){

        //quickGrid += '|';
        mvaddch(i,0,'|');
        for(int j=0; j<10; ++j) /*quickGrid += grid[i][j];*/mvaddch(i,j+1,grid[i][j]);//.append(to_string(grid[i][j]));
                                                                                      //quickGrid += "|\n";   //.append("\n");
        mvaddch(i,11,'|');
    }
    mvprintw(20,0,"============");
    //quickGrid += "============";
    //printw("%s",quickGrid.c_str());
    refresh();
}

void refreshGrid(char grid[23][10]){
    lock_guard<mutex> lock(grid_mutex);
    int len = curRow + 1;
    for(int i=curRow; i<len; ++i){
        for(int j=0; j<4; ++j){
            for(int k=0; k<10; ++k){
                if(i+j <= stp){
                    if(curBlock[j][k].load()>0) grid[i+j][k] = 'X'; 
                    else grid[i+j][k] = ' '; 
                }
            }
        } 
        // resetGrid(grid[i]);
    }
}

void mov(char grid[23][10]){
    while(run.load()){
        char input = getch();
        if(input != ERR){
            paus.store(true);
            if(input == 'a' && indL > 0) shiftLeft(grid);
            else if(input == 'd' && indR < 9) shiftRight(grid);
            refreshGrid(grid);
        }
        printGrid(grid);
        //this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void shiftLeft(const char grid[23][10]){
    for(int i=0; i<4; ++i){
        for(int j=0; j<9; ++j){
            curBlock[i][j].store(curBlock[i][j+1].load()); 
        }
        curBlock[i][9].store(0);
    }
    --indL;
    --indR;
}

void shiftRight(const char grid[23][10]){
    for(int i=0; i<4; ++i){
        for(int j=9; j>0; --j){
            curBlock[i][j].store(curBlock[i][j-1].load()); 
        }
        curBlock[i][0].store(0);
    }
    ++indL;
    ++indR;
}

