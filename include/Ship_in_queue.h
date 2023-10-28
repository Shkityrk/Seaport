//
// Created by shkit on 26.10.2023.
//

#pragma once


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

#include "globals.h"
#include "Ship.h"

/**
 * Структура, для создаения очереди из кораблей, пришедших в порты
 * @param arrivalTime время прибытия в порт, в часах
 * @param unloadingTime время разгрузки, в часах
 * @param name имя корабля
 * @param time_in_queue текущее время корабля простаивания в очереди
 * @param start_unloading начало времени разгрузки
 */
struct Ship_in_queue {
    int arrivalTime;
    int unloadingTime;
    string name;
    int time_in_queue;
    int start_unloading;
};