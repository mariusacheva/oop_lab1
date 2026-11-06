#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <memory>
#include "Products.h"

class WarehouseIterator {
private:
    std::vector<std::unique_ptr<Product>>::iterator current_;
    std::vector<std::unique_ptr<Product>>::iterator end_;
public:
    WarehouseIterator(std::vector<std::unique_ptr<Product>>::iterator start, std::vector<std::unique_ptr<Product>>::iterator finish);
    WarehouseIterator& operator++();
    Product* operator*();
    bool operator!=(const WarehouseIterator& other) const;
    bool operator==(const WarehouseIterator& other) const;
};

class ConstWarehouseIterator {
private:
    std::vector<std::unique_ptr<Product>>::const_iterator current_;
    std::vector<std::unique_ptr<Product>>::const_iterator end_;
public:
    ConstWarehouseIterator(std::vector<std::unique_ptr<Product>>::const_iterator start, std::vector<std::unique_ptr<Product>>::const_iterator finish);
    ConstWarehouseIterator& operator++();
    const Product* operator*() const;
    bool operator!=(const ConstWarehouseIterator& other) const;
    bool operator==(const ConstWarehouseIterator& other) const;
};

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products_;
    size_t maxSize_;

public:
    Warehouse(size_t maxSize);
    ~Warehouse();
    
    Warehouse(const Warehouse& other);
    Warehouse& operator=(const Warehouse& other);
    Warehouse(Warehouse&& other) noexcept;
    Warehouse& operator=(Warehouse&& other) noexcept;

    void addProduct(std::unique_ptr<Product> product);
    void removeById(int id);
    void removeByIndex(size_t index);
    
    Product* findById(int id) const;
    std::vector<Product*> findByCategory(const std::string& category) const;
    std::vector<Product*> findByPrice(const Price& price) const;

    WarehouseIterator begin();
    WarehouseIterator end();
    ConstWarehouseIterator begin() const;
    ConstWarehouseIterator end() const;
};

#endif
