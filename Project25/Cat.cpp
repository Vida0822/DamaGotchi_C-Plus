#include "Cat.h"
#include <algorithm>
#include <iostream>

using namespace std;

Cat::Cat(string n, string g, int s, int e, int lv, int aff, int ac, string lastTime, string playTime)
    : Pet(n, "고양이", g, s, e, lv, aff, ac, lastTime, playTime) {
}

int Cat::calculateAffectionDrop(double timeUnits) {
    return ((int)timeUnits) * 5;
}

void Cat::draw(int state) {
    switch (state) {
    case EATING:
        cout << "        /\\_/\\  " << endl;
        cout << "       ( >.< )      <((((~  " << endl;
        cout << "       (  v  )     _______  " << endl;
        cout << "      /       \\   / 생 선 \\ " << endl;
        break;
    case SLEEPING:
        cout << "       |\\       _,,,---,,_ " << endl;
        cout << "       /,`.-'`'      -.  ;-;;,_ " << endl;
        cout << "      |,4-  ) )-,_. ,\\ (  `'-' " << endl;
        cout << "     '---''(_/--'  `-'\\_)  [Zzz]" << endl;
        break;
    case PLAYING:
        cout << "        /\\_/\\  " << endl;
        cout << "       ( ^.^ )  " << endl;
        cout << "        > ^ <     " << endl;
        cout << "       /      \\  [ 냥냥펀치! ]" << endl;
        break;
    default:
        cout << "        |\\__/,|    (`\\  " << endl;
        cout << "      _.|o o  |_    ) ) " << endl;
        cout << "     -(((---(((-------- " << endl;
    }
}

void Cat::eat() {
    for (int i = 0; i < 3; i++) {
        clearScreen(); printStatus();
        cout << "        /\\_/\\  " << endl;
        cout << "       ( o.o )      <((((~  " << endl;
        cout << "       (  _  )     _______  " << endl;
        cout << "      /       \\   / 생 선 \\ " << endl;
        wait(400);

        clearScreen(); printStatus();
        draw(EATING);
        wait(400);
    }
    cout << "\n>>> " << name << "가 생선을 야무지게 발라 먹습니다. (포만감 +20)" << endl;
    satiety = min(100, satiety + 20);

    actionCount++;
    checkLevelUp();

    wait(1000);
}

void Cat::sleep() {
    for (int i = 0; i < 3; i++) {
        clearScreen(); printStatus();
        cout << "       |\\       _,,,---,,_ " << endl;
        cout << "       /,`.-'`'      -.  ;-;;,_ " << endl;
        cout << "      |,4-  ) )-,_. ,\\ (  `'-' " << endl;
        cout << "     '---''(_/--'  `-'\\_)  " << endl;
        wait(400);

        clearScreen(); printStatus();
        draw(SLEEPING);
        wait(400);
    }
    cout << "\n>>> " << name << "(이)가 꿀잠을 잡니다. (에너지 +20)" << endl;
    energy = min(100, energy + 20);

    actionCount++;
    checkLevelUp();

    wait(1000);
}

