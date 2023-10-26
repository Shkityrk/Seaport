#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "./globals.h"
#include "Ship.h"
#include "./generator.h"
#include "./readfile.h"
#include "./Ship_in_queue.h"
#include "./write_file.h"
#include "./modelling.h"
#include "./vizualization.h"
using namespace std;


void vizualization_particulate(vector<Ship>& data, vector<int> model_particulate){
//    queue[0]=num_cranes_min_penny;
//    queue[1]=min_penny;
    int num_cranes_min_penny=model_particulate[0];
    //запись шапки
    std::ofstream outFile("statics.txt", std::ios::app);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    // Здесь вы можете записать элемент в файл, который будет добавлен к существующему содержимому
    outFile<<"=======================Выбраны Сухогрузы======================="<<endl;
    outFile.close();

    vizualization_modelling_ships(num_cranes_min_penny, data);
}

void vizualization_container(vector<Ship>& data, vector<int> model_container){
    int num_cranes_min_penny=model_container[0];
    //запись шапки
    std::ofstream outFile("statics.txt", std::ios::app);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    // Здесь вы можете записать элемент в файл, который будет добавлен к существующему содержимому
    outFile<<"=======================Выбраны Контейнеры======================="<<endl;
    outFile.close();

    vizualization_modelling_ships(num_cranes_min_penny, data);
}

void vizualization_liquid(vector<Ship>& data, vector<int> model_liquid){
    int num_cranes_min_penny=model_liquid[0];
    //запись шапки
    std::ofstream outFile("statics.txt", std::ios::app);
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    // Здесь вы можете записать элемент в файл, который будет добавлен к существующему содержимому
    outFile<<"=======================Выбраны Жидкости======================="<<endl;
    outFile.close();

    vizualization_modelling_ships(num_cranes_min_penny, data);
}


void visualization(vector<vector<Ship>>& data, const vector<vector<int>>& best_models){
    cout<<"Запуск визуализации"<<endl;
    /*
     * Сухогрузы
     * ---------------------1 день------------------------
     * номер осталось_времени очередь
     * 1 1д 15ч ===============
     * 2 2ч     ========
     * 3
     * 4
     * 5
     * 6
     * 7
     * ----------------------------------------------------
     * Далее 3 день(enter), выход(/away)
     * _
     */
    vector<Ship> viz_particulate_Ships=data[0];
    vector<Ship> viz_container_Ships=data[1];
    vector<Ship> viz_liquid_Ships=data[2];

    const vector<int>& best_model_particulate=best_models[0];
    const vector<int>& best_model_container=best_models[1];
    const vector<int>& best_model_liquid=best_models[2];

    int var;
    cout << "Выберите тип корабля:" << endl << "1 - Сухогрузы" << endl << "2 - Контейнеры" << endl << "3 - Жидкости"
         << endl;
    cout<<"Или введите другой символ для выхода из программы"<<endl;
    cin>>var;
    //цикл
    while((var==1)||(var==2)||(var==3)) {
        if (var == 1) {
            //Сухогрузы
            vizualization_particulate(viz_particulate_Ships, best_model_particulate);
        } else if (var == 2) {
            //Контейнеры
            vizualization_container(viz_container_Ships, best_model_container);
        } else if (var == 3) {
            //Жидкости
            vizualization_liquid(viz_liquid_Ships, best_model_liquid);
        } else {
            return;
        }
        cin>>var;
    }
}
/*итоговая статистика
 *
*/

//количество разгруженных кораблей
int num_corabl(){
    std::ifstream inputFile("statics.txt"); // Замените "input.txt" на имя вашего файла
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

//вывод статистики
int final_statistics(){
    std::ofstream outFile("statics.txt", std::ios::app);
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
    SetConsoleOutputCP(CP_UTF8);

    //для проверки производительности - таймер выполнения программы
    unsigned int start_time =  clock();
    unsigned int n=0;// время в генерации


    cout<<"Генерация файла"<<endl;
    generator();
    cout<<"Файл сгенерирован"<<endl;

    // Создание экземпляров судов - будут подтягиваться из сгенерированного файлика
    vector<Ship> database_arrival_ships= readShipsFromFile("input.txt");// получаем данные из файла
    //создаем пустые вектора под каждый тип груза
    vector<Ship> particulate_Ships;
    vector<Ship> liquid_Ships;
    vector<Ship> container_Ships;

    //оформляем файл, пишем пояснение
    std::ofstream ofs;
    ofs.open("statics.txt", std::ofstream::out | std::ofstream::trunc);
    ofs<<"Список произведенных разгрузок"<<endl;
    ofs<<"Вид данных в файле: <Название корабля> <Время прихода в порт в часах, начиная от начала отсчета> <Время ожидания в очереди на разгрузку> <Продолжительность разгрузки>";
    ofs<<"Каждый столбец дня пронумерован - это номер порта, затем время, когда порт освободится от разгружаемого корабля"<<endl;
    ofs<<"Символ = означает корабль в очереди на разгрузку в данный порт"<<endl;
    ofs.close();

    //сортировка по типу груза
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
    int max_num_cranes=10;//максимальное кол-во кранов одного вида

    //Далее ищем минимальную сумму штрафа и количество портов при этом
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