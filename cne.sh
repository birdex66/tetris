#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "One argument expected"
    if [ "$#" -lt 2 ]; then
        echo "Specify a compilation type!!"
        echo "Default Type:                        0"
        echo "Mid-Speed Type (Safer defaults):     1"
        echo "Maximum Speed Type:                  2"
    fi
    exit 1
fi

> err

if [ "$1" == 0 ]; then
    g++ src/tetris.cpp src/functions.cpp -o dev -lncurses &&
    rm -f bin/dev ;
    mv dev bin/ &&
    gnome-terminal --wait -- bash -c './bin/dev; echo $? > err'
    echo "Ran: ./bin/dev"
elif [ "$1" == 1 ]; then
    g++ -O1 src/tetris.cpp src/functions.cpp -o stable -lncurses &&
    rm -f bin/stable ;
    mv stable bin/ && 
    gnome-terminal --wait -- bash -c './bin/stable; echo $? > err'
    echo "Ran: ./bin/stable"
elif [ "$1" == 2 ]; then
    g++ -O3 src/tetris.cpp src/functions.cpp -o perf -lncurses &&
    rm -f bin/perf ;
    mv perf bin/ &&
    gnome-terminal --wait -- bash -c './bin/perf; echo $? > err'
    echo "Ran: ./bin/perf"
else
    echo "Wrong compilation type"
    exit 2
fi

if [ "$(cat err | tr -d '\n')" = "139" ]; then
    echo "Segmentation Fault (core dumped)"
    exit 3
fi


exit 0
