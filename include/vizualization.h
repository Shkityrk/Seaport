//
// Created by shkit on 26.10.2023.
//

#pragma once
#include "Ship.h"

/**
 * Визуализация очереди для вывода в консоль, в зависимости от типа корабля
 * Включает в себя выбор типа кораблей, вывод шапки типа груза, запуск функции вывода очереди соответсвующего типа кораблей
 * @param data Отсортированный набор данных
 * @param best_models лучшая из моделей, при которой число портов и сумма штрафов @b МИНИМАЛЬНЫ
 */
void visualization(vector<vector<Ship>>& data, const vector<vector<int>>& best_models);