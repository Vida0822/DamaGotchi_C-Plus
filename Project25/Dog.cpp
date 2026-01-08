#include "Dog.h"
#include <algorithm>
#include <iostream>

using namespace std;

Dog::Dog(string n, string g, int s, int e, int lv, int aff, int ac, string lastTime, string playTime)
    : Pet(n, "강아지", g, s, e, lv, aff, ac, lastTime, playTime) {
}

int Dog::calculateAffectionDrop(double timeUnits) {
    return ((int)timeUnits) * 10;
}

void Dog::draw(int state) {
    switch (state) {
    case EATING:
        cout << "   / \\__  " << endl;
        cout << "  (    @\\___   [ 냠냠! ] " << endl;
        cout << "  /          O    V " << endl;
        cout << " /     (_____/     (m m) " << endl;
        break;
    case SLEEPING:
        cout << "      |\\_/|  " << endl;
        cout << "      ( Z z )   [ 드르렁... ] " << endl;
        cout << "      /_ _ \\ " << endl;
        cout << "     (______) " << endl;
        break;
    case PLAYING:
        cout << "    \\  ^__^  / " << endl;
        cout << "     \\ (oo) /    [ 신나개! ] " << endl;
        cout << "      \\_\\/_/ " << endl;
        cout << "        ||       " << endl;
        break;
    default: // IDLE
        cout << "       __        " << endl;
        cout << "     o'')}____//  " << endl;
        cout << "      `_/        )  " << endl;
        cout << "      (_(_/-(_/     " << endl;
    }
}

void Dog::eat() {
    for (int i = 0; i < 3; i++) {
        clearScreen(); printStatus();
        cout << "   / \\__  " << endl;
        cout << "  (    @\\___   [ 아~ ] " << endl;
        cout << "  /          O    " << endl;
        cout << " /     (_____/     (m m) " << endl;
        wait(300);

        clearScreen(); printStatus();
        draw(EATING);
        wait(300);
    }
    cout << "\n>>> " << name << "(이)가 밥을 먹습니다. (포만감 +20)" << endl;
    satiety = min(100, satiety + 20);

    actionCount++;
    checkLevelUp();

    wait(1000);
}

void Dog::sleep() {
    for (int i = 0; i < 3; i++) {
        clearScreen(); printStatus();
        cout << "      |\\_/|  " << endl;
        cout << "      ( - - )   [ 새근... ] " << endl;
        cout << "      /_ _ \\ " << endl;
        cout << "     (______) " << endl;
        wait(400);

        clearScreen(); printStatus();
        draw(SLEEPING);
        wait(400);
    }
    cout << "\n>>> " << name << "가 잠을 잡니다. (에너지 +20)" << endl;
    energy = min(100, energy + 20);

    actionCount++;
    checkLevelUp();

    wait(1000);
}

