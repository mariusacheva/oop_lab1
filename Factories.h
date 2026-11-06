#ifndef FACTORIES_H
#define FACTORIES_H

#include "Products.h"

class ProductFactory {
public:
    virtual ~ProductFactory() = default;
    virtual std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) = 0;
};

class SmartphoneFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

class LaptopFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

class TShirtFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

class JacketFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

class MilkFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

class BreadFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(int id, const std::string& name, int price, int quantity, double weight) override;
};

#endif
