//
// Created by shkit on 26.10.2023.
//

#pragma once
#include "Ship.h"

int modelling_ships(int num_ports, vector<Ship>& data);

//Вычисление очереди при наличии количества кранов и вектора из прибывших кораблей
vector<int> calculate_queue(int max_num_cranes, vector<Ship> database_arrival_ships);