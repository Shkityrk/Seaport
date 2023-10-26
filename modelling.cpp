//
// Created by shkit on 26.10.2023.
//

#include "modelling.h"
#include "generator.h"
#include "Ship_in_queue.h"

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