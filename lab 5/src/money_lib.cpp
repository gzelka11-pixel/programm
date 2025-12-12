#include "money_lib.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <limits>

namespace MoneyLib {

    Money::Money(double amt, const std::string& curr) 
        : amount(amt), currency(curr) {
        if (amount < 0) {
            throw MoneyException("Сумма не может быть отрицательной");
        }
        if (currency.empty()) {
            throw MoneyException("Валюта не может быть пустой");
        }
    }

    std::vector<Money> inputMoneyAmounts() {
        std::vector<Money> amounts;
        int count;
        
        std::cout << "Введите количество денежных сумм: ";
        std::cin >> count;
        
        if (count <= 0) {
            throw MoneyException("Количество сумм должно быть положительным");
        }
        
        for (int i = 0; i < count; ++i) {
            double amount;
            std::string currency;
            
            std::cout << "Сумма " << i + 1 << " (например: 100.50): ";
            std::cin >> amount;
            
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw MoneyException("Некорректный ввод суммы");
            }
            
            std::cout << "Валюта " << i + 1 << " (например: RUB, USD, EUR): ";
            std::cin >> currency;
            
            // Проверка валюты
            std::string upperCurrency = currency;
            std::transform(upperCurrency.begin(), upperCurrency.end(), 
                          upperCurrency.begin(), ::toupper);
            
            amounts.emplace_back(amount, upperCurrency);
        }
        
        return amounts;
    }

    std::vector<ExchangeRate> inputExchangeRates() {
        std::vector<ExchangeRate> rates;
        int count;
        
        std::cout << "Введите количество курсов обмена: ";
        std::cin >> count;
        
        if (count <= 0) {
            throw MoneyException("Количество курсов должно быть положительным");
        }
        
        for (int i = 0; i < count; ++i) {
            ExchangeRate rate;
            
            std::cout << "Курс " << i + 1 << " - из валюты: ";
            std::cin >> rate.fromCurrency;
            
            std::cout << "Курс " << i + 1 << " - в валюту: ";
            std::cin >> rate.toCurrency;
            
            std::cout << "Курс обмена (например: 0.011 для USD->RUB): ";
            std::cin >> rate.rate;
            
            if (std::cin.fail() || rate.rate <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw MoneyException("Курс обмена должен быть положительным числом");
            }
            
            // Приводим валюты к верхнему регистру
            std::transform(rate.fromCurrency.begin(), rate.fromCurrency.end(),
                          rate.fromCurrency.begin(), ::toupper);
            std::transform(rate.toCurrency.begin(), rate.toCurrency.end(),
                          rate.toCurrency.begin(), ::toupper);
            
            rates.push_back(rate);
        }
        
        return rates;
    }

    Money convertCurrency(const Money& money, 
                         const std::vector<ExchangeRate>& rates,
                         const std::string& targetCurrency) {
        
        if (money.currency == targetCurrency) {
            return money;
        }
        
        // Поиск прямого курса
        for (const auto& rate : rates) {
            if (rate.fromCurrency == money.currency && 
                rate.toCurrency == targetCurrency) {
                return Money(money.amount * rate.rate, targetCurrency);
            }
        }
        
        // Поиск обратного курса
        for (const auto& rate : rates) {
            if (rate.fromCurrency == targetCurrency && 
                rate.toCurrency == money.currency) {
                return Money(money.amount / rate.rate, targetCurrency);
            }
        }
        
        throw MoneyException("Не найден курс обмена для указанных валют");
    }

    Money addMoney(const std::vector<Money>& amounts,
                  const std::vector<ExchangeRate>& rates,
                  const std::string& targetCurrency) {
        
        if (amounts.empty()) {
            return Money(0, targetCurrency);
        }
        
        double total = 0;
        for (const auto& money : amounts) {
            if (money.currency == targetCurrency) {
                total += money.amount;
            } else {
                Money converted = convertCurrency(money, rates, targetCurrency);
                total += converted.amount;
            }
        }
        
        return Money(total, targetCurrency);
    }

    Money subtractMoney(const Money& minuend,
                       const Money& subtrahend,
                       const std::vector<ExchangeRate>& rates) {
        
        // Конвертируем вычитаемое в валюту уменьшаемого
        Money convertedSubtrahend = convertCurrency(subtrahend, rates, 
                                                   minuend.currency);
        
        if (minuend.amount < convertedSubtrahend.amount) {
            throw MoneyException("Результат вычитания не может быть отрицательным");
        }
        
        return Money(minuend.amount - convertedSubtrahend.amount, 
                    minuend.currency);
    }

    Money calculatePercentage(const Money& money, double percentage) {
        if (percentage < 0 || percentage > 100) {
            throw MoneyException("Процент должен быть от 0 до 100");
        }
        
        double result = money.amount * (percentage / 100.0);
        return Money(result, money.currency);
    }

    Money roundToKopeks(const Money& money) {
        // Округляем до двух знаков после запятой (копейки)
        double rounded = std::round(money.amount * 100.0) / 100.0;
        return Money(rounded, money.currency);
    }

    void printResults(const Money& converted,
                     const Money& sum,
                     const Money& difference,
                     const Money& percentage,
                     const Money& rounded) {
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\n=== РЕЗУЛЬТАТЫ ===\n";
        std::cout << "Конвертированная сумма: " << converted.amount 
                  << " " << converted.currency << std::endl;
        std::cout << "Сумма всех валют: " << sum.amount 
                  << " " << sum.currency << std::endl;
        std::cout << "Разность: " << difference.amount 
                  << " " << difference.currency << std::endl;
        std::cout << "10% от суммы: " << percentage.amount 
                  << " " << percentage.currency << std::endl;
        std::cout << "Округленная сумма: " << rounded.amount 
                  << " " << rounded.currency << std::endl;
    }

} // namespace MoneyLib