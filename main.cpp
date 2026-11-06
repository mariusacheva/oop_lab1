#include <iostream>
#include <vector>
#include <memory>
#include "Warehouse.h"
#include "Factories.h"

void printWarehouse(const Warehouse& wh, const std::string& title) {
    for (auto it = wh.begin(); it != wh.end(); ++it) {
        const Product* p = *it;
        std::cout << "ID: " << p->getId() 
                  << " | Название: " << p->getName() 
                  << " | Категория: " << p->getCategory()
                  << " | Цена: " << p->getPrice().getValue() 
                  << " | Кол-во: " << p->getQuantity().getValue() 
                  << " | Вес: " << p->getWeight().getValue() << " кг\n";
    }
    std::cout << "\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    SmartphoneFactory phoneFactory;
    LaptopFactory laptopFactory;
    MilkFactory milkFactory;
    TShirtFactory shirtFactory;

    std::cout << "Сценарий 1: Инициализация склада и добавление через фабрики\n";
    Warehouse mainWarehouse(10); 

    mainWarehouse.addProduct(phoneFactory.createProduct(0, "iPhone 15", 90000, 15, 0.2));
    mainWarehouse.addProduct(laptopFactory.createProduct(0, "MacBook Pro", 190000, 5, 1.6));
    mainWarehouse.addProduct(milkFactory.createProduct(0, " Молоко Простоквашино", 90, 50, 1.0));
    mainWarehouse.addProduct(shirtFactory.createProduct(0, "Худи Nike", 3500, 20, 0.4));

    printWarehouse(mainWarehouse, "Основной склад (Начальное состояние)");

    std::cout << "Сценарий 2: Глубокое копирование склада\n";
    Warehouse copiedWarehouse = mainWarehouse; 

    Product* pInCopy = copiedWarehouse.findById(1);
    if (pInCopy) {
        pInCopy->setPrice(Price(110000)); 
        pInCopy->changeQuantity(-5);      
    }

    printWarehouse(mainWarehouse, "Оригинальный склад (Без изменений)");
    printWarehouse(copiedWarehouse, "Скопированный склад (С изменениями цены/кол-ва)");

    std::cout << "Сценарий 3: Перемещение склада\n";
    Warehouse movedWarehouse = std::move(copiedWarehouse); 

    printWarehouse(movedWarehouse, "Новый склад (Данные после перемещения)");
    printWarehouse(copiedWarehouse, "Старый скопированный склад (Пуст)");

    std::cout << "Сценарий 4: Тестирование функций поиска и удаления\n";
    
    Product* foundId = mainWarehouse.findById(2);
    if (foundId) {
        std::cout << "Найдено по ID 2: " << foundId->getName() << "\n";
    }

    std::cout << "Поиск товаров категории 'food':\n";
    std::vector<Product*> foodProducts = mainWarehouse.findByCategory("food");
    for (auto* p : foodProducts) {
        std::cout << "   " << p->getName() << " (" << p->getPrice().getValue() << " руб)\n";
    }

    std::cout << "Поиск товаров дешевле 5000 руб:\n";
    std::vector<Product*> cheapProducts = mainWarehouse.findByPrice(Price(5000));
    for (auto* p : cheapProducts) {
        std::cout << "   " << p->getName() << " - " << p->getPrice().getValue() << " руб\n";
    }
    std::cout << "\n";

    std::cout << "Удаляем товар с ID 1 (iPhone) и товар под индексом 1 (MacBook)\n";
    mainWarehouse.removeById(1);    
    mainWarehouse.removeByIndex(0); 
    
    printWarehouse(mainWarehouse, "Основной склад после удалений");

    std::cout << "Сценарий 5: Перемещение товара между складами\n";
    Warehouse secondaryWarehouse(5); 
    
    Product* productToTransfer = mainWarehouse.findById(3); 
    if (productToTransfer) {
        std::cout << "Переносим '" << productToTransfer->getName() << "' на вспомогательный склад\n";
        productToTransfer->transferTo(secondaryWarehouse);
    }

    printWarehouse(secondaryWarehouse, "Вспомогательный склад после transferTo");

    std::cout << "Дополнительный тест:\n";
    try {
        std::cout << "Попытка задать отрицательную цену (-500)\n";
        Price badPrice(-500);
    } catch (const std::invalid_argument& e) {
        std::cout << "Перехвачено исключение: " << e.what() << "\n";
    }

    try {
        std::cout << "Попытка переполнить вспомогательный склад сверх лимита\n";
        secondaryWarehouse.addProduct(milkFactory.createProduct(0, "Тест 1", 10, 1, 1));
        secondaryWarehouse.addProduct(milkFactory.createProduct(0, "Тест 2", 10, 1, 1));
        secondaryWarehouse.addProduct(milkFactory.createProduct(0, "Тест 3", 10, 1, 1));
        secondaryWarehouse.addProduct(milkFactory.createProduct(0, "Тест 4", 10, 1, 1));
        secondaryWarehouse.addProduct(milkFactory.createProduct(0, "Тест 5", 10, 1, 1)); 
    } catch (const std::runtime_error& e) {
        std::cout << "Перехвачено исключение переполнения: " << e.what() << "\n";
    }

    return 0;
}
