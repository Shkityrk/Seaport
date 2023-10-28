//
// Created by shkit on 26.10.2023.
//


/**
 * 3 функции имеют одинаковые функции, которые различаются лишь выводом информации о типе груза
 */
#pragma once
#include "Ship.h"



void vizualization_particulate(vector<Ship>& data, vector<int> model_particulate);

void vizualization_container(vector<Ship>& data, vector<int> model_container);

void vizualization_liquid(vector<Ship>& data, vector<int> model_liquid);

