#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <cstring>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

// Forward Declarations
void MainMenu();
void DisplayLeaderBoard();
void DisplayHelp();

void AuthMenu();
void LoginForm();
void SignupForm();
void AfterLoginMenu();
void HackMenu();

void LevelMenu();
void Play();

// Code
#include "util/display.cpp"
#include "util/menu.cpp"
#include "util/auth.cpp"
#include "util/play.cpp"