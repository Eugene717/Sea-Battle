#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int ROW = 10;
const int COL = 10;
const char EMPTY = '\0';       //пусто
const char DEAD = 'X';         //помер
const char ALIVE = '\1';       //живой корабль
const char ENEMY_ALIVE = ' ';  //живой корабль противника
const char MISS = '*';         //промах
const char SURVIVING_SHIP = 'S';
const int MIN_F_BOARD_X = 50;
const int MIN_S_BOARD_X = 450;
const int MIN_Y = 80;
const int SQUARE_SIDE_SIZE = 30;

#endif // !CONSTANTS_H

