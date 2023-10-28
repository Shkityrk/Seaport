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
 * @brief Чтение данных из файла и создание динамического массива, в котором сохраняется вся информация о корабле из файла
 * @param file_path путь исходного файла
 * @return Вектор методов класса Ship, содержит информацию о каждом корабле, который, согласно расписания, прибудет в
 */
vector<Ship> readShipsFromFile(const string& file_path);

/**
 * @b НЕИСПОЛЬЗУЕТСЯ Неоптимальный и неотлаженный вариант, не используется в проекте.
 * Чтение данных, используется для теста системы
 * @return
 */
[[maybe_unused]] vector<vector<string>> read_data();

/**
 * @b НЕИСПОЛЬЗУЕТСЯ Тестирование функции readShipsFromFile, не использовать в стаблиной версии проекта
 * @return
 */
[[maybe_unused]] int test();