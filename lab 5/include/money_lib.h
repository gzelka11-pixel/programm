#ifndef MONEY_LIB_H
#define MONEY_LIB_H

#include <string>
#include <vector>
#include <stdexcept>

namespace MoneyLib {
    
    // Исключение для ошибок валидации
    class MoneyException : public std::runtime_error {
    public:
        explicit MoneyException(const std::string& message) 
            : std::runtime_error(message) {}
    };

    // Структура для хранения денежной суммы
    struct Money {
        double amount;
        std::string currency;  // RUB, USD, EUR и т.д.
        
        Money(double amt = 0.0, const std::string& curr = "RUB");
    };

    // Структура для хранения курса обмена
    struct ExchangeRate {
        std::string fromCurrency;
        std::string toCurrency;
        double rate;
    };

    // Функция ввода денежных сумм
    std::vector<Money> inputMoneyAmounts();
    
    // Функция ввода курсов обмена
    std::vector<ExchangeRate> inputExchangeRates();
    
    // Конвертация денежной суммы
    Money convertCurrency(const Money& money, 
                         const std::vector<ExchangeRate>& rates,
                         const std::string& targetCurrency);
    
    // Сложение денежных сумм
    Money addMoney(const std::vector<Money>& amounts,
                  const std::vector<ExchangeRate>& rates,
                  const std::string& targetCurrency);
    
    // Вычитание денежных сумм
    Money subtractMoney(const Money& minuend,
                       const Money& subtrahend,
                       const std::vector<ExchangeRate>& rates);
    
    // Вычисление процентов от суммы
    Money calculatePercentage(const Money& money, double percentage);
    
    // Округление до копеек
    Money roundToKopeks(const Money& money);
    
    // Вывод результатов
    void printResults(const Money& converted,
                     const Money& sum,
                     const Money& difference,
                     const Money& percentage,
                     const Money& rounded);

} // namespace MoneyLib

#endif // MONEY_LIB_H