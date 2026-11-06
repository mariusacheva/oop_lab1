#include "Attributes.h"

Price::Price() : value_(0) {}
Price::Price(int val) { setValue(val); }
int Price::getValue() const { return value_; }
void Price::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Цена не может быть отрицательной!");
    value_ = newVal;
}

Quantity::Quantity() : value_(0) {}
Quantity::Quantity(int val) { setValue(val); }
int Quantity::getValue() const { return value_; }
void Quantity::setValue(int newVal) {
    if (newVal < 0) throw std::invalid_argument("Количество не может быть отрицательным!");
    value_ = newVal;
}
void Quantity::change(int delta) {
    if (value_ + delta < 0) throw std::invalid_argument("Недостаточно товара на складе!");
    value_ += delta;
}

Weight::Weight() : value_(0.0) {}
Weight::Weight(double val) { setValue(val); }
double Weight::getValue() const { return value_; }
void Weight::setValue(double newVal) {
    if (newVal < 0.0) throw std::invalid_argument("Вес не может быть отрицательным!");
    value_ = newVal;
}
