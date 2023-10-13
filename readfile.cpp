#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;


vector<vector<string>> read_data() {
    SetConsoleOutputCP(CP_UTF8);// для minGW
    //setlocale(LC_ALL, "Rus"); // для Visual Studio

    // Укажите путь к вашему файлу .txt
    std::string file_path = "input.txt";

    // Создайте вектор для хранения строк
    std::vector<std::vector<std::string>> arriving_ships_database;

    // Откройте файл для чтения
    std::ifstream file(file_path);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<std::string> elements;
            std::istringstream line_stream(line);
            std::string element;
            while (line_stream >> element) {
                elements.push_back(element);
            }
            arriving_ships_database.push_back(elements);
        }

        file.close();

        // Теперь у вас есть вектор, в котором каждый элемент представляет собой вектор строк
        return arriving_ships_database;
    } else {
        std::cerr << "Не удалось открыть файл." << std::endl;
        // Возвращаем пустой вектор в случае ошибки
        std::vector<std::vector<std::string>> arriving_ship_database;

        return arriving_ship_database;
    }
}

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


