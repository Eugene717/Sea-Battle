#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <random>

const int ROW = 10;
const int COL = 10;
const char EMPTY = '\0';       //�����
const char DEAD = 'X';         //�����
const char ALIVE = '\1';       //����� �������
const char ENEMY_ALIVE = ' ';  //����� ������� ����������, ��� �� �� �� ����������� �� �����
const char MISS = '*';         //������

static std::random_device RD;

#endif // !CONSTANTS_H

