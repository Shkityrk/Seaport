//
// Created by shkit on 26.10.2023.
//

#include "../include/modelling.h"
#include "../include/generator.h"
#include "../include/Ship_in_queue.h"

int modelling_ships(int num_ports, vector<Ship>& data){
    int numPorts= num_ports;// Количество портов
    int totalPenalty = 0;//
    int numShips=data.size(); // Количество кораблей
    vector<Ship_in_queue> ships(numShips);
    //Заполняем вектор информацией
    for (int i = 0; i < numShips; ++i) {
        ships[i].arrivalTime=data[i].real_arrivalTime;// время прибытия
        ships[i].unloadingTime=data[i].actualDuration; // продолжительность разгрузки
        ships[i].name=data[i].name; //имя
    }
    //Важно отсортировать массив!
    //Сортровку выполнить стандартными средствами С++, используя библиотеку algorittm.h
    sort(ships.begin(), ships.end(), compareByArrivalTime);

    vector<int> ports(numPorts, 0);

    for(int time=0; time<24*30; time++){//время
        for(int korabl=0; korabl<numShips; korabl++){//Каждый корабль
            for (int port=0; port<numPorts; port++ ){//Каждый порт
                /**
                 * Если время разгрузки корабля не равно 0(его не обработала программа) и текущее время цикла больше либо равно времени прибытия(т.е. корабль прибыл в порт либо в этот час, либо уже определенное время стоит в очереди на разгрузку - обрабатываем его
                 */
                if ((ships[korabl].unloadingTime!=0)){
                    if ((time>=ports[port])&&(time>=ships[korabl].arrivalTime)){
                        ports[port]=ships[korabl].unloadingTime+time;//Порт занят до времени текущее+ время разгрузки
                        ships[korabl].unloadingTime=0;//зануляем элемент, который разгрузился/разгружается и больше его не учитываем
                        break;
                    }
                }
            }
        }
        //Если кораблдь не обработан и до сих пор находится в очереди - уведличить штраф( в данном случае штраф не в у.е, а в количестве кораблей)
        for(int Queue_ships=0; Queue_ships<numShips; Queue_ships++){
            if((ships[Queue_ships].arrivalTime<=time)&&(ships[Queue_ships].unloadingTime!=0))//Если Время прибытия меньше настоящего времени и корабль не обратботан
            {
                totalPenalty+=1;//Увеличиваем счетчик на 1
            }
        }
    };
    return totalPenalty;//Возвращаем сумму штрафов всех кораблей за все время
}

vector<int> calculate_queue(int max_num_cranes, vector<Ship> database_arrival_ships){
    /**
     * Вектор очереди
     * @param queue[0] количество портов, при котором сумма штрафа за время будет минимальной
     * @param queue[1] минимальная сумма штрафа, при количестве портов , указанном в queue[0]
     */
    vector<int> queue(2);

    /**
     * Для каждого количества портов запоминает очередь кораблей и количество портов, при котором количество портов минимально, и сумма штрафа минимальна
     */
    vector<int> sum_cranes_min_penny(max_num_cranes, 0);

    int num_cranes_min_penny;//количество кранов типа при котором сумма штрафов минимальная
    int min_penny=INT_MAX;//максимум, используется для нахождения минимального штрафа
    int penny;//штраф

    for(int num_crane=1; num_crane<=max_num_cranes;++num_crane) {//кол-во портов
        penny=modelling_ships(num_crane, database_arrival_ships);//Расчет штрафов
        /**
         *  Поиск минимального штрафа
         */
        if (penny<min_penny){
            min_penny=penny;
            num_cranes_min_penny=num_crane;
        }
    }
    /**
     * Функция возращает количество портов, при котором сумма штрафа минимальна, и саму сумму штрафа
     */
    queue[0]=num_cranes_min_penny;
    queue[1]=min_penny;
    return queue;
}