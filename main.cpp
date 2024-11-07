#include<iostream>
using namespace std;

// 일반적인 프린트 기계를 위한 기본 클래스
class PrintMachine {
    string model, manufacturer;  // 프린터의 모델과 제조사
    int pcount, availablecount;  // 인쇄 횟수와 남아있는 종이 수
protected:
    // 보호된 생성자, 파생 클래스만 초기화할 수 있음
    PrintMachine(string model, string manufacturer, int availablecount) {
        this->model = model;
        this->manufacturer = manufacturer;
        this->availablecount = availablecount;
    }

    // 보호된 print 함수, 종이 수 감소를 처리함
    bool print(int pages) {
        if (availablecount < pages) {  // 필요한 종이 수가 부족할 경우
            cout << "용지가 부족하여 프린트 할 수 없습니다.\n";
            return false;  // 프린트 불가
        }
        for (int i = 0; i < pages; i++) {
            availablecount--;  // 프린트할 때마다 종이 수 감소
        }
        return true;  // 프린트 성공
    }

    // 모델을 반환하는 함수
    string get_model() { return model; }

    // 제조사를 반환하는 함수
    string get_manufacturer() { return manufacturer; }

    // 남아있는 종이 수를 반환하는 함수
    int get_availablecount() { return availablecount; }
};

// 잉크젯 프린터 클래스, PrintMachine을 상속받음
class PrintInkJet : public PrintMachine {
    int availableink;  // 남아있는 잉크의 수량
public:
    // 생성자, 모델, 제조사, 종이 수, 잉크 수량을 초기화
    PrintInkJet(string model, string manufacturer, int availablecount, int availableink)
        : PrintMachine(model, manufacturer, availablecount) {
        this->availableink = availableink;
    }

    // 잉크젯 프린터에서 인쇄하는 함수
    bool printInkJet(int pages) {
        if (!print(pages))  // 종이가 부족할 경우
            return false;
        if (availableink < pages) {  // 잉크가 부족할 경우
            cout << "잉크가 부족하여 프린트 할 수 없습니다.\n";
            return false;
        }
        for (int i = 0; i < pages; i++) {
            availableink--;  // 프린트할 때마다 잉크 수량 감소
        }
        return true;  // 프린트 성공
    }

    // 프린터 상태를 출력하는 함수
    void show() {
        cout << get_model() << "\t," << get_manufacturer() << "\t,남은 종이 "
            << get_availablecount() << "장\t,남은 잉크 " << availableink << endl;
    }
};

// 레이저 프린터 클래스, PrintMachine을 상속받음
class PrintLaser : public PrintMachine {
    int availabletoner;  // 남아있는 토너의 수량
public:
    // 생성자, 모델, 제조사, 종이 수, 토너 수량을 초기화
    PrintLaser(string model, string manufacturer, int availablecount, int availabletoner)
        : PrintMachine(model, manufacturer, availablecount) {
        this->availabletoner = availabletoner;
    }

    // 레이저 프린터에서 인쇄하는 함수
    bool printLaser(int pages) {
        if (!print(pages))  // 종이가 부족할 경우
            return false;
        if (availabletoner < pages) {  // 토너가 부족할 경우
            cout << "토너가 부족하여 프린트 할 수 없습니다.\n";
            return false;
        }
        for (int i = 0; i < pages; i++) {
            availabletoner--;  // 프린트할 때마다 토너 수량 감소
        }
        return true;  // 프린트 성공
    }

    // 프린터 상태를 출력하는 함수
    void show() {
        cout << get_model() << " ," << get_manufacturer() << "\t,남은 종이 "
            << get_availablecount() << "장\t,남은 토너 " << availabletoner << endl;
    }
};

// 메인 함수
int main() {
    int pnum, pages;
    char yorn;
    PrintInkJet* inkjet = new PrintInkJet("Officejet V40", "Hp", 5, 10);  // 잉크젯 프린터 생성
    PrintLaser* laser = new PrintLaser("SCX-6x45", "삼성전자", 3, 20);  // 레이저 프린터 생성

    cout << "현재 작동중인 2 대의 프린터는 아래와 같다\n";
    cout << "잉크젯 : ";
    inkjet->show();
    cout << "레이저 : ";
    laser->show();
    cout << endl;

    // 사용자 입력을 통한 프린트 기능
    while (true) {
        cout << "프린터(1:잉크젯, 2:레이저)와 매수 입력>>";
        cin >> pnum >> pages;

        // 선택한 프린터에서 인쇄 수행
        if (pnum == 1) {
            if (inkjet->printInkJet(pages))
                cout << "프린트 하였습니다.\n";
        }
        else if (pnum == 2) {
            if (laser->printLaser(pages))
                cout << "프린트 하였습니다.\n";
        }
        else {
            cout << "프린터를 잘못 선택하셨습니다.\n";
        }

        // 현재 상태 출력
        inkjet->show();
        laser->show();

        // 계속할지 여부를 묻는 루프
        while (true) {
            cout << "계속 프린트 하시겠습니까(y/n)>>";
            cin >> yorn;
            cout << endl;
            if (yorn == 'n') {  // 종료 선택 시
                
                return 0;
            }
            else if (yorn == 'y') {  // 계속할 경우
                break;
            }
            else {
                cout << "잘못 입력하셨습니다.\n";  // 유효하지 않은 입력
            }
        }
    }
    delete inkjet;
    delete laser;
}