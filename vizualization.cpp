//
// Created by shkit on 26.10.2023.
//

#include "vizualization.h"
#include "vizualization_types.h"


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