#include <arrayd/arrayd.hpp>

#include <stdexcept>

ArrayD::ArrayD(const std::ptrdiff_t size) 
    : ssize_(size) 
{
    if (ssize_ < 0) {
        throw std::invalid_argument("size can't be negative");
    }
    if (size > 0) {
        capacity_ = ssize_;
        data_ = new double[capacity_] {};
    }
}

ArrayD::~ArrayD() {
    delete[] data_;
}

ArrayD::ArrayD(const ArrayD& arr) {
    resize(arr.ssize());
    std::copy(arr.data_, arr.data_ + arr.ssize(), data_);
}

ArrayD& ArrayD::operator=(const ArrayD& arr) {
    resize(arr.ssize());
    std::copy(arr.data_, arr.data_ + arr.ssize(), data_);
    return *this;
}

double& ArrayD::operator[](std::ptrdiff_t i) {
    if (i < 0 || i >= ssize_) {
        throw std::out_of_range("array index out of range");
    }
    return data_[i];
}

const double& ArrayD::operator[](std::ptrdiff_t i) const {
    if (i < 0 || i >= ssize_) {
        throw std::out_of_range("array index out of range");
    }
    return data_[i];
}

std::ptrdiff_t ArrayD::ssize() const noexcept {
    return ssize_;
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
    
}

void ArrayD::insert(const std::ptrdiff_t i, const double value) {

}

void ArrayD::remove(const std::ptrdiff_t i) {
   
}