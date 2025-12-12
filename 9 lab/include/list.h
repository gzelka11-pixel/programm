#ifndef NOTIFICATION_LIST_H
#define NOTIFICATION_LIST_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

namespace NotificationSystem {

// Структура уведомления
struct Notification {
    int id;
    char* type;
    char* message;
    bool isRead;
    
    // Конструктор по умолчанию
    Notification() : id(0), type(nullptr), message(nullptr), isRead(false) {}
    
    // Конструктор с параметрами
    Notification(int id, const char* type, const char* message, bool isRead) 
        : id(id), isRead(isRead) {
        this->type = new char[strlen(type) + 1];
        strcpy(this->type, type);
        
        this->message = new char[strlen(message) + 1];
        strcpy(this->message, message);
    }
    
    // Деструктор
    ~Notification() {
        delete[] type;
        delete[] message;
    }
    
    // Конструктор копирования
    Notification(const Notification& other) 
        : id(other.id), isRead(other.isRead) {
        type = new char[strlen(other.type) + 1];
        strcpy(type, other.type);
        
        message = new char[strlen(other.message) + 1];
        strcpy(message, other.message);
    }
    
    // Оператор присваивания
    Notification& operator=(const Notification& other) {
        if (this != &other) {
            delete[] type;
            delete[] message;
            
            id = other.id;
            isRead = other.isRead;
            
            type = new char[strlen(other.type) + 1];
            strcpy(type, other.type);
            
            message = new char[strlen(other.message) + 1];
            strcpy(message, other.message);
        }
        return *this;
    }
};

// Структура узла списка
struct Node {
    Notification data;
    Node* next;
    
    Node(const Notification& notif) : data(notif), next(nullptr) {}
};

// Класс для управления списком уведомлений
class NotificationList {
private:
    Node* head;
    int size;
    
    // Вспомогательная функция для копирования
    void copyFrom(const NotificationList& other);
    
    // Вспомогательная функция для очистки
    void clear();
    
public:
    // Конструкторы и деструктор
    NotificationList();
    NotificationList(const NotificationList& other);
    ~NotificationList();
    
    // Оператор присваивания
    NotificationList& operator=(const NotificationList& other);
    
    // Основные функции
    void addNotification(const Notification& notif);
    bool removeNotification(int id);
    bool markAsRead(int id);
    int countUnread() const;
    void printToFile(std::ofstream& out) const;
    void printToConsole() const;
    bool isEmpty() const;
    int getSize() const;
    
    // Функция для чтения из файла
    void readFromFile(const std::string& filename);
    
    // Функция для записи в файл
    void writeToFile(const std::string& filename) const;
};

} // namespace NotificationSystem

#endif // NOTIFICATION_LIST_H