#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "cell.cpp"

using namespace std;

class Board{
public:
    int width = 0;
    int height = 0;
    int numMines = 0;
    vector<Cell> cells;
    vector<int> minePlacement;
    
    //functions//
    
    // Returns false if the config is missing, unreadable, or has values the game can't use.
    bool readCFG(){
        ifstream infile("files/board_config.cfg");
        if(!(infile >> width >> height >> numMines)){
            return false;
        }
        // The mine counter shows three digits, and at least one tile must be mine-free.
        long long totalCells = static_cast<long long>(width) * height;
        return width > 0 && height > 0 && numMines > 0 && numMines <= 999 && numMines < totalCells;
    }

    void fillBoard(){
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                Cell currentCell(x, y);
                cells.push_back(currentCell);
            }
        }
    }

    Cell* getCell(int xCoord, int yCoord){
        int listIndex = (yCoord * width) + xCoord;
        return &cells.at(listIndex);
    }

    void addMines(int _numMines) {
        int minesPlaced = 0;
        while(minesPlaced < _numMines){
            int randNum = rand() % cells.size();
            if(count(minePlacement.begin(), minePlacement.end(), randNum) == 0){
                minePlacement.push_back(randNum);
                cells.at(randNum).isMine = true;
                minesPlaced++;
            }
        }
    }

    int countMinesAroundCell(int xCoord, int yCoord) {
        int minesAround = 0;
        int index = yCoord * width + xCoord;
        if(!cells[index].isMine) {
            // Check all neighboring cells (including diagonals)
            for (int y = yCoord - 1; y <= yCoord + 1; y++) {
                for (int x = xCoord - 1; x <= xCoord + 1; x++) {
                    // Skip cells that are outside the board or are the current cell
                    if (x < 0 || x >= width || y < 0 || y >= height || (x == xCoord && y == yCoord)) {
                        continue;
                    }

                    int neighborIndex = y * width + x;
                    if (cells[neighborIndex].isMine) {
                        minesAround++;
                    }
                }
            }
        }
        return minesAround;
    }
    void resetBoard(){
        for(int i = 0; i < cells.size(); i++){
            cells.at(i).resetCell();
        }
        minePlacement.clear();
    }



    void getSurroundingCells(int xCoord, int yCoord) {
        vector<Cell *> neighbors;
        Cell* currentCell = getCell(xCoord, yCoord);
        // Check all neighboring cells (including diagonals)
        for (int y = yCoord - 1; y <= yCoord + 1; y++) {
            for (int x = xCoord - 1; x <= xCoord + 1; x++) {
                // Skip cells that are outside the board or are the current cell
                if (x < 0 || x >= width || y < 0 || y >= height || (x == xCoord && y == yCoord)) {
                    continue;
                }
                int neighborIndex = y * width + x;
                Cell* currentNeighbor = &cells.at(neighborIndex);
                neighbors.push_back(currentNeighbor);
            }
        }
        currentCell->adjacentCells = neighbors;
    }


};