void Cat::play() {
    if (energy < 20) {
        cout << "\n>>> 에너지가 부족해서 놀 수 없습니다! (필요: 20)" << endl;
        wait(1000);
        return;
    }

    while (true) {
        clearScreen();
        cout << "\n=== [ " << name << "와(과) 무엇을 하고 놀까요? ] ===" << endl;
        cout << "    (현재 레벨: " << level << " / 누적 행동: " << actionCount << ")" << endl;

        cout << "1. 낚싯대 놀이 (Lv.1)" << endl;

        if (level >= 2) cout << "2. 레이저 포인터 (Lv.2)" << endl;
        else cout << "2. ??? (Lv.2 이상 가능)" << endl;

        if (level >= 3) cout << "3. 박스 들어가기 (Lv.3)" << endl;
        else cout << "3. ??? (Lv.3 이상 가능)" << endl;

        if (level >= 4) cout << "4. 캣휠 타기 (Lv.4)" << endl;
        else cout << "4. ??? (Lv.4 이상 가능)" << endl;

        if (level >= 5) cout << "5. 츄르 먹여주기 (Lv.5)" << endl;
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
            playMsg = "현란한 낚싯대 솜씨에 정신을 못 차립니다!";
            for (int i = 0; i < 4; i++) {
                clearScreen(); printStatus();
                cout << "        /\\_/\\  " << endl;
                cout << "       ( o.o )    ~  " << endl;
                cout << "        > ^ <    ( ) " << endl;
                cout << "       /      \\    |  " << endl;
                wait(200);
                clearScreen(); printStatus();
                draw(PLAYING);
                wait(200);
            }
        }
        else if (choice == 2) { 
            playMsg = "빨간 점을 잡으려고 우다다 뛰어다닙니다!";
            for (int i = 0; i < 4; i++) {
                clearScreen(); printStatus();
                cout << "        /\\_/\\  " << endl;
                cout << "       ( o.o ) " << endl;
                cout << "      *(  _  ) " << endl;
                cout << "       /      \\ " << endl;
                wait(200);
                clearScreen(); printStatus();
                cout << "        /\\_/\\  " << endl;
                cout << "       ( o.o ) " << endl;
                cout << "       (  _  )*" << endl;
                cout << "       /      \\ " << endl;
                wait(200);
            }
        }
        else if (choice == 3) { 
            playMsg = "역시 고양이는 박스를 제일 좋아하네요.";
            for (int i = 0; i < 3; i++) {
                clearScreen(); printStatus();
                cout << "        /\\_/\\     _______ " << endl;
                cout << "       ( o.o )   | box  | " << endl;
                cout << "       (  _  )   |______| " << endl;
                wait(500);
                clearScreen(); printStatus();
                cout << "                 _______ " << endl;
                cout << "                | /\\_/\\| " << endl;
                cout << "                | ^ - ^| " << endl;
                cout << "                |______| " << endl;
                wait(500);
            }
        }
        else if (choice == 4) { 
            playMsg = "캣휠을 타며 에너지를 발산합니다!";
            for (int i = 0; i < 6; i++) {
                clearScreen(); printStatus();
                cout << "        /\\_/\\   // " << endl;
                cout << "       ( >.< ) //  " << endl;
                cout << "       /  _  )//   " << endl;
                cout << "      (  /  )/      " << endl;
                wait(150);
                clearScreen(); printStatus();
                cout << "        /\\_/\\   // " << endl;
                cout << "       ( >.< ) //  " << endl;
                cout << "       /  _  )//   " << endl;
                cout << "      (       )      " << endl;
                wait(150);
            }
        }
        else if (choice == 5) { 
            playMsg = "츄르를 먹으며 행복해합니다. (애정도 대폭 상승!)";
            for (int i = 0; i < 3; i++) {
                clearScreen(); printStatus();
                cout << "        /\\_/\\  " << endl;
                cout << "       ( o.o )    [ Churu ] " << endl;
                cout << "       (  _  )    / " << endl;
                cout << "       /      \\  /  " << endl;
                wait(300);
                clearScreen(); printStatus();
                cout << "        /\\_/\\  " << endl;
                cout << "       ( ^Q^ )    [ Churu ] " << endl;
                cout << "       (  _  )    / " << endl;
                cout << "       /      \\  /  " << endl;
                wait(300);
            }
            affection += 5;
        }
        else {
            cout << "\n>>> 잘못된 선택입니다." << endl;
            wait(1000);
            continue;
        }

        cout << "\n>>> " << playMsg << endl;
        cout << ">>> (애정도 +10, 에너지 -10, 포만감 -10)" << endl;

        energy = max(0, energy - 10);
        affection = min(100, affection + 10);
        satiety = max(0, satiety - 10);

        actionCount++;
        checkLevelUp();

        wait(1500);
        break;
    }
}