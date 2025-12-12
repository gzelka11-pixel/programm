#include "list.h"
#include <iostream>

int main() {
    using namespace NotificationSystem;
    
    try {
        // Создаем список уведомлений
        NotificationList notifications;
        
        // Читаем данные из файла
        std::cout << "Чтение данных из файла..." << std::endl;
        notifications.readFromFile("data/input.txt");
        
        // Выводим в консоль для проверки
        std::cout << "\nСодержимое списка после чтения из файла:\n";
        notifications.printToConsole();
        
        // Добавляем новое уведомление в начало
        std::cout << "\nДобавляем новое уведомление..." << std::endl;
        Notification newNotif(7, "Система", "Новое_сообщение", false);
        notifications.addNotification(newNotif);
        
        // Отмечаем уведомление с ID=3 как прочитанное
        std::cout << "\nОтмечаем уведомление с ID=3 как прочитанное..." << std::endl;
        if (notifications.markAsRead(3)) {
            std::cout << "Уведомление с ID=3 отмечено как прочитанное" << std::endl;
        } else {
            std::cout << "Уведомление с ID=3 не найдено" << std::endl;
        }
        
        // Удаляем уведомление с ID=2
        std::cout << "\nУдаляем уведомление с ID=2..." << std::endl;
        if (notifications.removeNotification(2)) {
            std::cout << "Уведомление с ID=2 удалено" << std::endl;
        } else {
            std::cout << "Уведомление с ID=2 не найдено" << std::endl;
        }
        
        // Подсчитываем количество непрочитанных
        std::cout << "\nКоличество непрочитанных уведомлений: " 
                  << notifications.countUnread() << std::endl;
        
        // Записываем результат в файл
        std::cout << "\nЗапись результатов в файл..." << std::endl;
        notifications.writeToFile("data/output.txt");
        
        // Выводим финальный список в консоль
        std::cout << "\nФинальный список уведомлений:\n";
        notifications.printToConsole();
        
        // Список будет автоматически очищен деструктором
        std::cout << "\nПрограмма завершена. Все ресурсы освобождены." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}