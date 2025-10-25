#include "money.h"
#include <iostream>
#include <limits>

using namespace std;

// Функция для очистки буфера ввода
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Функция для отображения меню
void displayMenu() {
    cout << "\n=== МЕНЮ ОПЕРАЦИЙ С ДЕНЕЖНЫМИ СУММАМИ ===" << endl;
    cout << "1. Показать текущие курсы валют" << endl;
    cout << "2. Сложение денежных сумм" << endl;
    cout << "3. Вычитание денежных сумм" << endl;
    cout << "4. Конвертация валют" << endl;
    cout << "5. Вычисление процентов" << endl;
    cout << "6. Округление суммы" << endl;
    cout << "7. Комплексная операция (доход - расходы - налоги)" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите операцию: ";
}

int main() {
    // Инициализация курсов валют
    Money::setExchangeRate("USD", "EUR", 0.85);
    Money::setExchangeRate("USD", "RUB", 92.50);
    Money::setExchangeRate("EUR", "RUB", 108.80);

    int choice;
    bool running = true;

    cout << "=== ПРОГРАММА ДЛЯ РАБОТЫ С ДЕНЕЖНЫМИ СУММАМИ ===" << endl;

    while (running) {
        displayMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 0: {
            running = false;
            cout << "Выход из программы..." << endl;
            break;
        }

        case 1: {
            // Показать курсы валют
            Money::displayAllRates();
            break;
        }

        case 2: {
            // Сложение сумм
            cout << "\n--- СЛОЖЕНИЕ ДЕНЕЖНЫХ СУММ ---" << endl;
            Money sum1 = Money::inputMoney("Первая сумма:\n");
            Money sum2 = Money::inputMoney("Вторая сумма:\n");

            Money result = sum1 + sum2;
            cout << "Результат сложения: ";
            result.print();
            cout << endl;
            break;
        }

        case 3: {
            // Вычитание сумм
            cout << "\n--- ВЫЧИТАНИЕ ДЕНЕЖНЫХ СУММ ---" << endl;
            Money sum1 = Money::inputMoney("Уменьшаемое:\n");
            Money sum2 = Money::inputMoney("Вычитаемое:\n");

            Money result = sum1 - sum2;
            cout << "Результат вычитания: ";
            result.print();
            cout << endl;
            break;
        }

        case 4: {
            // Конвертация валют
            cout << "\n--- КОНВЕРТАЦИЯ ВАЛЮТ ---" << endl;
            Money original = Money::inputMoney("Исходная сумма:\n");

            string targetCurrency;
            cout << "Введите целевую валюту (USD, EUR, RUB): ";
            cin >> targetCurrency;

            // Преобразуем в верхний регистр
            for (char& c : targetCurrency) {
                c = toupper(c);
            }

            try {
                Money converted = original.convertTo(targetCurrency);
                cout << "Результат конвертации: ";
                converted.print();
                cout << endl;
            }
            catch (const invalid_argument& e) {
                cout << "Ошибка: " << e.what() << endl;
            }
            break;
        }

        case 5: {
            // Вычисление процентов
            cout << "\n--- ВЫЧИСЛЕНИЕ ПРОЦЕНТОВ ---" << endl;
            Money original = Money::inputMoney("Базовая сумма:\n");

            double percent;
            cout << "Введите процент: ";
            cin >> percent;

            Money percentAmount = original.calculatePercent(percent).rounded();
            cout << percent << "% от суммы: ";
            percentAmount.print();
            cout << endl;
            break;
        }

        case 6: {
            // Округление суммы
            cout << "\n--- ОКРУГЛЕНИЕ СУММЫ ---" << endl;
            Money original = Money::inputMoney("Исходная сумма:\n");

            Money rounded = original.rounded();
            cout << "Исходная сумма: ";
            original.print();
            cout << "\nОкругленная сумма: ";
            rounded.print();
            cout << endl;
            break;
        }

        case 7: {
            // Комплексная операция
            cout << "\n--- КОМПЛЕКСНАЯ ОПЕРАЦИЯ ---" << endl;
            cout << "Расчет чистого дохода после расходов и налогов" << endl;

            Money income = Money::inputMoney("Введите доход:\n");
            Money expenses = Money::inputMoney("Введите расходы:\n");

            double taxRate;
            cout << "Введите ставку налога (%): ";
            cin >> taxRate;

            // Расчеты
            Money netBeforeTax = income - expenses;
            Money tax = netBeforeTax.calculatePercent(taxRate).rounded();
            Money netIncome = netBeforeTax - tax;

            cout << "\n--- РЕЗУЛЬТАТЫ РАСЧЕТА ---" << endl;
            cout << "Доход: "; income.print(); cout << endl;
            cout << "Расходы: "; expenses.print(); cout << endl;
            cout << "Доход до налогообложения: "; netBeforeTax.print(); cout << endl;
            cout << "Налог (" << taxRate << "%): "; tax.print(); cout << endl;
            cout << "ЧИСТЫЙ ДОХОД: "; netIncome.print(); cout << endl;
            break;
        }

        default: {
            cout << "Неверный выбор! Попробуйте снова." << endl;
            break;
        }
        }

        if (choice != 0) {
            cout << "\nНажмите Enter для продолжения...";
            clearInputBuffer();
        }
    }

    cout << "Программа завершена. Спасибо за использование!" << endl;
    return 0;
}