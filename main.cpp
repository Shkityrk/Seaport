#include <iostream>  // Библиотека для ввода и вывода данных. Позволяет работать с потоками ввода и вывода, такими как cin и cout.
#include <vector>  // Библиотека, предоставляющая контейнер std::vector для хранения и управления динамическими массивами данных.
#include <cstdlib>  // Библиотека, содержащая функции для управления памятью, выполнения операций с псевдослучайными числами и другими стандартными функциями.
#include <ctime>  // Библиотека, предоставляющая функции для работы со временем и датами, такие как time(), которая часто используется для генерации случайных чисел на основе времени.
#include <algorithm>  // Библиотека, содержащая различные алгоритмы обработки и сортировки структур данных, такие как std::sort() и std::find().
#include <fstream>  // Библиотека для работы с файлами. Позволяет открывать, читать и записывать данные в файлы.
#include <string>  // Библиотека, предоставляющая структуры данных и функции для работы со строками, такие как std::string.
#include <sstream>  // Библиотека, предоставляющая классы и функции для работы с потоками строк, что полезно при преобразовании данных между строками и другими типами данных.
#include <windows.h>  // Библиотека для операций, специфичных для операционной системы Windows. Здесь она, вероятно, используется для управления окнами и процессами в Windows-среде.


#include "include/globals.h"
#include "include/Ship.h"
#include "include/generator.h"
#include "include/readfile.h"
#include "include/modelling.h"
#include "include/vizualization.h"
using namespace std;

/*
 *итоговая статистика
*/

//количество разгруженных кораблей
int num_corabl(){
    std::ifstream inputFile("data/statics.txt"); // Замените "input.txt" на имя вашего файла
    if (!inputFile.is_open()) {
        std::cerr << "Не удалось открыть файл." << std::endl;
        return 1;
    }

    int asteriskCount=0; // Счетчик звездочек
        std::string line;

    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            // Проверяем первый символ в строке
            if (line[0] == '*') {
                asteriskCount++;
            }
        }
    }
    inputFile.close();
    return asteriskCount;
};

//средняя длина очереди
double average_len_queue(){
    return (double) global_count_queue/global_len_queue;
}

//среднее время ожидания
double average_time_queue(){
    return (double) global_sum_time_queue/global_len_time_queue;
}

// макс задержка разгрузки = max_duration

// средняя задержка разгрузки
double average_duration(){
    return sum_duration/len_duration;
}

//общая сумма штрафа (по условию)
int absolut_penny(){
    return all_penny*2;
}

//вывод статистики с использованием глобальных переменных
int final_statistics(){
    std::ofstream outFile("data/statics.txt", std::ios::app);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 0;
    }

    outFile<<"=======================Итоговая статистика======================="<<endl;
    outFile<<"Число разгруженных судов: "<<num_corabl()<<endl;
    outFile<<"Средняя длина очереди на разгрузку: "<<average_len_queue()<<endl;
    outFile<<"Среднее время ожидания в очереди: "<<average_time_queue()<<endl;
    outFile<<"Максимальная задержка разгрузки: "<<max_duration<<endl;
    outFile<<"Средняя задержка разгрузки: "<<average_duration()<<endl;
    outFile<<"Общая сумма выплаченного штрафа: "<<absolut_penny()<<endl;
    outFile.close();
    cout<<"Статистика записана в файл statics.txt"<<endl;

    return 0;
}

int main() {
    //setlocale(LC_ALL, "Russian");//для работы в Visual Studio
    SetConsoleOutputCP(CP_UTF8);// в иных случаях

    //для проверки производительности - таймер выполнения программы, впоследствии не используется, однако можно запустить, добавив библиотеку в начало кода
//    unsigned int start_time =  clock();
//    unsigned int n=0;// время в генерации


    cout<<"Генерация файла"<<endl;
    generator();
    cout<<"Файл сгенерирован"<<endl;

    // Создание экземпляров судов - данный будут подтягиваться из сгенерированного файлика
    vector<Ship> database_arrival_ships= readShipsFromFile("data/input.txt");// получаем данные из файла

    //Создание пустых векторов под каждый тип груза - для сортировки
    vector<Ship> particulate_Ships;
    vector<Ship> liquid_Ships;
    vector<Ship> container_Ships;

    //оформление итогового файла, пояснение
    ofstream ofs;// При повторном открытии текст не стирается, а дописывается. Работа по принципу log
    ofs.open("data/statics.txt", ofstream::out | ofstream::trunc);
    ofs<<"Список произведенных разгрузок"<<endl;
    ofs<<"Вид данных в файле: <Название корабля> <Время прихода в порт в часах, начиная от начала отсчета> <Время ожидания в очереди на разгрузку> <Продолжительность разгрузки>";
    ofs<<"Каждый столбец дня пронумерован - это номер порта, затем время, когда порт освободится от разгружаемого корабля"<<endl;
    ofs<<"Символ = означает корабль в очереди на разгрузку в данный порт"<<endl;
    ofs.close();

    //сортировка по типу груза - каждый корабль проверяется, какому типу он принадлежит. В случае ошибки - выводится предупреждение, программа завершает работу
    for (const Ship& ship : database_arrival_ships) {
        if (ship.cargoType == "Сухогруз") {
            particulate_Ships.push_back(ship);
        } else if (ship.cargoType == "Жидкий") {
            liquid_Ships.push_back(ship);
        } else if (ship.cargoType == "Контейнер") {
            container_Ships.push_back(ship);
        } else{
            cout<<"Не все строки обработаны, проверьте тип необходимого порта"<<endl;
            return 0;
        }
    }
    vector<vector<Ship>> sorted_Ships={particulate_Ships, container_Ships, liquid_Ships};//для визуализации, набор сортированных векторов
    int max_num_cranes;//максимальное кол-во кранов одного вида(можно менять, однако чем больше значение, тем меньше быстродействие програмы
    cout<<"Введите максимальное число портов: "<<endl;
    cin>>max_num_cranes;
    //Поиск минимальной суммы штрафа и количество портов при этом

    vector<int> best_model_particulate;
    vector<int> best_model_container;
    vector<int> best_model_liquid;
    best_model_particulate= calculate_queue(max_num_cranes, particulate_Ships);
    best_model_container= calculate_queue(max_num_cranes, container_Ships);
    best_model_liquid= calculate_queue(max_num_cranes, liquid_Ships);

//    тестовые параметры num_cranes_min_penny min_penny
//    cout<<best_model_particulate[0]<<" "<<best_model_particulate[1]<<endl;
//    cout<<best_model_liquid[0]<<" "<<best_model_liquid[1]<<endl;
//    cout<<best_model_container[0]<<" "<<best_model_container[1]<<endl;

    vector<vector<int>> best_models={best_model_particulate, best_model_container, best_model_liquid};

    visualization(sorted_Ships, best_models);

    //итоговая статистика
    final_statistics();

    //все
    return 0;
}