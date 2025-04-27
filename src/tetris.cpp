#include "setup.hpp"

int main(){

    char grid[24][10];

    for(int i=0; i<24; ++i){
        for(int j=0; j<10; ++j){
            grid[i][j] = ' ';
        }
    }
srand(time(0));
standby:
    run.store(true);
    resetGrid(grid);
    
    initNcurses();
    clear();
    int swit = rand()%(6-0+1)+0;
    printw("Ready? (press any key) : Pattern %i",swit);
    refresh();
    getch();
    
    nodelay(stdscr, TRUE);
    timeout(100);
    //halfdelay(1);

    //int swit = rand()%(6-0+1)+0; 
    initalizePattern(swit);  
    //for(int k=0; k<10; ++k) curBlock[k].store(init[k]);

    thread worker(drop,grid);
    thread listen(mov,grid);
    worker.join();
    listen.join();

    //cout << "\nbye bye\n";
    nodelay(stdscr, FALSE);
    printw("Replay? (y/n)");
    refresh();
    char inp = getch();
    if(inp != 'n') goto standby;
    endwin();
    return 0;
}




