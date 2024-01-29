#pragma once

#include "SFML/Audio.hpp"
#include <SFML/Graphics.hpp>  
#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <fstream>
#include<string>
#include <string.h>
#include <chrono>
#include <mutex>
#include <filesystem>
#include <thread>
#include <map>
#include <memory>


enum KEYS {
	KEY_UP = 72,
	KEY_DOWN = 80,
	KEY_LEFT = 75,
	KEY_RIGHT = 77
};

using namespace std;

enum Color {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};






HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);