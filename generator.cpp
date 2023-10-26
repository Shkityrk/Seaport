//
// Created by shkit on 26.10.2023.
//

#include "generator.h"

//
// Created by shkit on 26.10.2023.
//
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



/*
 * Генерация файла
 */
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Генерация случайной строки
string generateRandomString(int length) {
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += alphabet[randomInRange(0, sizeof(alphabet) - 2)];

    }
    return randomString;
}

int generator() {
    int n;
    std::cout << "Введите количество строк (n): ";
    std::cin >> n;

    std::ofstream outFile("input.txt");
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return 1;
    }

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < n; ++i) {
        int day = randomInRange(1, 30);
        int hour = randomInRange(0, 23);
        std::string shipName = generateRandomString(10);  // Генерируем случайное имя корабля
        std::string shipType;
        int weight = randomInRange(1, 1000);  // Генерируем случайный вес в тоннах
        int unloadTime = randomInRange(1, 24);  // Генерируем время разгрузки в часах

        int arrivalTime = randomInRange(1, 719);  // Генерируем прибытие в пределах 30 дней
        int departureTime = arrivalTime + unloadTime;

        // Случайным образом выбираем тип корабля
        int typeChoice = randomInRange(1, 3);
        if (typeChoice == 1) {
            shipType = "Сухогруз";
        } else if (typeChoice == 2) {
            shipType = "Контейнер";
        } else {
            shipType = "Жидкий";
        }

        // Записываем данные в файл
        outFile << day << ' ' << hour << ' ' << shipName << ' ' << shipType << ' ' << weight << ' ' << arrivalTime << ' ' << departureTime << '\n';
    }

    outFile.close();
    std::cout << "Файл 'input.txt' успешно создан." << std::endl;
    return 0;
}

bool compareByArrivalTime(const Ship_in_queue & a, const Ship_in_queue & b) {
    return a.arrivalTime < b.arrivalTime;
}
