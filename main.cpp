#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>

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
    int arrivalDate; // Время прибытия в днях после начала
    int arrivalTime; // Время прибытия в днях после начала

    int real_arrivalTime; // Время прибытия в часах после начала с учетом опоздания или досрочного прибытия





    Ship(int ship_arrivalDate, int ship_arrivalTime, string ship_n,string ship_cargoType, int ship_cargoWeight, int ship_plannedDuration) {//конструктор
        name = ship_n;
        cargoType = ship_cargoType;
        cargoWeight = ship_cargoWeight;
        plannedDuration = ship_plannedDuration;
         //обработка в функции
        arrivalDate = ship_arrivalDate;
        arrivalTime=ship_arrivalTime;

//        actualDuration=plannedDuration;
//        real_arrivalTime = arrivalDate*24 + arrivalTime;



        // Инициализация генератора случайных чисел

        srand(static_cast<unsigned int>(time(0)));

        // Генерация случайного значения для actualDuration (реальная продолжительность разгрузки)
        actualDuration = plannedDuration +12; //12 ЗАМЕНИТЬ НА РАНДОМ

        //увеличение продолжительности из-за веса
        if (cargoWeight>=5000){//при большом весе длительность разгрузки увеличивается
            actualDuration = actualDuration+ (cargoWeight/1000);
        }

        //увеличение продолжительности из-за погоды
        if(random(0,2)==1){// если ветренно, длительность увеличивается
            actualDuration +=cargoWeight%60;
        }
        else if (random(0,2)==2){// если идет дождь, длительность увеличивается
            actualDuration = actualDuration + (cargoWeight%100);
        }
        //ВОЛНЫ

        //увеличение продолжительности из-за типа
        if (cargoType=="Сыпучий"){
            actualDuration =actualDuration+ (actualDuration%10);
        }
        else if (cargoType=="Жидкий"){
            actualDuration =actualDuration+ (actualDuration%25);
        }
        else if(cargoType=="Контейнер"){
            actualDuration =actualDuration+ (actualDuration%15);
        }

        //Задержка окончания разгрузки судна(?), см п. 8 ТЗ
        actualDuration += random(0, 12*24);


        // Генерация реального отклонения от расписания
        int start = -2; // Нижняя граница
        int end = 9; // Верхняя граница
        int random_number=random(start, end) ;
        real_arrivalTime = arrivalDate*24 + arrivalTime + random_number;

    }

    int random(int low, int high)
    {
        return low + rand() % (high - low + 1);
    }

};


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

        if (ss >> date >> time>> n >> type >> weight >> duration ) {
            arriving_ships_database.emplace_back(date, time, n, type, weight, duration );
        } else {
            cerr << "Ошибка чтения строки: " << line << endl;
        }
    }

        file.close();
    return arriving_ships_database;
}

//Изменение данных в файле
// Определение класса для разгрузочных кранов
// Метод для начала разгрузки судна
// Метод для завершения разгрузки судна
// Оптимизация количества кранов
// Перераспределение кранов между разными типами груза
// Определение класса для модели морского порта

struct Ship_in_queue {
    int arrivalTime;
    int unloadingTime;
};

bool compareByArrivalTime(const Ship_in_queue& a, const Ship_in_queue& b) {
    return a.arrivalTime < b.arrivalTime;
}

