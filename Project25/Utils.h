#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>

enum State { IDLE, EATING, SLEEPING, PLAYING };

void clearScreen();
void wait(int milliseconds);

std::string getCurrentTimeStr();
time_t stringToTime(std::string dateTimeStr);
double getTimeDiff30Sec(std::string lastTimeStr);

#endif