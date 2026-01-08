#ifndef PET_H
#define PET_H

#include <string>
#include <iostream>
#include <algorithm>
#include "Utils.h"

class Pet {
protected:
    std::string name;
    std::string type;
    std::string gender;
    int satiety; 
    int energy;
    int level;
    int affection;

    int actionCount;

    std::string lastAccessTime; 
    std::string lastPlayTime; 

public:
    Pet(std::string n, std::string t, std::string g, int s, int e, int lv, int aff, int ac, std::string lastTime, std::string playTime);
    virtual ~Pet();

    virtual void draw(int state) = 0;
    virtual void play() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;

    virtual int calculateAffectionDrop(double timeUnits) = 0;
    void updateStatusByTime(double timeUnits);

    void checkLevelUp();

    void printStatus();
    bool passTime();

    std::string getSaveData(); 

    std::string getName() { return name; }
    std::string getType() const { return type; }
    std::string getGender() { return gender; }

    int getSatiety() { return satiety; }
    int getEnergy() { return energy; }
    int getLevel() { return level; }
    int getAffection() { return affection; }
    int getActionCount() { return actionCount; }

    std::string getLastAccessTime() { return lastAccessTime; }
    std::string getLastPlayTime() { return lastPlayTime; }

    void setSatiety(int s);
    void setEnergy(int e);
    void setAffection(int a);

    void updateLastAccessTime();
    void updateLastPlayTime();
};

#endif