//Моделирование очереди работы num_ports портов для данных из data. Порты и корабли только для одного ТИПА
int modelling_ships(int num_ports, vector<Ship>& data){
    /*
     * Массив количества портов типа. В начальный момент времени все порты свободны, т.е освободятся в 0.
     * Поэтому их начальное значение=0
     * Если корабль прибыл, то в ячейку записываем время, когда порт ОСВОБОДИТСЯ, т.е закончит разгрузку последнего корабля
     *
     * Проходим циклом по часам и проверяем - свободен ли хотя бы один порт? Если да - загоняем корабль в порт.
     * Далее удаляем из вектора - он нам больше не нужен.
     *
     */
    int numPorts= num_ports;// Количество портов
    int totalPenalty = 0;
    int numShips=data.size(); // Количество кораблей
    vector<Ship_in_queue> ships(numShips);

    for (int i = 0; i < numShips; ++i) {
        ships[i].arrivalTime=data[i].real_arrivalTime;
        ships[i].unloadingTime=data[i].actualDuration;
    }
    // отсортировать массив!
    sort(ships.begin(), ships.end(), compareByArrivalTime);

    vector<int> ports(numPorts, 0);


    for(int time=0; time<100; time++){//время
        for(int korabl=0; korabl<numShips; korabl++){
            for (int port=0; port<numPorts; port++ ){
                if ((ships[korabl].unloadingTime!=0)){
                    if ((time>=ports[port])&&(time>=ships[korabl].arrivalTime)){
                        ports[port]=ships[korabl].unloadingTime+time;
                        ships[korabl].unloadingTime=0;//зануляем
                        break;
                        ///????????
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

vector<int> calculate_queue(int max_num_cranes, vector<Ship> database_arrival_ships){
    vector<int> queue(2);
    vector<int> sum_cranes_min_penny(max_num_cranes, 0);

    int num_cranes_min_penny;//количество кранов типа при котором сумма штрафов минимальная
    int min_penny=INT_MAX;
    int penny;


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



int main() {
    SetConsoleOutputCP(CP_UTF8);
    unsigned int start_time =  clock();
    string path="input.txt";
    // Создание экземпляров судов - будут подтягиваться из файлика

    vector<Ship> database_arrival_ships= readShipsFromFile("input.txt");// получаем данные из файла
    //создаем пустые вектора под каждый тип груза
    vector<Ship> particulate_Ships;
    vector<Ship> liquid_Ships;
    vector<Ship> container_Ships;


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


    unsigned int n=0;// время в генерации

    int max_num_cranes=6;//максимальное кол-во кранов одного вида




    //Далее ищем минимальную сумму штрафа и количество портов при этом


    vector<int> best_model_particulate;
    vector<int> best_model_container;
    vector<int> best_model_liquid;
    best_model_particulate= calculate_queue(max_num_cranes, particulate_Ships);
    best_model_container= calculate_queue(max_num_cranes, container_Ships);
    best_model_liquid= calculate_queue(max_num_cranes, liquid_Ships);

    cout<<best_model_particulate[0]<<" "<<best_model_particulate[1]<<endl;
    cout<<best_model_liquid[0]<<endl;
    cout<<best_model_container[0]<<endl;

//    //Сухогруз
//    int num_cranes_min_penny_particulate=0;//количество кранов типа СУХОГРУЗ при котором сумма штрафов минимальная
//    int sum_cranes_min_penny_particulate=1000000000;// сумма штрафа
//
//    for(int num_particulate_crane=0; num_particulate_crane<=max_num_cranes;num_particulate_crane++) {//кол-во сыпучих кранов
//        int penny= modelling_ships(num_particulate_crane, database_arrival_ships);
//        if (penny<sum_cranes_min_penny_particulate){
//            num_cranes_min_penny_particulate=num_particulate_crane;
//            sum_cranes_min_penny_particulate=penny;
//        }
//    }
//    //КОНТЕЙНЕР
//    int num_cranes_min_penny_container=0;//количество кранов типа СУХОГРУЗ при котором сумма штрафов минимальная
//    int sum_cranes_min_penny_container=1000000000;// сумма штрафа
//
//    for(int num_container_crane=0; num_container_crane<=max_num_cranes;num_container_crane++) {//кол-во сыпучих кранов
//        int penny= modelling_ships(num_container_crane, database_arrival_ships);
//        if (penny<sum_cranes_min_penny_container){
//            num_cranes_min_penny_container=num_container_crane;
//            sum_cranes_min_penny_container=penny;
//        }
//    }
//
//
//    //Жидкость
//    int num_cranes_min_penny_liquid=0;//количество кранов типа СУХОГРУЗ при котором сумма штрафов минимальная
//    int sum_cranes_min_penny_liquid=1000000000;// сумма штрафа
//
//    for(int num_liquid_crane=0; num_liquid_crane<=max_num_cranes;num_liquid_crane++) {//кол-во сыпучих кранов
//        int penny= modelling_ships(num_liquid_crane, database_arrival_ships);
//        if (penny<sum_cranes_min_penny_liquid){
//            num_cranes_min_penny_liquid=num_liquid_crane;
//            sum_cranes_min_penny_liquid=penny;
//        }
//    }
//
//    cout<<num_cranes_min_penny_particulate<<endl;
//    cout<<num_cranes_min_penny_container<<endl;
//    cout<<num_cranes_min_penny_liquid<<endl;



//                //создаем три вектора, длиной max_num_cranes
//                vector<int> queue_particulate_crane(max_num_cranes, 0);//очередь
//                vector<int> queue_containers_crane(max_num_cranes, 0);
//                vector<int> queue_liquid_crane(max_num_cranes, 0);
//                for (int time=0; time<=24*30; time++){
//                    n++;
//                }
















    //подсчет времени выполнения программы
//    unsigned int end_time = clock();
//    unsigned int search_time = end_time - start_time;
//    cout<<search_time/1000<<endl;
//    cout<<n<<endl;

    // Добавление судов в порт

    // Дальнейшая симуляция порта и работа с моделью порта.


    // Добавление кранов в модель порта

    // Запуск симуляции


    // Оптимизация

    // Визуализация (при необходимости)


    return 0;
}