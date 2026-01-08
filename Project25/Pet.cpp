#include "Pet.h"
#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

Pet::Pet(std::string n, std::string t, std::string g, int s, int e, int lv, int aff, int ac, std::string lastTime, std::string playTime)
    : name(n), type(t), gender(g), satiety(s), energy(e), level(lv), affection(aff), actionCount(ac), lastAccessTime(lastTime), lastPlayTime(playTime) {
}

Pet::~Pet() {}

void Pet::checkLevelUp() {
    int oldLevel = level;

    if (actionCount >= 1000) level = 5;
    else if (actionCount >= 100) level = 4;
    else if (actionCount >= 10) level = 3;
    else if (actionCount >= 5) level = 2;

    if (level > oldLevel) {
        std::cout << "\n>>>축하합니다! 레벨이 " << level << "로 올랐습니다!" << std::endl;
        wait(1500);
    }
}

void Pet::printStatus() {
    cout << "\n==================================================" << endl;
    cout << " [" << type << "] " << name << " (" << gender << "/Lv." << level << ")" << endl;
    cout << " 상태 | 포만감: " << satiety << "/100 | 에너지: " << energy
        << "/100 | 애정도: " << affection << "/100" << endl;
    cout << "==================================================" << endl;
}

bool Pet::passTime() {
    return (satiety > 0 && energy > 0);
}

void Pet::updateStatusByTime(double timeUnits) {
    int affDrop = calculateAffectionDrop(timeUnits);
    affection = max(0, affection - affDrop);

    int satDrop = ((int)timeUnits) * 5;
    satiety = max(0, satiety - satDrop);
}

string Pet::getSaveData() {
    return type + " " + name + " " + gender + " "
        + to_string(satiety) + " "
        + to_string(energy) + " "
        + to_string(level) + " "
        + to_string(affection) + " "
        + to_string(actionCount) + " " 
        + lastAccessTime + " " + lastPlayTime;
}

void Pet::setSatiety(int s) { satiety = max(0, min(100, s)); }
void Pet::setEnergy(int e) { energy = max(0, min(100, e)); }
void Pet::setAffection(int a) { affection = max(0, min(100, a)); }

void Pet::updateLastAccessTime() { lastAccessTime = getCurrentTimeStr(); }
void Pet::updateLastPlayTime() { lastPlayTime = getCurrentTimeStr(); }