//
// Created by shkit on 26.10.2023.
//

#include "write_file.h"
#include "Ship_in_queue.h"


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