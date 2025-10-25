#include "money.h"
#include <iostream>
#include <limits>

using namespace std;

// ������� ��� ������� ������ �����
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ������� ��� ����������� ����
void displayMenu() {
    cout << "\n=== ���� �������� � ��������� ������� ===" << endl;
    cout << "1. �������� ������� ����� �����" << endl;
    cout << "2. �������� �������� ����" << endl;
    cout << "3. ��������� �������� ����" << endl;
    cout << "4. ����������� �����" << endl;
    cout << "5. ���������� ���������" << endl;
    cout << "6. ���������� �����" << endl;
    cout << "7. ����������� �������� (����� - ������� - ������)" << endl;
    cout << "0. �����" << endl;
    cout << "�������� ��������: ";
}

int main() {
    // ������������� ������ �����
    Money::setExchangeRate("USD", "EUR", 0.85);
    Money::setExchangeRate("USD", "RUB", 92.50);
    Money::setExchangeRate("EUR", "RUB", 108.80);

    int choice;
    bool running = true;

    cout << "=== ��������� ��� ������ � ��������� ������� ===" << endl;

    while (running) {
        displayMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 0: {
            running = false;
            cout << "����� �� ���������..." << endl;
            break;
        }

        case 1: {
            // �������� ����� �����
            Money::displayAllRates();
            break;
        }

        case 2: {
            // �������� ����
            cout << "\n--- �������� �������� ���� ---" << endl;
            Money sum1 = Money::inputMoney("������ �����:\n");
            Money sum2 = Money::inputMoney("������ �����:\n");

            Money result = sum1 + sum2;
            cout << "��������� ��������: ";
            result.print();
            cout << endl;
            break;
        }

        case 3: {
            // ��������� ����
            cout << "\n--- ��������� �������� ���� ---" << endl;
            Money sum1 = Money::inputMoney("�����������:\n");
            Money sum2 = Money::inputMoney("����������:\n");

            Money result = sum1 - sum2;
            cout << "��������� ���������: ";
            result.print();
            cout << endl;
            break;
        }

        case 4: {
            // ����������� �����
            cout << "\n--- ����������� ����� ---" << endl;
            Money original = Money::inputMoney("�������� �����:\n");

            string targetCurrency;
            cout << "������� ������� ������ (USD, EUR, RUB): ";
            cin >> targetCurrency;

            // ����������� � ������� �������
            for (char& c : targetCurrency) {
                c = toupper(c);
            }

            try {
                Money converted = original.convertTo(targetCurrency);
                cout << "��������� �����������: ";
                converted.print();
                cout << endl;
            }
            catch (const invalid_argument& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }

        case 5: {
            // ���������� ���������
            cout << "\n--- ���������� ��������� ---" << endl;
            Money original = Money::inputMoney("������� �����:\n");

            double percent;
            cout << "������� �������: ";
            cin >> percent;

            Money percentAmount = original.calculatePercent(percent).rounded();
            cout << percent << "% �� �����: ";
            percentAmount.print();
            cout << endl;
            break;
        }

        case 6: {
            // ���������� �����
            cout << "\n--- ���������� ����� ---" << endl;
            Money original = Money::inputMoney("�������� �����:\n");

            Money rounded = original.rounded();
            cout << "�������� �����: ";
            original.print();
            cout << "\n����������� �����: ";
            rounded.print();
            cout << endl;
            break;
        }

        case 7: {
            // ����������� ��������
            cout << "\n--- ����������� �������� ---" << endl;
            cout << "������ ������� ������ ����� �������� � �������" << endl;

            Money income = Money::inputMoney("������� �����:\n");
            Money expenses = Money::inputMoney("������� �������:\n");

            double taxRate;
            cout << "������� ������ ������ (%): ";
            cin >> taxRate;

            // �������
            Money netBeforeTax = income - expenses;
            Money tax = netBeforeTax.calculatePercent(taxRate).rounded();
            Money netIncome = netBeforeTax - tax;

            cout << "\n--- ���������� ������� ---" << endl;
            cout << "�����: "; income.print(); cout << endl;
            cout << "�������: "; expenses.print(); cout << endl;
            cout << "����� �� ���������������: "; netBeforeTax.print(); cout << endl;
            cout << "����� (" << taxRate << "%): "; tax.print(); cout << endl;
            cout << "������ �����: "; netIncome.print(); cout << endl;
            break;
        }

        default: {
            cout << "�������� �����! ���������� �����." << endl;
            break;
        }
        }

        if (choice != 0) {
            cout << "\n������� Enter ��� �����������...";
            clearInputBuffer();
        }
    }

    cout << "��������� ���������. ������� �� �������������!" << endl;
    return 0;
}