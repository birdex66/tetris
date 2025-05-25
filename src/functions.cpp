#include "setup.hpp"

atomic<int> curBlock[4][10];
atomic<bool> run(true);
atomic<bool> paus(false);

mutex grid_mutex;
static int stp;
static int indL;
static int indR;
static vector<bPattern> blocks;
static bPattern* adminBlock;


static int curRow;
static int curCol;
static int rotateState = 0;
static int rotateLen;
static int patternNum;

void initNcurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    curs_set(0);
}

/*
void initalizePattern(int patternIndex){
    if(patternIndex == 0) stp = 21;
    else stp = 20;

    indL = 100;
    indR = -100;
    rotateLen = allBlocks[patternIndex].size(); 

    for(int i=0; i<4; ++i){
        for(int j=0; j<10; ++j){
            int fer = (*allBlocks[patternIndex][rotateState])[i][j];
            curBlock[i][j].store(fer);//(*allBlocks[patternIndex])[i][j]);
            if(fer == 1 && j < indL) indL = j;
            if(fer  == 1 && j > indR) indR = j;
        }
    }

    for(int k=0; k<3; ++k) shiftRight();
    patternNum = patternIndex;
}
*/

void initalizePattern(int patternIndex){
    rotateLen = allBlocks[patternIndex].size();
    //blocks.resize(rotateLen);
    if(patternIndex == 0) stp = 21;
    else stp = 20;

    for(int i=0; i<rotateLen; ++i){
        blocks.push_back(bPattern(allBlocks[patternIndex][i]));
    }

    adminBlock = &blocks[0];

    const int (*arr)[10] = adminBlock->getShape();
    for(int i=0; i<4; ++i){
        for(int j=0; j<10; ++j){
            curBlock[i][j].store(arr[i][j]);
        }
    }
    
    curCol = 3;
    shiftRight(3);
    indL = curCol;
    indR = curCol + (adminBlock->getIndR() - adminBlock->getIndL());
    patternNum = patternIndex;
    
}

void resetState(){blocks.clear();}


void drop(char grid[24][10]){
    while(run.load()){
        bool backout = false;
        curRow = 0;
        /* logic for locking in blocks

           while(paus.load()) this_thread::sleep_for(chrono::milliseconds(200));

           if(canDrop()){
           drop();
           ++curRow;
           }else{
           lock();
           }

        */

        for(int i=0; i<20; ++i){
            while(paus.load()) this_thread::sleep_for(chrono::milliseconds(200));
            unique_lock<mutex> lock(grid_mutex);
            int j=0;
            for(int j=0; j<4; ++j){
                for(int k=0; k<10; ++k){
                    if(i+j <= stp){
                        if(curBlock[j][k].load()>0) grid[i+j][k] = 'X'; 
                        else grid[i+j][k] = ' ';
                    }else{
                        backout = true;
                        break;
                    }
                }
                if(backout) break;
            }
            //adminBlock->dropBlock();
            lock.unlock();
            this_thread::sleep_for(chrono::milliseconds(800));
            if(backout) break;
            if(i+(adminBlock->getBottom()-adminBlock->getTop())<19) resetGridRow(grid[i]);
            else break;
            ++curRow;
        }
        run.store(false);
        this_thread::sleep_for(chrono::milliseconds(1500));
        resetGrid(grid);
    }
}

void resetGridRow(char grid[]){
    for(int j=0; j<10; ++j){
        grid[j] = ' ';
    }
}

void resetGrid(char grid[24][10]){
    for(int i=0; i<20; ++i){
        for(int j=0; j<10; ++j){
            grid[i][j] = ' ';
        }
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

void refreshGrid(char grid[24][10]){
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

void mov(char grid[24][10]){
    while(run.load()){
        char input = getch();
        if(input != ERR){
            paus.store(true);
            //lock_guard<mutex> lock(grid_mutex);
            //bool bound = indL > 0 && indR < 9;
            if(input == 'a' && indL > 0){
                shiftLeft(1);
                --curCol;
            }else if(input == 'd' && indR < 9){
                shiftRight(1);
                ++curCol;
            }else if(input == 's' && indR < 9) rotate(1);//&& canRotateLeft()) rotateLeft();
            else if(input == 'w' && indL > 0) rotate(-1);//&& canRotateRight()) rotateRight();
            refreshGrid(grid);
        }
        printGrid(grid);
        paus.store(false);

        //this_thread::sleep_for(chrono::milliseconds(50));
    }
}
/*
inline void rotate(const int change){
    rotateState += change;
    indL = 10;
    indR = -1;
    for(int i=0; i<4; ++i){
        for(int j=0; j<10; ++j){
            int fer = (*allBlocks[patternNum][abs(rotateState) % rotateLen])[i][j];
            curBlock[i][j].store(fer);
            if(fer == 1){
                if(j < indL) indL = j;
                if(j > indR) indR = j;
            }
        }
    }
}
*/
inline void rotate(const int change){
    rotateState += change;
    adminBlock = &blocks[abs(rotateState)%rotateLen];
    
    const int (*arr)[10] = adminBlock->getShape();
    int newIndL = adminBlock->getIndL();
    int newIndR = adminBlock->getIndR();

    for(int i=0; i<4; ++i){
        for(int j=0; j<10; ++j){
            curBlock[i][j].store(arr[i][j]);
        }
    }
    int shiftAmount = curCol - newIndL;
   
    if(shiftAmount + newIndR > 9) shiftAmount = 9 - newIndR;
    if(shiftAmount < 0) shiftAmount = 0;

    if(shiftAmount > 0) shiftRight(shiftAmount);
    else if(shiftAmount < 0) shiftLeft(-shiftAmount);

    indL = newIndL + shiftAmount;
    indR = newIndR + shiftAmount;
}

inline void shiftLeft(int change){
    for(int i=0; i<4; ++i){
        for(int j=0; j<10-change; ++j){
            curBlock[i][j].store(curBlock[i][j+change].load()); 
        }
        for(int k=10-change; k<10; ++k){
            curBlock[i][k].store(0); 
        }
    }
    indL -= change;
    indR -= change;
}

inline void shiftRight(int change){
    for(int i=0; i<4; ++i){
        for(int j=9; j>=change; --j){
            curBlock[i][j].store(curBlock[i][j-change].load()); 
        }
        for(int k=0; k<change; ++k){
            curBlock[i][k].store(0); 
        }
    }
    indL += change;
    indR += change;
}


/*
inline void shiftLeft(){
    for(int i=0; i<4; ++i){
        for(int j=0; j<9; ++j){
            curBlock[i][j].store(curBlock[i][j+1].load()); 
        }
        curBlock[i][9].store(0);
    }
    --indL;
    --indR;
}

inline void shiftRight(){
    for(int i=0; i<4; ++i){
        for(int j=9; j>0; --j){
            curBlock[i][j].store(curBlock[i][j-1].load()); 
        }
        curBlock[i][0].store(0);
    }
    ++indL;
    ++indR;
}
*/

