#include <matrixs/matrixs.hpp>

#include <tuple>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

MatrixS::MatrixS(const SizeType& size) {
    if (get<0>(size) < 0 || get<1>(size) < 0) {
        throw std::invalid_argument("size can't be negative");
    }
    else {
        m_ = get<0>(size);
        n_ = get<1>(size);
        data_ = new int* [m_];
        for (int i = 0; i < m_; i += 1) {
            data_[i] = new int[n_]{};
        }
    }
}

MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
    if (m < 0 || n < 0) {
        throw std::invalid_argument("size can't be negative");
    }
    else {
        m_ = m;
        n_ = n;
        data_ = new int* [m_];
        for (int i = 0; i < m_; i += 1) {
            data_[i] = new int[n_]{};
        }
    }
}

MatrixS::~MatrixS() {
    for (int i = 0; i < m_; i += 1) {
        delete[] data_[i];
    }
    delete[] data_;
}

MatrixS::MatrixS(const MatrixS& other) {
    if (this != &other) {
        resize(other.m_, other.n_);
        for (int i = 0; i < m_; i += 1) {
            std::copy(other.data_[i], other.data_[i] + other.n_, data_[i]);
        }
    }
}

MatrixS& MatrixS::operator=(const MatrixS& other) {
    if (this != &other) {
        resize(SizeType({ other.m_, other.n_ }));
        for (int i = 0; i < m_; i += 1) {
            std::copy(other.data_[i], other.data_[i] + other.n_, data_[i]);
        }
    }
    return *this;
}

int& MatrixS::at(const SizeType& elem) {
    if (0 <= get<0>(elem) && get<0>(elem) < m_ && 0 <= get<1>(elem) && get<1>(elem) < n_) {
        return data_[get<0>(elem)][get<1>(elem)];
    }
    else {
        throw std::out_of_range("matrix index out of range");
    }
}

const int& MatrixS::at(const SizeType& elem) const {
    if (0 <= get<0>(elem) && get<0>(elem) < m_ && 0 <= get<1>(elem) && get<1>(elem) < n_) {
        return data_[get<0>(elem)][get<1>(elem)];
    }
    else {
        throw std::out_of_range("matrix index out of range");
    }
}

int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
    if (0 <= i && i < m_ && 0 <= j && j < n_) {
        return data_[i][j];
    }
    else {
        throw std::out_of_range("matrix index out of range");
    }
}

const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
    if (0 <= i && i < m_ && 0 <= j && j < n_) {
        return data_[i][j];
    }
    else {
        throw std::out_of_range("matrix index out of range");
    }
}

void MatrixS::resize(const SizeType& new_size) {
    std::ptrdiff_t new_m = get<0>(new_size);
    std::ptrdiff_t new_n = get<1>(new_size);
    if (new_m <= 0 || new_n <= 0) {
        throw std::invalid_argument("size should be positive");
    }
    if (new_m > m_ || new_n > n_) {
        auto** new_data = new int* [new_m];
        for (int i = 0; i < new_m; i += 1) {
            new_data[i] = new int[new_n]{};
        }
        for (int i = 0; i < std::min(m_, new_m); i += 1) {
           std::copy(data_[i], data_[i] + std::min(n_, new_n), new_data[i]);
        }
        for (int i = 0; i < m_; i += 1) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    m_ = new_m; 
    n_ = new_n;
}

void MatrixS::resize(const std::ptrdiff_t new_m, const std::ptrdiff_t new_n) {
    if (new_m <= 0 || new_n <= 0) {
        throw std::invalid_argument("size should be positive");
    }
    if (new_m > m_ || new_n > n_) {
        auto** new_data = new int* [new_m];
        for (int i = 0; i < new_m; i += 1) {
            new_data[i] = new int[new_n]{};
        }
        for (int i = 0; i < std::min(m_, new_m); i += 1) {
            std::copy(data_[i], data_[i] + std::min(n_, new_n), new_data[i]);
        }
        for (int i = 0; i < m_; i += 1) {
            delete[] data_[i];
        }
        delete[] data_;
        data_ = new_data;
    }
    m_ = new_m;
    n_ = new_n;
}

const MatrixS::SizeType& MatrixS::ssize() const noexcept {
    return SizeType({ m_, n_ });
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
    return m_;
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
    return n_;
}