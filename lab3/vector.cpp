#include <algorithm>
#include <stdexcept>
#include <utility> // std::swap()
#include "vector.h"

Vector::Vector(std::size_t toAlloc) : size_{}, capacity_{toAlloc} {
    data_ = std::unique_ptr<Fraction[]>(new Fraction[capacity_]);
}

Vector::Vector(const Vector& src) {
    size_ = src.size_;
    capacity_ = src.capacity_;

    data_ = std::unique_ptr<Fraction[]>(new Fraction[capacity_]);
    for (size_t i = 0; i < size_; i++) {
        data_[i] = src.data_[i];
    } 
}

Vector::Vector(Vector&& src) : data_{std::move(src.data_)}, size_{src.size_}, capacity_{src.capacity_} {
    src.size_ = 0;
    src.capacity_ = 0;
}

Vector& Vector::operator=(const Vector& toCopy) {
    if (this == &toCopy) {
        return *this;
    }

    size_ = toCopy.size_;
    capacity_ = toCopy.capacity_;

    data_ = std::unique_ptr<Fraction[]>(new Fraction[capacity_]);
    for (size_t i = 0; i < size_; i++) {
        data_[i] = toCopy.data_[i];
    }

    return *this;
}

Vector& Vector::operator=(Vector&& toMove) {
    if (this == &toMove) {
        return *this;
    }

    size_ = toMove.size_;
    capacity_ = toMove.capacity_;
    data_ = std::move(toMove.data_);

    toMove.size_ = 0;
    toMove.capacity_ = 0;

    return *this;
}

void Vector::push_back(const Fraction& toAdd) {
    if (size_++ == capacity_) {
        auto newData = std::unique_ptr<Fraction[]>(new Fraction[++capacity_]);
        
        for (size_t i = 0; i < size_ - 1; i++) {
            newData[i] = data_[i];
        }

        newData[size_ - 1] = toAdd;
        std::swap(data_, newData);
    } else {
        data_[size_ - 1] = toAdd;
    }
}

Fraction& Vector::operator[](std::size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Indeks poza zasięgiem tablicy: " + index);
    }

    return data_.get()[index];
}

const Fraction& Vector::operator[](std::size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Indeks poza zasięgiem tablicy: " + index);
    }

    return data_.get()[index];
}
