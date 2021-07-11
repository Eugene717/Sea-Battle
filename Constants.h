#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <random>

const int ROW = 10;
const int COL = 10;
const char EMPTY = '\0';       //пусто
const char DEAD = 'X';         //помер
const char ALIVE = '\1';       //живой корабль
const char ENEMY_ALIVE = ' ';  //живой корабль противника, что бы он не отображался на карте
const char MISS = '*';         //промах

static std::random_device RD;

#endif // !CONSTANTS_H

