#include "Products.h"
#include "Warehouse.h"

int Product::nextId_ = 1;

Product::Product(
    const std::string& name, 
    const Price& price, 
    const Quantity& quantity, 
    const Weight& weight, 
    const std::string& category
) : name_(name), 
    price_(price), 
    quantity_(quantity), 
    weight_(weight), 
    category_(category) 
{
    id_ = nextId_++;
}

void Product::transferTo(Warehouse& other) {
    std::unique_ptr<Product> copyOfMe = this->clone();
    other.addProduct(std::move(copyOfMe));
}

void Product::changeQuantity(int delta) { quantity_.change(delta); }
void Product::setPrice(const Price& newPrice) { price_ = newPrice; }
int Product::getId() const { return id_; }
std::string Product::getName() const { return name_; }
std::string Product::getCategory() const { return category_; }
Price Product::getPrice() const { return price_; }
Quantity Product::getQuantity() const { return quantity_; }
Weight Product::getWeight() const { return weight_; }

Electronics::Electronics(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Product(name, price, quantity, weight, "electronics") {}

Clothing::Clothing(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Product(name, price, quantity, weight, "clothing") {}

Food::Food(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Product(name, price, quantity, weight, "food") {}

Smartphone::Smartphone(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Electronics(name, price, quantity, weight) {}

std::unique_ptr<Product> Smartphone::clone() const { 
    return std::make_unique<Smartphone>(*this); 
}

Laptop::Laptop(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Electronics(name, price, quantity, weight) {}

std::unique_ptr<Product> Laptop::clone() const { 
    return std::make_unique<Laptop>(*this); 
}

TShirt::TShirt(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Clothing(name, price, quantity, weight) {}

std::unique_ptr<Product> TShirt::clone() const { 
    return std::make_unique<TShirt>(*this); 
}

Jacket::Jacket(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Clothing(name, price, quantity, weight) {}

std::unique_ptr<Product> Jacket::clone() const { 
    return std::make_unique<Jacket>(*this); 
}

Milk::Milk(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Food(name, price, quantity, weight) {}

std::unique_ptr<Product> Milk::clone() const { 
    return std::make_unique<Milk>(*this); 
}

Bread::Bread(
    const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight
) : Food(name, price, quantity, weight) {}

std::unique_ptr<Product> Bread::clone() const { 
    return std::make_unique<Bread>(*this); 
}