void Dog::play() {
    if (energy < 20) {
        cout << "\n>>> 에너지가 부족해서 놀 수 없습니다! (필요: 20)" << endl;
        wait(1000);
        return;
    }

    while (true) {
        clearScreen();
        cout << "\n=== [ " << name << "와(과) 무엇을 하고 놀까요? ] ===" << endl;
        cout << "    (현재 레벨: " << level << " / 누적 행동: " << actionCount << ")" << endl;

        cout << "1. 공 던지기 (Lv.1)" << endl;

        if (level >= 2) cout << "2. 터그 놀이 (Lv.2)" << endl;
        else cout << "2. ??? (Lv.2 이상 가능)" << endl;

        if (level >= 3) cout << "3. 산책 가기 (Lv.3)" << endl;
        else cout << "3. ??? (Lv.3 이상 가능)" << endl;

        if (level >= 4) cout << "4. 원반 던지기 (Lv.4)" << endl;
        else cout << "4. ??? (Lv.4 이상 가능)" << endl;

        if (level >= 5) cout << "5. 손! 훈련 (Lv.5)" << endl;
        else cout << "5. ??? (Lv.5 이상 가능)" << endl;

        cout << "0. 뒤로 가기" << endl;
        cout << "선택: ";
        int choice; cin >> choice;

        if (choice == 0) return;

        if ((choice == 2 && level < 2) ||
            (choice == 3 && level < 3) ||
            (choice == 4 && level < 4) ||
            (choice == 5 && level < 5)) {
            cout << "\n>>> 아직 레벨이 부족하여 이 놀이를 할 수 없습니다!" << endl;
            wait(1000);
            continue;
        }

        string playMsg = "";
        if (choice == 1) {
            playMsg = "공을 던지자 신나게 뛰어갑니다!";
            for (int i = 0; i < 3; i++) {
                clearScreen(); printStatus();
                cout << "       ^__^    " << endl;
                cout << "     / (oo) \\    [ 공 어딨지? ] " << endl;
                cout << "    (  \\_\\/_ ) " << endl;
                cout << "      /    \\   " << endl;
                wait(300);
                clearScreen(); printStatus();
                draw(PLAYING); 
                wait(300);
            }
        }
        else if (choice == 2) { 
            playMsg = "장난감을 물고 놓지 않습니다! 으르렁~";
            for (int i = 0; i < 4; i++) {
                clearScreen(); printStatus();
                cout << "      < ( >_<)====   [ 끙끙! ]" << endl;
                cout << "       /(  _ ) " << endl;
                cout << "        /    \\  " << endl;
                wait(200);
                clearScreen(); printStatus();
                cout << "        ====(>_< ) >  [ 안져! ]" << endl;
                cout << "           ( _  )\\ " << endl;
                cout << "           /    \\  " << endl;
                wait(200);
            }
        }
        else if (choice == 3) {
            playMsg = "꼬리를 흔들며 산책을 합니다.";
            for (int i = 0; i < 4; i++) {
                clearScreen(); printStatus();
                cout << "       __        " << endl;
                cout << "     o'')}____//    [ 룰루~ ]" << endl;
                cout << "      `_/        )  " << endl;
                cout << "      (_(_/-(_/     " << endl;
                wait(300);
                clearScreen(); printStatus();
                cout << "       __        " << endl;
                cout << "     o'')}____//    [ 랄라~ ]" << endl;
                cout << "      `_/        )  " << endl;
                cout << "      (_(_/  (_/     " << endl;
                wait(300);
            }
        }
        else if (choice == 4) {
            playMsg = "원반을 나이스 캐치합니다!";
            for (int i = 0; i < 3; i++) {
                clearScreen(); printStatus();
                cout << "       ^__^    " << endl;
                cout << "     / (..) \\    [ 원반이다! ] " << endl;
                cout << "    (  \\_\\/_ ) " << endl;
                cout << "      /    \\   " << endl;
                wait(300);
                clearScreen(); printStatus();
                cout << "    \\  ^__^  / " << endl;
                cout << "     \\ (OO) /    [ 앙! ] " << endl;
                cout << "      \\_\\/_/ " << endl;
                cout << "     ==== ||        " << endl;
                wait(400);
            }
        }
        else if (choice == 5) {
            playMsg = "앞발을 척! 올립니다. 똑똑하네요.";
            for (int i = 0; i < 3; i++) {
                clearScreen(); printStatus();
                cout << "       ^__^    " << endl;
                cout << "      (oo  )      [ 주인님? ] " << endl;
                cout << "     (______) " << endl;
                wait(500);
                clearScreen(); printStatus();
                cout << "       ^__^    " << endl;
                cout << "      (OO  ) /    [ 옛다 손! ] " << endl;
                cout << "     (______) " << endl;
                wait(500);
            }
        }
        else {
            cout << "\n>>> 잘못된 선택입니다." << endl;
            wait(1000);
            continue;
        }

        cout << "\n>>> " << playMsg << endl;
        cout << ">>> (애정도+10, 에너지-15, 포만감-10)" << endl;

        energy = max(0, energy - 15);
        affection = min(100, affection + 10);
        satiety = max(0, satiety - 10);

        actionCount++;
        checkLevelUp();

        wait(1500);
        break; 
    }
}