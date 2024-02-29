#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Cell{
public:
    bool isMine;
    bool isFlagged;
    bool isOpen;
    int minesAround;
    int xCoord;
    int yCoord;
    vector<Cell*> adjacentCells;

    //functions//
    Cell(int _xCoord, int _yCoord){
        xCoord = _xCoord;
        yCoord = _yCoord;
        minesAround = 0;
        isMine = false;
        isOpen = false;
        isFlagged = false;
    }

    //reset cell// -> individual cell
    void resetCell(){
        isMine = false;
        isFlagged = false;
        isOpen = false;
        minesAround = 0;
    }


    void printCoords(){
        cout << "(" << xCoord << ", " << yCoord << ")" << endl;
    }

    
};