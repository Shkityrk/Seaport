#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

#include "../include/globals.h"
#include "../include/Ship.h"

using namespace std;


vector<Ship> readShipsFromFile(const string& file_path){
//    int count_lines=length_file(file_path);//для тестов, в стабильной версии программы не используется ввиду ненужности

    vector<Ship> arriving_ships_database; //Объявление вектора, содержащего данные обо всех кораблях из входного файла
    ifstream file("data/input.txt");//Попытка открытия файла

    /**
     * Обработка исключения открытия файла
     */
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла: " << file_path << std::endl;
        return arriving_ships_database;
    }

    //Заполнение динамического массива с типом данных Ships

    string line;//Каждая строка в файле, необходимо для построчного чтения файла; изменяется в ходе цикла while
    while (getline(file, line)) {
        istringstream ss(line);//реализует операции ввода для потоков на основе строк. Он эффективно хранит экземпляр std ::basic_string и выполняет операции ввода над ним.

        //Объявление переменных для записи данных из строки в файл
        string n, type;
        int weight, duration, date, time, pen;

        //Если в ss имеется достаточное количество данных, разделенных пробелом - добавляем метод в вектор
        if (ss >> date >> time>> n >> type >> weight >> duration )
        // порядок выгрузки данных <день время имя_корабля тип_корабля вес_грузов_корабля время_разгрузки>
        {
            arriving_ships_database.emplace_back(date, time, n, type, weight, duration );
        } else {
            cerr << "Ошибка чтения строки: " << line << endl;//Обработка ошибки
        }
    }

    file.close();//Закрытие файла
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


