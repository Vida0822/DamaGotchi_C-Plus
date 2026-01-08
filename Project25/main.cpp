#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Utils.h"
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"

using namespace std;

int myFood = 10;

void saveAllPets(const vector<Pet*>& pets) {
    ofstream outFile("savegame.txt");
    if (outFile.is_open()) {
        for (Pet* p : pets) {
            outFile << p->getSaveData() << endl;
        }
        outFile.close();
    }
}

vector<Pet*> loadAllPets() {
    vector<Pet*> pets;
    ifstream inFile("savegame.txt");
    if (!inFile.is_open()) return pets;

    string type, name, gender;
    int satiety, energy, level, affection, actionCount; 
    string date1, time1; 
    string date2, time2; 

    while (inFile >> type >> name >> gender >> satiety >> energy >> level >> affection >> actionCount >> date1 >> time1 >> date2 >> time2) {
        string accessTime = date1 + " " + time1;
        string playTime = date2 + " " + time2;

        if (type == "강아지") {
            pets.push_back(new Dog(name, gender, satiety, energy, level, affection, actionCount, accessTime, playTime));
        }
        else if (type == "고양이") {
            pets.push_back(new Cat(name, gender, satiety, energy, level, affection, actionCount, accessTime, playTime));
        }
    }
    return pets;
}

void createPet(vector<Pet*>& pets) {
    if (pets.size() >= 5) {
        cout << "\n>>> 펫은 최대 5마리까지만 키울 수 있습니다!" << endl;
        wait(1000);
        return;
    }
    clearScreen();
    cout << "=== 새로운 펫 입양 ===" << endl;
    cout << "1. 강아지  2. 고양이\n선택: ";
    int typeChoice; cin >> typeChoice;
    cout << "이름: "; string name; cin >> name;
    cout << "성별(남/여): "; string gender; cin >> gender;

    int startSatiety = 70;
    int startEnergy = 70;
    int startLevel = 1;
    int startAffection = rand() % 51;
    int startActionCount = 0; 
    string now = getCurrentTimeStr();

    Pet* newPet = nullptr;

    if (typeChoice == 1) newPet = new Dog(name, gender, startSatiety, startEnergy, startLevel, startAffection, startActionCount, now, now);
    else newPet = new Cat(name, gender, startSatiety, startEnergy, startLevel, startAffection, startActionCount, now, now);

    pets.push_back(newPet);
    saveAllPets(pets);
    cout << "\n>>> " << name << "이(가) 가족이 되었습니다!" << endl;
    wait(1000);
}

void playGame(Pet* myPet, vector<Pet*>& pets) {
    myPet->updateLastPlayTime();
    saveAllPets(pets);

    while (true) {
        clearScreen();
        myPet->printStatus();
        myPet->draw(IDLE);

        cout << "\n   [ 보유 먹이: " << myFood << "개 ]" << endl;
        cout << "1.먹이주기  2.재우기  3.놀아주기  4.저장하고 나가기" << endl;
        cout << "선택: ";
        int action; cin >> action;

        if (action == 4) {
            myPet->updateLastPlayTime();
            myPet->updateLastAccessTime();

            saveAllPets(pets);
            cout << "\n>>> 저장하고 메인으로 돌아갑니다." << endl;
            wait(1000);
            break;
        }

        switch (action) {
        case 1:
            if (myFood > 0) {
                myPet->eat();
                myFood--;
            }
            else {
                cout << "\n>>> 먹이가 부족합니다!" << endl;
                wait(500);
            }
            break;
        case 2:
            myPet->sleep();
            break;
        case 3:
            myPet->play();
            break;
        default: cout << "잘못된 선택입니다." << endl;
        }
    }
}

int main() {
    srand((unsigned int)time(0));

    while (true) {
        vector<Pet*> pets = loadAllPets();

        vector<int> affectionDiffs;

        for (Pet* p : pets) {
            int beforeAffection = p->getAffection();

            double timeUnits = getTimeDiff30Sec(p->getLastAccessTime());
            p->updateStatusByTime(timeUnits);

            int afterAffection = p->getAffection();
            int diff = afterAffection - beforeAffection;

            affectionDiffs.push_back(diff);

            p->updateLastAccessTime();
        }

        saveAllPets(pets);

        clearScreen();
        cout << "===========================================" << endl;
        cout << "        슥사고치(SCSAgotchi) (전체 : " << pets.size() << "/5)" << endl;
        cout << "===========================================" << endl;

        for (int i = 0; i < pets.size(); i++) {
            Pet* p = pets[i];
            cout << "[" << (i + 1) << "] [" << p->getType() << "] "
                << p->getName()
                << " (" << p->getGender() << "/Lv." << p->getLevel() << ")" << endl;

            cout << "    상태: 포만감 " << p->getSatiety()
                << " | 에너지 " << p->getEnergy();

            cout << " | 애정도 " << p->getAffection();

            if (affectionDiffs[i] != 0) {
                cout << " (";
                if (affectionDiffs[i] > 0) {
                    cout << "▲" << affectionDiffs[i];
                }
                else {
                    cout << "▼" << -affectionDiffs[i];
                }
                cout << ")";
            }
            cout << endl;

            cout << "    최근 플레이: " << p->getLastPlayTime() << endl;
            cout << "-------------------------------------------" << endl;
        }

        cout << "\n0. 펫 생성  1~5. 펫 선택 (키우기)  9. 종료" << endl;
        cout << "선택: "; int choice; cin >> choice;

        if (choice == 9) break;

        if (choice == 0) {
            createPet(pets);
        }
        else if (choice >= 1 && choice <= pets.size()) {
            Pet* selectedPet = pets[choice - 1];
            playGame(selectedPet, pets);
        }

        for (Pet* p : pets) delete p;
    }
    return 0;
}