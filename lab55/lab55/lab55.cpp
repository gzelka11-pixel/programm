// lab55.cpp: определяет точку входа для приложения.
//

#include "money.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>

// Инициализация статической переменной
std::unordered_map<std::string, double> Money::exchangeRates;

Money::Money(double amount, const std::string& currency)
    : amount(amount), currency(currency) {
}

void Money::setExchangeRate(const std::string& from, const std::string& to, double rate) {
    std::string key = from + "_TO_" + to;
    exchangeRates[key] = rate;
}

double Money::getExchangeRate(const std::string& from, const std::string& to) {
    if (from == to) return 1.0;

    std::string key = from + "_TO_" + to;
    if (exchangeRates.find(key) != exchangeRates.end()) {
        return exchangeRates[key];
    }

    std::string reverseKey = to + "_TO_" + from;
    if (exchangeRates.find(reverseKey) != exchangeRates.end()) {
        return 1.0 / exchangeRates[reverseKey];
    }

    throw std::invalid_argument("Курс обмена не найден для пары: " + from + " -> " + to);
}

void Money::displayAllRates() {
    std::cout << "\n--- ТЕКУЩИЕ КУРСЫ ВАЛЮТ ---" << std::endl;
    for (const auto& rate : exchangeRates) {
        std::cout << "1 " << rate.first.substr(0, 3) << " = "
            << std::fixed << std::setprecision(4) << rate.second
            << " " << rate.first.substr(6, 3) << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

Money Money::convertTo(const std::string& targetCurrency) const {
    if (currency == targetCurrency) return *this;

    double rate = getExchangeRate(currency, targetCurrency);
    return Money(amount * rate, targetCurrency);
}

Money Money::operator+(const Money& other) const {
    Money convertedOther = other.convertTo(currency);
    return Money(amount + convertedOther.amount, currency);
}

Money Money::operator-(const Money& other) const {
    Money convertedOther = other.convertTo(currency);
    return Money(amount - convertedOther.amount, currency);
}

Money Money::calculatePercent(double percent) const {
    return Money(amount * percent / 100.0, currency);
}

Money Money::rounded() const {
    return Money(std::round(amount * 100) / 100, currency);
}

double Money::getAmount() const {
    return amount;
}

std::string Money::getCurrency() const {
    return currency;
}

void Money::print() const {
    std::cout << std::fixed << std::setprecision(2) << amount << " " << currency;
}

Money Money::inputMoney(const std::string& prompt) {
    double amount;
    std::string currency;

    std::cout << prompt;
    std::cout << "Введите сумму: ";
    std::cin >> amount;
    std::cout << "Введите валюту (USD, EUR, RUB): ";
    std::cin >> currency;

    // Преобразуем валюту к верхнему регистру
    for (char& c : currency) {
        c = toupper(c);
    }

    return Money(amount, currency);
}
