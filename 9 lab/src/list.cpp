#include "list.h"
#include <iostream>
#include <fstream>
#include <cstring>

namespace NotificationSystem {

// Конструктор по умолчанию
NotificationList::NotificationList() : head(nullptr), size(0) {}

// Конструктор копирования
NotificationList::NotificationList(const NotificationList& other) 
    : head(nullptr), size(0) {
    copyFrom(other);
}

// Деструктор
NotificationList::~NotificationList() {
    clear();
}

// Оператор присваивания
NotificationList& NotificationList::operator=(const NotificationList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// Вспомогательная функция для копирования
void NotificationList::copyFrom(const NotificationList& other) {
    if (other.head == nullptr) {
        head = nullptr;
        size = 0;
        return;
    }
    
    Node* current = other.head;
    Node* prev = nullptr;
    
    while (current != nullptr) {
        Node* newNode = new Node(current->data);
        
        if (prev == nullptr) {
            head = newNode;
        } else {
            prev->next = newNode;
        }
        
        prev = newNode;
        current = current->next;
    }
    
    size = other.size;
}

// Вспомогательная функция для очистки
void NotificationList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}

// Добавление уведомления в начало списка
void NotificationList::addNotification(const Notification& notif) {
    Node* newNode = new Node(notif);
    newNode->next = head;
    head = newNode;
    size++;
}

// Удаление уведомления по ID
bool NotificationList::removeNotification(int id) {
    if (head == nullptr) {
        return false;
    }
    
    // Если удаляем первый элемент
    if (head->data.id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        return true;
    }
    
    // Ищем элемент для удаления
    Node* current = head;
    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }
    
    // Если нашли элемент
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        size--;
        return true;
    }
    
    return false;
}

// Отметить уведомление как прочитанное
bool NotificationList::markAsRead(int id) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data.id == id) {
            current->data.isRead = true;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Подсчитать количество непрочитанных уведомлений
int NotificationList::countUnread() const {
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        if (!current->data.isRead) {
            count++;
        }
        current = current->next;
    }
    return count;
}

// Вывести все уведомления в файл
void NotificationList::printToFile(std::ofstream& out) const {
    if (!out.is_open()) {
        std::cerr << "Файл не открыт для записи!" << std::endl;
        return;
    }
    
    out << "Список уведомлений (от новых к старым):\n";
    Node* current = head;
    while (current != nullptr) {
        out << "ID: " << current->data.id 
            << ", Тип: " << current->data.type 
            << ", Сообщение: " << current->data.message 
            << ", Статус: " << (current->data.isRead ? "Прочитано" : "Не прочитано") 
            << "\n";
        current = current->next;
    }
    out << "\nНепрочитанных уведомлений: " << countUnread() << "\n";
}

// Вывести все уведомления в консоль (для отладки)
void NotificationList::printToConsole() const {
    std::cout << "Список уведомлений (от новых к старым):\n";
    Node* current = head;
    while (current != nullptr) {
        std::cout << "ID: " << current->data.id 
                  << ", Тип: " << current->data.type 
                  << ", Сообщение: " << current->data.message 
                  << ", Статус: " << (current->data.isRead ? "Прочитано" : "Не прочитано") 
                  << "\n";
        current = current->next;
    }
    std::cout << "\nНепрочитанных уведомлений: " << countUnread() << "\n";
}

// Проверить, пуст ли список
bool NotificationList::isEmpty() const {
    return head == nullptr;
}

// Получить размер списка
int NotificationList::getSize() const {
    return size;
}

// Чтение уведомлений из файла
void NotificationList::readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }
    
    int count;
    inFile >> count;
    
    // Проверка корректности данных
    if (count < 0) {
        std::cerr << "Некорректное количество уведомлений: " << count << std::endl;
        inFile.close();
        return;
    }
    
    for (int i = 0; i < count; i++) {
        int id;
        std::string type, message;
        int readStatus;
        
        inFile >> id >> type >> message >> readStatus;
        
        // Проверка корректности данных
        if (id < 0 || (readStatus != 0 && readStatus != 1)) {
            std::cerr << "Некорректные данные в строке " << (i + 1) << std::endl;
            continue;
        }
        
        // Заменяем подчеркивания на пробелы для красивого вывода (опционально)
        // В данном случае оставляем как есть, как в примере
        
        bool isRead = (readStatus == 1);
        Notification notif(id, type.c_str(), message.c_str(), isRead);
        addNotification(notif);
    }
    
    inFile.close();
}

// Запись уведомлений в файл
void NotificationList::writeToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Не удалось открыть файл для записи: " << filename << std::endl;
        return;
    }
    
    printToFile(outFile);
    outFile.close();
}

} // namespace NotificationSystem