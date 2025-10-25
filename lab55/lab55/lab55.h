// lab55.h : включаемый файл для стандартных системных включаемых файлов
// или включаемые файлы для конкретного проекта.

#pragma once
#include <string>
#include <unordered_map>

class Money {
private:
    double amount;
    std::string currency;
    static std::unordered_map<std::string, double> exchangeRates;

public:
    Money(double amount = 0.0, const std::string& currency = "USD");

    // Управление курсами валют
    static void setExchangeRate(const std::string& from, const std::string& to, double rate);
    static double getExchangeRate(const std::string& from, const std::string& to);
    static void displayAllRates();

    // Основные операции
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;
    Money calculatePercent(double percent) const;
    Money rounded() const;
    Money convertTo(const std::string& targetCurrency) const;

    // Геттеры
    double getAmount() const;
    std::string getCurrency() const;

    // Ввод/вывод
    void print() const;
    static Money inputMoney(const std::string& prompt);
};
int main() {

}
