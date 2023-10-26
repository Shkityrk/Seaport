//
// Created by shkit on 26.10.2023.
//

#pragma once


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

#include "./globals.h"
#include "Ship.h"


struct Ship_in_queue {
    int arrivalTime;
    int unloadingTime;
    string name;
    int time_in_queue;
    int start_unloading;
};