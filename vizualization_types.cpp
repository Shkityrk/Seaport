//
// Created by shkit on 26.10.2023.
//

#include "vizualization_types.h"
#include "vizualization_modelling_ships.h"


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

