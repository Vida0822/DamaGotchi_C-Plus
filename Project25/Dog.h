#ifndef DOG_H
#define DOG_H
#include "Pet.h"

class Dog : public Pet {
public:
    Dog(std::string n, std::string g, int s, int e, int lv, int aff, int ac, std::string lastTime, std::string playTime);

    void draw(int state) override;
    void eat() override;
    void sleep() override;
    void play() override;

    int calculateAffectionDrop(double timeUnits) override;
};
#endif