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

vector<Ship> readShipsFromFile(const string& file_path);

vector<vector<string>> read_data();

int test();