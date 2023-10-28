//
// Created by shkit on 26.10.2023.
//

#pragma once
#include "Ship.h"

/**
 * @brief Моделирование работы порта в зависимости от количества портов и количества кораблей, приходящих в них
 * @param num_ports Количество портов
 * @param data Вектор методов класса Ship, в каждом элементе хранятся необходимые данные о каждом корабле
 * @param return Возвращает сумму штрафов всех кораблей за все время
 */
int modelling_ships(int num_ports, vector<Ship>& data);

/**
 * @brief Вычисление очереди при наличии количества кранов и вектора из прибывших кораблей
 * @param max_num_cranes Максимальное количество портов
 * @param database_arrival_ships Вектор методов класса Ship, представляет собой набор данных о каждом корабле, данные берутся из расписания в файле input.txt
 * @return Возвращает Вектор queue = [количество портов, при котором сумма штрафа за время будет минимальной][минимальная сумма штрафа, при количестве портов , указанном в queue[0]]
 */
vector<int> calculate_queue(int max_num_cranes, vector<Ship> database_arrival_ships);