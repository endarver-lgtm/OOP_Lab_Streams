#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include "Shop.h"

static void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

static void pauseScreen() {
    std::cout << "\nНажмите Enter, чтобы продолжить...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод, ожидалось целое число\n";
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод, ожидалось число\n";
    }
}

std::string readLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void printMenu() {
    std::cout << "\n--- Магазин парфюмерии ---\n";
    std::cout << std::boolalpha;
    std::cout << "1. Просмотр каталога\n";
    std::cout << "2. Добавить духи\n";
    std::cout << "3. Добавить косметику\n";
    std::cout << "4. Удалить товар\n";
    std::cout << "5. Редактировать цену товара\n";
    std::cout << "6. Сортировка по цене\n";
    std::cout << "7. Сортировка по названию\n";
    std::cout << "8. Поиск по названию\n";
    std::cout << "9. Список производителей\n";
    std::cout << "10. Добавить производителя\n";
    std::cout << "11. Оформить заказ\n";
    std::cout << "12. Экспорт каталога в файл\n";
    std::cout << "0. Выход\n";
    std::cout << "Выбор: ";
}

Manufacturer* chooseManufacturer(Shop& shop) {
    shop.listManufacturers(std::cout);
    int id = readInt("Введите ID производителя: ");
    Manufacturer* m = shop.findManufacturerById(id);
    if (!m) std::cout << "Производитель не найден, будет установлен пустым\n";
    return m;
}

void handleAddPerfume(Shop& shop) {
    std::string name = readLine("Название: ");
    double volume = readDouble("Объём, мл: ");
    double price = readDouble("Цена: ");
    Manufacturer* m = chooseManufacturer(shop);
    std::string family = readLine("Группа аромата: ");
    int hours = readInt("Стойкость, часов: ");
    shop.addPerfume(name, volume, price, m, family, hours);
    std::cout << "Товар добавлен\n";
}

void handleAddCosmetic(Shop& shop) {
    std::string name = readLine("Название: ");
    double volume = readDouble("Объём, мл: ");
    double price = readDouble("Цена: ");
    Manufacturer* m = chooseManufacturer(shop);
    std::string skinType = readLine("Тип кожи: ");
    shop.addCosmetic(name, volume, price, m, skinType);
    std::cout << "Товар добавлен\n";
}

void handleRemoveProduct(Shop& shop) {
    shop.printCatalog(std::cout);
    int id = readInt("ID товара для удаления: ");
    if (shop.removeProduct(id)) std::cout << "Товар удалён\n";
    else std::cout << "Товар с таким ID не найден\n";
}

void handleEditPrice(Shop& shop) {
    shop.printCatalog(std::cout);
    int id = readInt("ID товара для редактирования: ");
    Product* p = shop.findProductById(id);
    if (!p) { std::cout << "Товар не найден\n"; return; }
    double price = readDouble("Новая цена: ");
    p->setPrice(price);
    std::cout << "Цена обновлена\n";
}

void handleSearch(Shop& shop) {
    std::string part = readLine("Часть названия: ");
    auto found = shop.findProductsByName(part);
    if (found.empty()) { std::cout << "Ничего не найдено\n"; return; }
    std::cout.setf(std::ios::left, std::ios::adjustfield);
    std::cout << std::setw(4) << "ID" << std::setw(9) << "Type" << std::setw(22) << "Name";
    std::cout.setf(std::ios::right, std::ios::adjustfield);
    std::cout << std::setw(8) << "Vol,ml" << std::setw(10) << "Price";
    std::cout << "  " << std::setw(14) << "Manufacturer" << std::setw(20) << "Details" << "\n";
    for (auto p : found) p->printRow(std::cout);
}

void handleAddManufacturer(Shop& shop) {
    std::string name = readLine("Название производителя: ");
    std::string country = readLine("Страна: ");
    shop.addManufacturer(name, country);
    std::cout << "Производитель добавлен\n";
}

void handleCreateOrder(Shop& shop) {
    std::string customer = readLine("Имя покупателя: ");
    Order* order = shop.createOrder(customer);
    while (true) {
        shop.printCatalog(std::cout);
        int id = readInt("ID товара для добавления в заказ (0 для завершения): ");
        if (id == 0) break;
        Product* p = shop.findProductById(id);
        if (!p) { std::cout << "Товар не найден\n"; continue; }
        int qty = readInt("Количество: ");
        order->addLine(p, qty);
    }
    std::cout << "\n";
    order->printReceipt(std::cout);
}

void handleExport(Shop& shop) {
    std::string path = readLine("Имя файла для экспорта: ");
    shop.exportCatalogToFile(path);
    std::cout << "Каталог сохранён в файл\n";
}

int main() {

    setlocale(LC_ALL, "Rus");
    Shop shop;
    shop.seedDemoData();

    int choice;
    do {
        clearScreen();
        printMenu();
        choice = readInt("");
        clearScreen();
        switch (choice) {
        case 1: shop.printCatalog(std::cout); break;
        case 2: handleAddPerfume(shop); break;
        case 3: handleAddCosmetic(shop); break;
        case 4: handleRemoveProduct(shop); break;
        case 5: handleEditPrice(shop); break;
        case 6: shop.sortByPrice(); std::cout << "Отсортировано по цене\n"; break;
        case 7: shop.sortByName(); std::cout << "Отсортировано по названию\n"; break;
        case 8: handleSearch(shop); break;
        case 9: shop.listManufacturers(std::cout); break;
        case 10: handleAddManufacturer(shop); break;
        case 11: handleCreateOrder(shop); break;
        case 12: handleExport(shop); break;
        case 0: std::cout << "Выход\n"; break;
        default: std::cout << "Неизвестный пункт меню\n"; break;
        }
        if (choice != 0) pauseScreen();
    } while (choice != 0);

    return 0;
}