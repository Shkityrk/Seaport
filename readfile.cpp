#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

#include "./globals.h"
#include "Ship.h"

using namespace std;


//Чтение данных из файла и создание вектора
vector<Ship> readShipsFromFile(const string& file_path){
//    int count_lines=length_file(file_path);
    ifstream file("input.txt");//open file
    vector<Ship> arriving_ships_database;

    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << file_path << std::endl;
        return arriving_ships_database;
    }
    //создаем динамический массив с типом данных Ships

    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string n, type;
        int weight, duration, date, time, pen;

        if (ss >> date >> time>> n >> type >> weight >> duration ) {
            arriving_ships_database.emplace_back(date, time, n, type, weight, duration );
        } else {
            cerr << "Ошибка чтения строки: " << line << endl;
        }
    }

    file.close();
    return arriving_ships_database;
}


//vector<vector<string>> read_data() {
//    SetConsoleOutputCP(CP_UTF8);// для minGW
//    //setlocale(LC_ALL, "Rus"); // для Visual Studio
//
//    // Укажите путь к вашему файлу .txt
//    std::string file_path = "input.txt";
//
//    // Создайте вектор для хранения строк
//    std::vector<std::vector<std::string>> arriving_ships_database;
//
//    // Откройте файл для чтения
//    std::ifstream file(file_path);
//
//    if (file.is_open()) {
//        std::string line;
//        while (std::getline(file, line)) {
//            std::vector<std::string> elements;
//            std::istringstream line_stream(line);
//            std::string element;
//            while (line_stream >> element) {
//                elements.push_back(element);
//            }
//            arriving_ships_database.push_back(elements);
//        }
//
//        file.close();
//
//        // Теперь у вас есть вектор, в котором каждый элемент представляет собой вектор строк
//        return arriving_ships_database;
//    } else {
//        std::cerr << "Не удалось открыть файл." << std::endl;
//        // Возвращаем пустой вектор в случае ошибки
//        std::vector<std::vector<std::string>> arriving_ship_database;
//
//        return arriving_ship_database;
//    }
//}
//
//int test() {
//    // Вызываем функцию и сохраняем возвращенный вектор
//    std::vector<std::vector<std::string>> data = read_data();
//
//    // Теперь вы можете использовать вектор данных в вашей программе
//    for (const std::vector<std::string>& row : data) {
//        for (const std::string& element : row) {
//            std::cout << element << " ";
//        }
//        std::cout << std::endl;
//    }
//
//    return 0;
//}


