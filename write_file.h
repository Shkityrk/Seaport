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
 * Запись элемента в файл без удаления предыдущего содержимого элемента
 * @param data Вектор данных о кораблях в очереди
 * @param time Время в часах, для которого записываются данные
 */
void write_elem_in_output(Ship_in_queue & data, int time);