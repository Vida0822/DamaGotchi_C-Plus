#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread> // 시간 지연을 위한 헤더
#include <chrono> // 시간 단위를 위한 헤더

#ifdef _WIN32
#include <cstdlib> // Windows system("cls")
#endif

using namespace std;

// 상태 상수 정의
enum State { IDLE, EATING, SLEEPING, PLAYING };

// ==========================================
// [유틸리티 함수] 화면 제어 및 시간 지연
// ==========================================
void clearScreen() {
    // 윈도우에서는 "cls", 맥/리눅스에서는 "clear"
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// ==========================================
// [Pet 클래스] 기본 뼈대
// ==========================================
class Pet {
protected:
    string name;
    string type;
    int hunger;
    int energy;

public:
    Pet(string n, string t, int h = 30, int e = 70)
        : name(n), type(t), hunger(h), energy(e) {
    }

    virtual ~Pet() {}

    // 상태에 따라 다른 그림을 그리는 가상 함수
    virtual void draw(int state) = 0;

    // 행동 함수들도 가상 함수(virtual)로 만들어 자식 클래스에서 애니메이션을 넣도록 함
    virtual void play() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;

    // 공통 상태 출력 함수
    void printStatus() {
        cout << "\n==================================================" << endl;
        cout << " [" << type << "] " << name << " | 배고픔: " << hunger << "/100 | 에너지: " << energy << "/100" << endl;
        cout << "==================================================" << endl;
    }

    // 게임 오버 체크 및 시간 경과
    bool passTime() {
        hunger += 10;
        energy -= 10;
        return (hunger < 100 && energy > 0);
    }

    string getSaveData() { return type + " " + name + " " + to_string(hunger) + " " + to_string(energy); }
    string getName() { return name; }
};

// ==========================================
// [Dog 클래스] 강아지 애니메이션 구현
// ==========================================
class Dog : public Pet {
public:
    Dog(string n, int h = 30, int e = 70) : Pet(n, "강아지", h, e) {}

    // 기본 그림 그리기 (한 컷)
    void draw(int state) override {
        switch (state) {
        case EATING:
            cout << "   / \\__  " << endl;
            cout << "  (    @\\___   [ 냠냠! ] " << endl;
            cout << "  /          O    V " << endl;
            cout << " /    (_____/     (m m) " << endl;
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
            cout << "        ||      " << endl;
            break;
        default: // IDLE
            cout << "      __       " << endl;
            cout << "    o'')}____//  " << endl;
            cout << "     `_/       )  " << endl;
            cout << "     (_(_/-(_/    " << endl;
        }
    }

    // [애니메이션] 먹기
    void eat() override {
        for (int i = 0; i < 3; i++) { // 3번 반복
            clearScreen(); printStatus();
            // 프레임 1: 입 벌림
            cout << "   / \\__  " << endl;
            cout << "  (    @\\___   [ 아~ ] " << endl;
            cout << "  /          O    " << endl;
            cout << " /    (_____/     (m m) " << endl;
            wait(300);

            clearScreen(); printStatus();
            // 프레임 2: 입 닫음
            draw(EATING);
            wait(300);
        }
        cout << "\n" << name << "가 냠냠 맛있게 먹습니다! (배고픔 -20)" << endl;
        hunger = max(0, hunger - 20);
        wait(1000);
    }

    // [애니메이션] 잠자기
    void sleep() override {
        for (int i = 0; i < 3; i++) {
            clearScreen(); printStatus();
            cout << "      |\\_/|  " << endl;
            cout << "      ( - - )   [ 새근... ] " << endl;
            cout << "      /_ _ \\ " << endl;
            cout << "     (______) " << endl;
            wait(400);

            clearScreen(); printStatus();
            draw(SLEEPING); // Zzz 나오는 그림
            wait(400);
        }
        cout << "\n" << name << "가 쿨쿨 잠을 잡니다. (에너지 +30)" << endl;
        energy = min(100, energy + 30);
        hunger += 10;
        wait(1000);
    }

    // [애니메이션] 놀기 (점프 효과)
    void play() override {
        for (int i = 0; i < 3; i++) {
            clearScreen(); printStatus();
            // 웅크리기
            cout << "       ^__^    " << endl;
            cout << "     / (oo) \\    [ 준비... ] " << endl;
            cout << "    (  \\_\\/_ ) " << endl;
            cout << "      /    \\   " << endl;
            wait(200);

            clearScreen(); printStatus();
            // 점프!
            draw(PLAYING);
            wait(200);
        }
        cout << "\n" << name << "와(과) 공놀이를 합니다! (에너지 -30)" << endl;
        energy -= 30; hunger += 20;
        wait(1000);
    }
};

// ==========================================
// [Cat 클래스] 고양이 애니메이션 구현
// ==========================================
class Cat : public Pet {
public:
    Cat(string n, int h = 30, int e = 70) : Pet(n, "고양이", h, e) {}

    void draw(int state) override {
        switch (state) {
        case EATING:
            cout << "    \\    /  " << endl;
            cout << "     )  (       [ 쩝쩝... ] " << endl;
            cout << "    (  /  )  " << endl;
            cout << "     \\(__)| " << endl;
            break;
        case SLEEPING:
            cout << "      |\\      _,,,---,,_ " << endl;
            cout << "      /,`.-'`'     -.  ;-;;,_ " << endl;
            cout << "     |,4-  ) )-,_. ,\\ (  `'-' " << endl;
            cout << "    '---''(_/--'  `-'\\_)  [Zzz]" << endl;
            break;
        case PLAYING:
            cout << "       /\\_/\\  " << endl;
            cout << "      ( ^.^ )  " << endl;
            cout << "       > ^ <    " << endl;
            cout << "      /     \\  [ 냥냥펀치! ]" << endl;
            break;
        default: // IDLE
            cout << "       |\\__/,|    (`\\  " << endl;
            cout << "     _.|o o  |_    ) ) " << endl;
            cout << "   -(((---(((-------- " << endl;
        }
    }

    // [애니메이션] 먹기 (고개 숙이기)
    void eat() override {
        for (int i = 0; i < 3; i++) {
            clearScreen(); printStatus();
            // 고개 듬
            cout << "    \\    /  " << endl;
            cout << "     )  (       [ ? ] " << endl;
            cout << "    (  /  )  " << endl;
            cout << "     \\(__)| " << endl;
            wait(300);

            clearScreen(); printStatus();
            // 고개 숙여 먹음
            draw(EATING);
            wait(300);
        }
        cout << "\n" << name << "가 냠냠 맛있게 먹습니다! (배고픔 -20)" << endl;
        hunger = max(0, hunger - 20);
        wait(1000);
    }

    // [애니메이션] 잠자기
    void sleep() override {
        for (int i = 0; i < 3; i++) {
            clearScreen(); printStatus();
            // 꼬리 내림
            cout << "      |\\      _,,,---,,_ " << endl;
            cout << "      /,`.-'`'     -.  ;-;;,_ " << endl;
            cout << "     |,4-  ) )-,_. ,\\ (  `'-' " << endl;
            cout << "    '---''(_/--'  `-'\\_)  " << endl;
            wait(400);

            clearScreen(); printStatus();
            // 꼬리 올림 + Zzz
            draw(SLEEPING);
            wait(400);
        }
        cout << "\n" << name << "가 쿨쿨 잠을 잡니다. (에너지 +30)" << endl;
        energy = min(100, energy + 30);
        hunger += 10;
        wait(1000);
    }

    // [애니메이션] 놀기 (펀치!)
    void play() override {
        for (int i = 0; i < 4; i++) {
            clearScreen(); printStatus();
            // 왼손 펀치
            cout << "       /\\_/\\  " << endl;
            cout << "      ( >.< )  " << endl;
            cout << "      / > ^ <    " << endl;
            cout << "     (      /  [ 얍! ]" << endl;
            wait(200);

            clearScreen(); printStatus();
            // 오른손 펀치
            draw(PLAYING);
            wait(200);
        }
        cout << "\n" << name << "이(가) 캣잎을 가지고 놉니다. (에너지 -15)" << endl;
        energy -= 15; hunger += 10;
        wait(1000);
    }
};

// ==========================================
// [메인 로직] 저장/불러오기 및 실행
// ==========================================
void saveGame(Pet* p) {
    ofstream outFile("savegame.txt");
    if (outFile.is_open()) {
        outFile << p->getSaveData();
        outFile.close();
        cout << "\n>>> 데이터가 안전하게 저장되었습니다." << endl;
        wait(1000);
    }
}

Pet* loadGame() {
    ifstream inFile("savegame.txt");
    if (!inFile.is_open()) return nullptr;
    string type, name;
    int hunger, energy;
    if (inFile >> type >> name >> hunger >> energy) {
        if (type == "강아지") return new Dog(name, hunger, energy);
        if (type == "고양이") return new Cat(name, hunger, energy);
    }
    return nullptr;
}

int main() {
    Pet* myPet = loadGame();

    if (myPet == nullptr) {
        clearScreen();
        cout << "1. 강아지  2. 고양이\n선택: ";
        int typeChoice; cin >> typeChoice;
        cout << "이름: "; string name; cin >> name;
        if (typeChoice == 2) myPet = new Cat(name);
        else myPet = new Dog(name);
    }

    while (true) {
        clearScreen(); // 매 턴마다 화면 깨끗하게
        myPet->printStatus();
        myPet->draw(IDLE); // 평소에는 가만히 있는 모습

        cout << "\n1.먹이 2.잠자기 3.놀기 4.종료\n선택: ";
        int action; cin >> action;

        if (action == 4) { saveGame(myPet); break; }

        // 각 행동 함수 내부에서 애니메이션 재생 -> 상태 변화
        if (action == 1) myPet->eat();
        else if (action == 2) myPet->sleep();
        else if (action == 3) myPet->play();

        // 행동 후 생존 체크
        if (!myPet->passTime()) {
            cout << "\n" << myPet->getName() << "가 쓰러졌습니다... 게임 오버." << endl;
            remove("savegame.txt");
            break;
        }
    }
    delete myPet;
    return 0;
}