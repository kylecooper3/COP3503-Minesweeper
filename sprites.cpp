#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "cell.cpp"
#include "board.cpp"

using namespace std;

class Mine{
public:
    sf::Sprite mine;
    bool draw = false;
    int coordX;
    int coordY;
    Mine(sf::Sprite _mine, int _coordX, int _coordY){
        mine = _mine;
        coordX = _coordX;
        coordY = _coordY;
    };
    void reposition(){
        mine.setPosition(coordX, coordY);
    }

};

class Flag{
public:
    sf::Sprite flag;
    bool draw = false;
    int coordX;
    int coordY;
    Flag(sf::Sprite _flag, int _coordX, int _coordY){
        flag = _flag;
        coordX = _coordX;
        coordY = _coordY;
    };
    void reposition(){
        flag.setPosition(coordX, coordY);
    }
};

class TileRevealed{
public:
    sf::Sprite tileRevealed;
    bool draw = false;
    int coordX;
    int coordY;
    TileRevealed(sf::Sprite _tileRevealed, int _coordX, int _coordY){
        tileRevealed = _tileRevealed;
        coordX = _coordX;
        coordY = _coordY;
    };
    void reposition(){
        tileRevealed.setPosition(coordX, coordY);
    }
};

class NumberTile{
public:
    sf::Sprite numberTile;
    bool draw = false;
    int coordX;
    int coordY;
    int num;
    NumberTile(sf::Sprite _numberTile, int _coordX, int _coordY, int _num){
        numberTile = _numberTile;
        coordX = _coordX;
        coordY = _coordY;
        num = _num;
    }
    void reposition(){
        numberTile.setPosition(coordX, coordY);
    }
};

class Counter{
public:
    sf::Sprite counterNumber;
    int coordX;
    int coordY;
    Counter(sf::Sprite _counterNumber, int _coordX, int _coordY){
        counterNumber = _counterNumber;
        coordX = _coordX;
        coordY = _coordY;
    }
    void reposition(){
        counterNumber.setPosition(coordX, coordY);
    }
};