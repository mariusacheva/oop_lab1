#ifndef PRODUCTS_H
#define PRODUCTS_H

#include <string>
#include <memory>
#include "Attributes.h"

class Warehouse; 

class Product {
protected:
    int id_;
    std::string name_;
    Price price_;
    Quantity quantity_;
    Weight weight_;
    std::string category_;
    static int nextId_;

public:
    Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category);
    virtual ~Product() = default;

    virtual std::unique_ptr<Product> clone() const = 0;
    void transferTo(Warehouse& other);
    
    void changeQuantity(int delta);
    void setPrice(const Price& newPrice);

    int getId() const;
    std::string getName() const;
    std::string getCategory() const;
    Price getPrice() const;
    Quantity getQuantity() const;
    Weight getWeight() const;
};

class Electronics : public Product {
public:
    Electronics(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Clothing : public Product {
public:
    Clothing(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Food : public Product {
public:
    Food(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
};

class Smartphone : public Electronics {
public:
    Smartphone(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Laptop : public Electronics {
public:
    Laptop(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class TShirt : public Clothing {
public:
    TShirt(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Jacket : public Clothing {
public:
    Jacket(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Milk : public Food {
public:
    Milk(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

class Bread : public Food {
public:
    Bread(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight);
    std::unique_ptr<Product> clone() const override;
};

#endif
