#include "money_lib.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>

int main() {
    try {
        std::cout << "=== БИБЛИОТЕКА ДЛЯ РАБОТЫ С ДЕНЕЖНЫМИ СУММАМИ ===\n\n";
        
        // Ввод данных
        std::vector<MoneyLib::Money> amounts = MoneyLib::inputMoneyAmounts();
        std::vector<MoneyLib::ExchangeRate> rates = MoneyLib::inputExchangeRates();
        
        // Выбор целевой валюты
        std::string targetCurrency;
        std::cout << "Введите целевую валюту для расчетов (RUB, USD, EUR): ";
        std::cin >> targetCurrency;
        
        // Использование лямбда-выражения 
        std::transform(targetCurrency.begin(), targetCurrency.end(),
                       targetCurrency.begin(),
                       [](unsigned char c) { return std::toupper(c); });
        
        // Конвертация первой суммы в целевую валюту
        MoneyLib::Money converted = MoneyLib::convertCurrency(
            amounts[0], rates, targetCurrency);
        
        // Сложение всех сумм
        MoneyLib::Money sum = MoneyLib::addMoney(amounts, rates, targetCurrency);
        
        // Вычитание (если есть хотя бы две суммы)
        MoneyLib::Money difference;
        if (amounts.size() >= 2) {
            difference = MoneyLib::subtractMoney(amounts[0], amounts[1], rates);
        } else {
            difference = MoneyLib::Money(0, targetCurrency);
        }
        
        // Вычисление 10% от первой суммы
        MoneyLib::Money percentage = MoneyLib::calculatePercentage(
            amounts[0], 10.0);
        
        // Округление до копеек
        MoneyLib::Money rounded = MoneyLib::roundToKopeks(sum);
        
        // Вывод результатов
        MoneyLib::printResults(converted, sum, difference, percentage, rounded);
        
        // Пример дополнительных операций
        std::cout << "\n=== ДОПОЛНИТЕЛЬНЫЕ ОПЕРАЦИИ ===\n";
        
        // Округление каждой суммы
        std::cout << "Округленные исходные суммы:\n";
        for (const auto& money : amounts) {
            MoneyLib::Money roundedMoney = MoneyLib::roundToKopeks(money);
            std::cout << "- " << roundedMoney.amount << " " 
                      << roundedMoney.currency << std::endl;
        }
        
        // Расчет разных процентов
        std::cout << "\nПроценты от первой суммы:\n";
        for (double perc : {5.0, 15.0, 20.0, 50.0}) {
            MoneyLib::Money percMoney = MoneyLib::calculatePercentage(
                amounts[0], perc);
            std::cout << "- " << perc << "%: " << percMoney.amount 
                      << " " << percMoney.currency << std::endl;
        }
        
    } catch (const MoneyLib::MoneyException& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Неожиданная ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}