//
// Created by shkit on 26.10.2023.
//

#include "vizualization_modelling_ships.h"
#include "Ship_in_queue.h"
#include "generator.h"
#include "write_file.h"



void vizualization_modelling_ships(int num_ports, vector<Ship>& data){
    int numPorts= num_ports;// Количество портов
    int totalPenalty = 0; //Суммарный штраф
    int numShips=data.size(); // Количество кораблей
    vector<Ship_in_queue> ships(numShips);//Корабли в очереди

    for (int i = 0; i < numShips; ++i) {
        ships[i].arrivalTime=data[i].real_arrivalTime;//Время прибытия с учетом задержек
        ships[i].unloadingTime=data[i].actualDuration;//Время разгрузки с учетом задержки
        ships[i].name=data[i].name; //имя корабля
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
            int cout_penalty=time_penalty;//суммарный штраф равен штрафу за опред время
            //Количество кораблей, стоящих в очереди на разгрузку
            int kol_penalty_on_port=cout_penalty/numPorts;
            //Для итоговой статистки
            global_len_queue+=1;
            global_count_queue+=kol_penalty_on_port;
            cout<<"---------------------------- День "<<time/24+1<< " время "<< time%24<<" ----------------------------"<<endl;
            for (int p=1; p<=numPorts; p++){ // порты
                int queue_time=ports[p-1]-time;//Машинное время(индекс массивов) в единицу времени для каждого порта
                cout<<p<<" ";//номер порта
                //Если порт свободен, в очередь ничего не записываем, если порт занят - выводим время очереди порта
                if(queue_time>=0){
                    cout<<queue_time<<" ";//до которого часа порт будет занят
                } else{
                    cout<<0<<" ";
                }

                /**
                 * Обозначаем знаком "=" каждый корабль, стоящий в очереди в понкретный порт. Введя kol_penalty_on_port раз знак "=" вычитыаем из общего количества кранов в очереди.
                 * Таким образом, выводим всю очередь из кораблей
                 */
                if(time_penalty>0){
                    if(cout_penalty>=kol_penalty_on_port){
                        for(int sign_penalty=0; sign_penalty<kol_penalty_on_port;sign_penalty++){
                            cout<<" = ";
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
    all_penny+=totalPenalty;//Добавление штрафа в общую сумму штрафов
    cout<<"Визуализация завершена."<<endl;
    cout << "Выберите тип корабля:" << endl << "1 - Сухогрузы" << endl << "2 - Контейнеры" << endl << "3 - Жидкости"
         << endl;
    cout<<"Или введите другой символ для выхода из программы"<<endl;
}
