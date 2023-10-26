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

using namespace std;



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

struct Ship_in_queue {
    int arrivalTime;
    int unloadingTime;
    string name;
    int time_in_queue;
    int start_unloading;
};

bool compareByArrivalTime(const Ship_in_queue& a, const Ship_in_queue& b) {
    return a.arrivalTime < b.arrivalTime;
}

void write_elem_in_output(Ship_in_queue & data, int time){

    std::ofstream outFile("statics.txt", std::ios::app);

    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }
    string name=data.name;
    int arT = data.arrivalTime;
    int TinQ=data.time_in_queue; // сколько стоит в очереди
    int UT=data.unloadingTime;
    int real_time=data.start_unloading;
    outFile<<"* "<<name<<" "<<arT<<" "<<TinQ<<" "<<time<<" "<<UT<<endl;
    global_sum_time_queue+=TinQ;
    global_len_time_queue+=1;

    outFile.close();
}


int modelling_ships(int num_ports, vector<Ship>& data){
    int numPorts= num_ports;// Количество портов
    int totalPenalty = 0;
    int numShips=data.size(); // Количество кораблей
    vector<Ship_in_queue> ships(numShips);
    for (int i = 0; i < numShips; ++i) {
        ships[i].arrivalTime=data[i].real_arrivalTime;// время прибытия
        ships[i].unloadingTime=data[i].actualDuration; // продолжительность разгрузки
        ships[i].name=data[i].name; //имя
    }
    // отсортировать массив!
    sort(ships.begin(), ships.end(), compareByArrivalTime);

    vector<int> ports(numPorts, 0);

    for(int time=0; time<24*30; time++){//время
        for(int korabl=0; korabl<numShips; korabl++){
            for (int port=0; port<numPorts; port++ ){
                if ((ships[korabl].unloadingTime!=0)){
                    if ((time>=ports[port])&&(time>=ships[korabl].arrivalTime)){
                        ports[port]=ships[korabl].unloadingTime+time;
                        ships[korabl].unloadingTime=0;//зануляем элемент, который разгрузился/разгружается и больше его не учитываем
                        break;
                    }
                }
            }
        }
        for(int Queue_ships=0; Queue_ships<numShips; Queue_ships++){
            if((ships[Queue_ships].arrivalTime<=time)&&(ships[Queue_ships].unloadingTime!=0)){
                totalPenalty+=1;
            }
        }
    };
    return totalPenalty;
}

//Вычисление очереди при наличии количества кранов и вектора из прибывших кораблей
vector<int> calculate_queue(int max_num_cranes, vector<Ship> database_arrival_ships){
    vector<int> queue(2);
    vector<int> sum_cranes_min_penny(max_num_cranes, 0);

    int num_cranes_min_penny;//количество кранов типа при котором сумма штрафов минимальная
    int min_penny=INT_MAX;//максимум
    int penny;//штраф

    for(int num_crane=1; num_crane<=max_num_cranes;++num_crane) {//кол-во сыпучих кранов
        penny=modelling_ships(num_crane, database_arrival_ships);
        if (penny<min_penny){
            min_penny=penny;
            num_cranes_min_penny=num_crane;
        }
    }
    queue[0]=num_cranes_min_penny;
    queue[1]=min_penny;
    return queue;
}

void vizualization_modelling_ships(int num_ports, vector<Ship>& data){
    /*
     * Массив количества портов типа. В начальный момент времени все порты свободны, т.е освободятся в 0.
     * Поэтому их начальное значение=0
     * Если корабль прибыл, то в ячейку записываем время, когда порт ОСВОБОДИТСЯ, т.е закончит разгрузку последнего корабль
     * Проходим циклом по часам и проверяем - свободен ли хотя бы один порт? Если да - загоняем корабль в порт.
     * Далее удаляем из вектора - он нам больше не нужен.
     */
    int numPorts= num_ports;// Количество портов
    int totalPenalty = 0;
    int numShips=data.size(); // Количество кораблей
    vector<Ship_in_queue> ships(numShips);

    for (int i = 0; i < numShips; ++i) {
        ships[i].arrivalTime=data[i].real_arrivalTime;
        ships[i].unloadingTime=data[i].actualDuration;
        ships[i].name=data[i].name; //имя
    }
    // отсортировать массив!
    sort(ships.begin(), ships.end(), compareByArrivalTime);

    vector<int> ports(numPorts, 0);
    vector<int> len_ports(numPorts, 0);// количество кораблей в очереди на каждый порт
    int time_penalty;//количество кораблей, стоящих во время time

    for(int time=0; time<24*30; time++){//время
        time_penalty=0;// обнуляем количество кораблей в очереди.
        for(int korabl=0; korabl<numShips; korabl++){
            for (int port=0; port<numPorts; port++ ){
                if ((ships[korabl].unloadingTime!=0)){
                    if ((time>=ports[port])&&(time>=ships[korabl].arrivalTime)){
                        ports[port]=ships[korabl].unloadingTime+time;// порт занят
                        //запись элемента в файл
                        if(ships[korabl].unloadingTime!=0) {
                            ships[korabl].start_unloading=time;
                            write_elem_in_output(ships[korabl], time);
                        }

                        ships[korabl].unloadingTime=0;//корабль разгружается/разгрузился
                        break;
                    }
                }
            }
        }
        for(int Queue_ships=0; Queue_ships<numShips; Queue_ships++){
            if((ships[Queue_ships].arrivalTime<=time)&&(ships[Queue_ships].unloadingTime!=0)){
                totalPenalty+=1;
                time_penalty+=1;
                ships[Queue_ships].time_in_queue+=1;
                num_korabl+=1;
            }
        }
        //если новый день - выводим статистику
        if(time%24==0){
            int cout_penalty=time_penalty;
            int kol_penalty_on_port=cout_penalty/numPorts;
            global_len_queue+=1;
            global_count_queue+=kol_penalty_on_port;
            cout<<"---------------------------- День "<<time/24+1<< " время "<< time%24<<" ----------------------------"<<endl;
            for (int p=1; p<=numPorts; p++){ // порты

                int queue_time=ports[p-1]-time;
                cout<<p<<" ";
                if(queue_time>=0){
                    cout<<queue_time<<" ";
                } else{
                    cout<<0<<" ";
                }

                if(time_penalty>0){
                    if(cout_penalty>=kol_penalty_on_port){
                        for(int sign_penalty=0; sign_penalty<kol_penalty_on_port;sign_penalty++){
                            cout<<" = ";
                            //-------------------------------------------------------------------------------------------------------------------------------
                        }
                        cout_penalty=cout_penalty-kol_penalty_on_port;
                    }else{
                        for(int sign_penalty=0; sign_penalty<(kol_penalty_on_port-cout_penalty);sign_penalty++){
                            cout<<" = ";
                        }
                    }
                }
                cout<<endl;
                // ввод числа с клавиатуры
            }
            cout<<"Day end"<<endl;
            cout<<"------------------------------------------------------------------------"<<endl;
            cout<<endl;
        }

    }
    all_penny+=totalPenalty;
    cout<<"Визуализация завершена."<<endl;
    cout << "Выберите тип корабля:" << endl << "1 - Сухогрузы" << endl << "2 - Контейнеры" << endl << "3 - Жидкости"
         << endl;
    cout<<"Или введите другой символ для выхода из программы"<<endl;
}

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