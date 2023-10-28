//
// Created by shkit on 26.10.2023.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "globals.h"

#pragma once

using namespace std;

// Определение класса для судов
/**
 * @param name имя корабля
 * @param cargoType тип груза
 * @param cargoWeight вес груза
 * @param plannedDuration планируемая продолжительность разгрузки, ч
 * @param actualDuration реальная продолжительность разгрузки, ч
 * @param arrivalDate Дата прибытия
 * @param waitingTime Время ожидания в очереди
 * @param startUnloadingTime Время начала разгрузки
 * @param finishUnloadingTime Время окончания разгрузки
 * @param penalty Штраф за дополнительное время стоянки
 */
class Ship {
public:
    string name;//имя корабля
    string cargoType; //тип груза
    int cargoWeight; //вес груза
    int plannedDuration; // планируемая продолжительность разгрузки, ч
    int actualDuration; // реальная продолжительность разгрузки, ч
    int arrivalDate; // Время прибытия в днях после начала
    int arrivalTime; // Время прибытия в днях после начала
    int real_arrivalTime; // Время прибытия в часах после начала с учетом опоздания или досрочного прибытия

    Ship(int ship_arrivalDate, int ship_arrivalTime, string ship_n,string ship_cargoType, int ship_cargoWeight, int ship_plannedDuration);
    //Генерация цисла в промежутке от до
    static int random(int low, int high);

};
