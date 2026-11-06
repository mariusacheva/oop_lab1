#include "Warehouse.h"

WarehouseIterator::WarehouseIterator(
    std::vector<std::unique_ptr<Product>>::iterator start, 
    std::vector<std::unique_ptr<Product>>::iterator finish
) : current_(start), end_(finish) {}

WarehouseIterator& WarehouseIterator::operator++() { 
    if (current_ != end_) ++current_; 
    return *this; 
}

Product* WarehouseIterator::operator*() { 
    return current_->get(); 
}

bool WarehouseIterator::operator!=(const WarehouseIterator& other) const { 
    return current_ != other.current_; 
}

bool WarehouseIterator::operator==(const WarehouseIterator& other) const { 
    return current_ == other.current_; 
}

ConstWarehouseIterator::ConstWarehouseIterator(
    std::vector<std::unique_ptr<Product>>::const_iterator start, 
    std::vector<std::unique_ptr<Product>>::const_iterator finish
) : current_(start), end_(finish) {}

ConstWarehouseIterator& ConstWarehouseIterator::operator++() { 
    if (current_ != end_) ++current_; 
    return *this; 
}

const Product* ConstWarehouseIterator::operator*() const { 
    return current_->get(); 
}

bool ConstWarehouseIterator::operator!=(const ConstWarehouseIterator& other) const { 
    return current_ != other.current_; 
}

bool ConstWarehouseIterator::operator==(const ConstWarehouseIterator& other) const { 
    return current_ == other.current_; 
}

Warehouse::Warehouse(size_t maxSize) : maxSize_(maxSize) {
    if (maxSize <= 0) {
        throw std::invalid_argument("Размер должен быть больше нуля!");
    }
}

Warehouse::~Warehouse() = default;

Warehouse::Warehouse(const Warehouse& other) : maxSize_(other.maxSize_) {
    for (const auto& prod : other.products_) {
        if (prod) this->products_.push_back(prod->clone());
    }
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this == &other) return *this;
    this->products_.clear();
    this->maxSize_ = other.maxSize_;
    for (const auto& prod : other.products_) {
        if (prod) this->products_.push_back(prod->clone());
    }
    return *this;
}

Warehouse::Warehouse(Warehouse&& other) noexcept 
    : products_(std::move(other.products_)), 
      maxSize_(other.maxSize_) 
{ 
    other.maxSize_ = 0; 
}

Warehouse& Warehouse::operator=(Warehouse&& other) noexcept {
    if (this == &other) return *this;
    this->products_ = std::move(other.products_);
    this->maxSize_ = other.maxSize_;
    other.maxSize_ = 0;
    return *this;
}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    if (products_.size() >= maxSize_) {
        throw std::runtime_error("Склад переполнен!");
    }
    if (product) products_.push_back(std::move(product));
}

void Warehouse::removeById(int id) {
    for (auto it = products_.begin(); it != products_.end(); ++it) {
        if ((*it)->getId() == id) { 
            products_.erase(it); 
            return; 
        }
    }
    throw std::runtime_error("Товар не найден!");
}

void Warehouse::removeByIndex(size_t index) {
    if (index >= products_.size()) {
        throw std::out_of_range("Индекс за границами!");
    }
    products_.erase(products_.begin() + index);
}

Product* Warehouse::findById(int id) const {
    for (const auto& prod : products_) { 
        if (prod->getId() == id) return prod.get(); 
    }
    return nullptr;
}

std::vector<Product*> Warehouse::findByCategory(const std::string& category) const {
    std::vector<Product*> result;
    for (const auto& prod : products_) { 
        if (prod->getCategory() == category) {
            result.push_back(prod.get()); 
        }
    }
    return result;
}

std::vector<Product*> Warehouse::findByPrice(const Price& price) const {
    std::vector<Product*> result;
    for (const auto& prod : products_) { 
        if (prod->getPrice().getValue() <= price.getValue()) {
            result.push_back(prod.get()); 
        }
    }
    return result;
}

WarehouseIterator Warehouse::begin() { 
    return WarehouseIterator(products_.begin(), products_.end()); 
}

WarehouseIterator Warehouse::end() { 
    return WarehouseIterator(products_.end(), products_.end()); 
}

ConstWarehouseIterator Warehouse::begin() const { 
    return ConstWarehouseIterator(products_.cbegin(), products_.cend()); 
}

ConstWarehouseIterator Warehouse::end() const { 
    return ConstWarehouseIterator(products_.cend(), products_.cend()); 
}
