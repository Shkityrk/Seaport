//
// Created by shkit on 26.10.2023.
//
#pragma once


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "./globals.h"
#include "Ship.h"
#include "Ship_in_queue.h"

/**
 * @brief Генерация числа в диапазоне [min; max]
 * @param min минимальное число, которое может быть сгенерировано
 * @param max максимальное число, которое может быть сгенерировано
 */
int randomInRange(int min, int max);

/**
 * @brief Генерация случайной строки
 * @details Генерируем случайную строку, представляющую из себя набор заглавных и строчных латинских букв. Так мы присваиваем кораблю имя
 * @param length Длина названия корабля
 * @return
 */
string generateRandomString(int length);

/**
 * @brief Генератор
 * @details Запуск генерации названий корабля и запись данных в файл
 * @return Если выполнено верно, возвращает 0
 */
int generator();

/**
 * @brief Сравнение прибытий корабля
 * @param a время прибытия первого корабля
 * @param b время прибытия второго корабля
 * @return Вовращение правды или лжи
 */
bool compareByArrivalTime(const Ship_in_queue & a, const Ship_in_queue & b) ;