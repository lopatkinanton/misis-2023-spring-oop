#pragma once
#ifndef ARRAYD_ARRAYD_HPP
#define ARRAYD_ARRAYD_HPP

#include <cstddef>

class ArrayD {
public:
    ArrayD() = default;
    explicit ArrayD(const std::ptrdiff_t size = 0);
    ~ArrayD();

    ArrayD(const ArrayD&) = delete;
    ArrayD& operator=(const ArrayD&) = delete;

    /**
     * \brief ������ � ��������� �� �������
     * \param[in] i ������ ������������� ��������
     * \return i-��� �������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size)
     */
    [[nodiscard]] double& operator[](std::ptrdiff_t i);
    [[nodiscard]] const double& operator[](std::ptrdiff_t i) const;

    [[nodiscard]] std::ptrdiff_t ssize() const noexcept;

    /**
     * \brief ��������� ������� �������
     * \param[in] new_size ����� ������ �������
     * \throw std::invalid_argument ���� ������� �������� new_size <= 0
     */
    void resize(const std::ptrdiff_t new_size);

    /**
     * \brief ��������� �������. ���� ������� ������������, ������ resize
     * \param[in] i ������ ��������, ������� ����� ��������
     * \param[in] value ��������, ������� ���� ��������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size]
     */
    void insert(const std::ptrdiff_t i, const double value);

    /**
     * \brief ������� ������� �� ������� i
     * \param[in] i ������ ���������� ��������
     * \throw std::out_of_range ���� ������ ��� ��������� [0, size)
     */
    void remove(const std::ptrdiff_t i);

private:
    std::ptrdiff_t ssize_ = 0;
    std::ptrdiff_t capacity_ = 0;
    double* data_ = nullptr;
};

#endif