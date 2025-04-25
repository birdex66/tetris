#include "setup.hpp"

int main(){

    char grid[20][10];

    for(int i=0; i<20; ++i){
        for(int j=0; j<10; ++j){
            grid[i][j] = ' ';
        }
    }

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
    for(int k=0; k<10; ++k) curBlock[k].store(init[k]);

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




