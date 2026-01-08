#include "Utils.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <sstream>
#include <iomanip>

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void wait(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

std::string getCurrentTimeStr() {
    time_t now = time(0);
    struct tm tstruct;
#ifdef _WIN32
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return std::string(buf);
}

time_t stringToTime(std::string dateTimeStr) {
    struct tm tm = {};
    std::istringstream ss(dateTimeStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return mktime(&tm);
}

double getTimeDiff30Sec(std::string lastTimeStr) {
    time_t last = stringToTime(lastTimeStr);
    time_t now = time(0);
    double seconds = difftime(now, last);
    return seconds / 30.0; 
}