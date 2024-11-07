#include<iostream>
using namespace std;

// �Ϲ����� ����Ʈ ��踦 ���� �⺻ Ŭ����
class PrintMachine {
    string model, manufacturer;  // �������� �𵨰� ������
    int pcount, availablecount;  // �μ� Ƚ���� �����ִ� ���� ��
protected:
    // ��ȣ�� ������, �Ļ� Ŭ������ �ʱ�ȭ�� �� ����
    PrintMachine(string model, string manufacturer, int availablecount) {
        this->model = model;
        this->manufacturer = manufacturer;
        this->availablecount = availablecount;
    }

    // ��ȣ�� print �Լ�, ���� �� ���Ҹ� ó����
    bool print(int pages) {
        if (availablecount < pages) {  // �ʿ��� ���� ���� ������ ���
            cout << "������ �����Ͽ� ����Ʈ �� �� �����ϴ�.\n";
            return false;  // ����Ʈ �Ұ�
        }
        for (int i = 0; i < pages; i++) {
            availablecount--;  // ����Ʈ�� ������ ���� �� ����
        }
        return true;  // ����Ʈ ����
    }

    // ���� ��ȯ�ϴ� �Լ�
    string get_model() { return model; }

    // �����縦 ��ȯ�ϴ� �Լ�
    string get_manufacturer() { return manufacturer; }

    // �����ִ� ���� ���� ��ȯ�ϴ� �Լ�
    int get_availablecount() { return availablecount; }
};

// ��ũ�� ������ Ŭ����, PrintMachine�� ��ӹ���
class PrintInkJet : public PrintMachine {
    int availableink;  // �����ִ� ��ũ�� ����
public:
    // ������, ��, ������, ���� ��, ��ũ ������ �ʱ�ȭ
    PrintInkJet(string model, string manufacturer, int availablecount, int availableink)
        : PrintMachine(model, manufacturer, availablecount) {
        this->availableink = availableink;
    }

    // ��ũ�� �����Ϳ��� �μ��ϴ� �Լ�
    bool printInkJet(int pages) {
        if (!print(pages))  // ���̰� ������ ���
            return false;
        if (availableink < pages) {  // ��ũ�� ������ ���
            cout << "��ũ�� �����Ͽ� ����Ʈ �� �� �����ϴ�.\n";
            return false;
        }
        for (int i = 0; i < pages; i++) {
            availableink--;  // ����Ʈ�� ������ ��ũ ���� ����
        }
        return true;  // ����Ʈ ����
    }

    // ������ ���¸� ����ϴ� �Լ�
    void show() {
        cout << get_model() << "\t," << get_manufacturer() << "\t,���� ���� "
            << get_availablecount() << "��\t,���� ��ũ " << availableink << endl;
    }
};

// ������ ������ Ŭ����, PrintMachine�� ��ӹ���
class PrintLaser : public PrintMachine {
    int availabletoner;  // �����ִ� ����� ����
public:
    // ������, ��, ������, ���� ��, ��� ������ �ʱ�ȭ
    PrintLaser(string model, string manufacturer, int availablecount, int availabletoner)
        : PrintMachine(model, manufacturer, availablecount) {
        this->availabletoner = availabletoner;
    }

    // ������ �����Ϳ��� �μ��ϴ� �Լ�
    bool printLaser(int pages) {
        if (!print(pages))  // ���̰� ������ ���
            return false;
        if (availabletoner < pages) {  // ��ʰ� ������ ���
            cout << "��ʰ� �����Ͽ� ����Ʈ �� �� �����ϴ�.\n";
            return false;
        }
        for (int i = 0; i < pages; i++) {
            availabletoner--;  // ����Ʈ�� ������ ��� ���� ����
        }
        return true;  // ����Ʈ ����
    }

    // ������ ���¸� ����ϴ� �Լ�
    void show() {
        cout << get_model() << " ," << get_manufacturer() << "\t,���� ���� "
            << get_availablecount() << "��\t,���� ��� " << availabletoner << endl;
    }
};

// ���� �Լ�
int main() {
    int pnum, pages;
    char yorn;
    PrintInkJet* inkjet = new PrintInkJet("Officejet V40", "Hp", 5, 10);  // ��ũ�� ������ ����
    PrintLaser* laser = new PrintLaser("SCX-6x45", "�Ｚ����", 3, 20);  // ������ ������ ����

    cout << "���� �۵����� 2 ���� �����ʹ� �Ʒ��� ����\n";
    cout << "��ũ�� : ";
    inkjet->show();
    cout << "������ : ";
    laser->show();
    cout << endl;

    // ����� �Է��� ���� ����Ʈ ���
    while (true) {
        cout << "������(1:��ũ��, 2:������)�� �ż� �Է�>>";
        cin >> pnum >> pages;

        // ������ �����Ϳ��� �μ� ����
        if (pnum == 1) {
            if (inkjet->printInkJet(pages))
                cout << "����Ʈ �Ͽ����ϴ�.\n";
        }
        else if (pnum == 2) {
            if (laser->printLaser(pages))
                cout << "����Ʈ �Ͽ����ϴ�.\n";
        }
        else {
            cout << "�����͸� �߸� �����ϼ̽��ϴ�.\n";
        }

        // ���� ���� ���
        inkjet->show();
        laser->show();

        // ������� ���θ� ���� ����
        while (true) {
            cout << "��� ����Ʈ �Ͻðڽ��ϱ�(y/n)>>";
            cin >> yorn;
            cout << endl;
            if (yorn == 'n') {  // ���� ���� ��
                
                return 0;
            }
            else if (yorn == 'y') {  // ����� ���
                break;
            }
            else {
                cout << "�߸� �Է��ϼ̽��ϴ�.\n";  // ��ȿ���� ���� �Է�
            }
        }
    }
    delete inkjet;
    delete laser;
}