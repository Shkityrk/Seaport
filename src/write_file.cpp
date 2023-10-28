//
// Created by shkit on 26.10.2023.
//

#include "../include/write_file.h"
#include "../include/Ship_in_queue.h"


void write_elem_in_output(Ship_in_queue & data, int time){
    ofstream outFile("data/statics.txt", ios::app);//Когда установлен ios::app, все операции вывода выполняются в конце файла, т.е не удаляются предыдущие элементы

    //Обработка ошибки
    if (!outFile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        return;
    }

    string name=data.name;//Имя
    int arT = data.arrivalTime;//Время прибытия
    int TinQ=data.time_in_queue; //Сколько стоит в очереди
    int UT=data.unloadingTime;//Времчя разгрузки
    int real_time=data.start_unloading;//Не используется; расчет произвдится внутри
    outFile<<"* "<<name<<" "<<arT<<" "<<TinQ<<" "<<time<<" "<<UT<<endl;//Строковая запись в файл строки
    //Итоговые вычисления в глобальных переменных
    global_sum_time_queue+=TinQ;
    global_len_time_queue+=1;

    outFile.close();// После использования необъодимо закрыть файл
}