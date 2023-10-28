//
// Created by shkit on 26.10.2023.
//

#include "Ship.h"

// конструктор cppreference

Ship::Ship(int ship_arrivalDate, int ship_arrivalTime, string ship_n, string ship_cargoType, int ship_cargoWeight,
           int ship_plannedDuration): name(ship_n), cargoType(ship_cargoType), cargoWeight (ship_cargoWeight),
                                      plannedDuration (ship_plannedDuration){//list constructor

    //обработка в функции
    arrivalDate = ship_arrivalDate;
    arrivalTime=ship_arrivalTime;
//      actualDuration=plannedDuration;
//      real_arrivalTime = arrivalDate*24 + arrivalTime;

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // Генерация случайного значения для actualDuration (реальная продолжительность разгрузки)
    actualDuration = plannedDuration + random(0,12);

    //увеличение продолжительности разгрузки из-за веса
    if (cargoWeight>=5000){//при большом весе длительность разгрузки увеличивается(от 0 до 1000)
        actualDuration = actualDuration+ (cargoWeight/1000);
    }

    //увеличение продолжительности из-за погоды
    if(random(0,2)==1){// если ветренно, длительность увеличивается(от 0 до 60)
        actualDuration +=cargoWeight%60;
    }
    else if (random(0,2)==2){// если идет дождь, длительность увеличивается(от 0 до 60
        actualDuration = actualDuration + (cargoWeight%100);
    }

    //увеличение продолжительности разгрузки  из-за типа
    if (cargoType=="Сыпучий"){
        actualDuration =actualDuration+ (actualDuration%10);
    }
    else if (cargoType=="Жидкий"){
        actualDuration =actualDuration+ (actualDuration%25);
    }
    else if(cargoType=="Контейнер"){
        actualDuration =actualDuration+ (actualDuration%15);
    }

    //Задержка окончания разгрузки судна, см п. 8 ТЗ
    actualDuration += random(0, 12*24);

    //Генерация реального отклонения от расписания
    int start = -2; // Нижняя граница
    int end = 9; // Верхняя граница
    int random_number=random(start, end) ;//использование функции генерации числа в диапазоне
    real_arrivalTime = arrivalDate*24 + arrivalTime + random_number;

    //Вычисления для итоговой статистки
    if(max_duration<(abs(actualDuration-plannedDuration))){
        max_duration=abs(actualDuration-plannedDuration);
    }
    sum_duration+=actualDuration;
    len_duration+=1;
}

int Ship::random(int low, int high) {
    return low + rand() % (high - low + 1);//Импорт функции генерации числа в заданном диапазоне
}
