#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <random>

#include "readfile.cpp"


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
    int arrivalDate; // Время прибытия в часах после начала





    Ship(string ship_n, string ship_cargoType, int ship_cargoWeight, int ship_plannedDuration, int ship_arrivalDate) {//конструктор
        name = ship_n;
        cargoType = ship_cargoType;
        cargoWeight = ship_cargoWeight;
        plannedDuration = ship_plannedDuration;
         //обработка в функции
        arrivalDate = ship_arrivalDate;
        // Инициализация генератора случайных чисел
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<int> dist(0, plannedDuration);

        // Генерация случайного значения для actualDuration
        actualDuration = dist(rng);

    }
    // Дополнительные методы для работы с суднами

    // Метод для расчета и установки времени начала разгрузки

    // Метод для расчета и установки времени окончания разгрузки


    // Метод для расчета и установки штрафа за дополнительное время стоянки

};

//Определение количества строк в файле
//int length_file(const string& file_path){
//    int numLines = 0; //количество строк
//    ifstream in(file_path); // путь к файлу
//    string unused;
//    while (getline(in, unused) ){//до тех пор, пока есть строка
//        ++numLines;
//    }
//
//    return numLines;
//}


vector<Ship> readShipsFromFile(const string& file_path){//чтение данных из файла и создание вектора
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

        if (ss >> n >> type >> weight >> duration >> date >> time >> pen) {
            arriving_ships_database.emplace_back(n, type, weight, duration, date);
        } else {
            cerr << "Ошибка чтения строки: " << line << endl;
        }
    }

        file.close();
    return arriving_ships_database;
}

//Изменение данных в файле
vector<Ship> ships_database(){
    string path="input.txt";
    vector<Ship>arriving_ships_database= readShipsFromFile(path);



}



// Определение класса для разгрузочных кранов



    // Метод для начала разгрузки судна

    // Метод для завершения разгрузки судна

    // Оптимизация количества кранов

    // Перераспределение кранов между разными типами груза


// Определение класса для модели морского порта



int main() {
    unsigned int start_time =  clock();
    string path="input.txt";


    // Создание экземпляров судов - будут подтягиваться из файлика



    // Создание экземпляров кранов ?

    unsigned int n=0;

    int max_num_cranes=100;//максимальное кол-во портов

    for(int num_particulate_crane=0; num_particulate_crane<=max_num_cranes;num_particulate_crane++){//кол-во сыпучих кранов

        for (int num_containers_crane=0;num_containers_crane<=max_num_cranes;num_containers_crane++){

            for (int num_liquid_crane=0;num_liquid_crane<=max_num_cranes;num_liquid_crane++){
                //задали перебор числа контейнеров каждого вида

                //создаем три вектора, длиной max_num_cranes
                vector<int> queue_particulate_crane(max_num_cranes, 0);
                vector<int> queue_containers_crane(max_num_cranes, 0);
                vector<int> queue_liquid_crane(max_num_cranes, 0);

                for (int time=0; time<=24*30; time++){
                    n++;






                }




            }


        }


    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    cout<<search_time/1000<<endl;
    cout<<n<<endl;

    // Добавление судов в порт

    // Дальнейшая симуляция порта и работа с моделью порта.


    // Добавление кранов в модель порта

    // Запуск симуляции


    // Оптимизация

    // Визуализация (при необходимости)


    return 0;
}