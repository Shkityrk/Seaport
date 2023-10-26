//
// Created by shkit on 26.10.2023.
//
#pragma once


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>

#include "./globals.h"
#include "Ship.h"
#include "Ship_in_queue.h"


int randomInRange(int min, int max);

string generateRandomString(int length);

int generator();
bool compareByArrivalTime(const Ship_in_queue & a, const Ship_in_queue & b) ;