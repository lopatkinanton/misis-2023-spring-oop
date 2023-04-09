#include <rational/rational.hpp>

#include <iostream>
#include <exception>
#include <string>

Rational::Rational(const int32_t num) noexcept
    :num_(num)
    ,denom_(1)
{
}

Rational::Rational(const int32_t num, const int32_t denom) {
    if (denom == 0) {
        throw std::invalid_argument("division by zero");
    }
    normalize();
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
    return rhs.writeTo(ostrm);
}
std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
    ostrm << num_ << separator << denom_;
    return ostrm;
}
std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
    return rhs.readFrom(istrm);
}
std::istream& Rational::readFrom(std::istream& istrm) noexcept {
    int32_t num(0);
    int32_t denom(1);
    char division_symbol(0);
    istrm >> num;
    istrm >> division_symbol;
    istrm >> denom;
    if (istrm.good() || !istrm.fail() && istrm.eof()) {
        if (Rational::separator == division_symbol) {
            istrm.clear();
            *this = Rational(num, denom);
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}

void operator+=(Rational& lhs, const Rational& rhs) {
    lhs = Rational();
}

void operator-=(Rational& lhs, const Rational& rhs) {
    lhs = Rational();
}
void operator/=(Rational& lhs, const Rational& rhs) {
    lhs = Rational();
}
void operator*=(Rational& lhs, const Rational& rhs) {
    lhs = Rational();
}

Rational Rational::operator-() noexcept {
    num_ = -num_;
    return *this;
}

bool Rational::operator==(const Rational& rhs) const noexcept { return (num_ == rhs.num_) && (denom_ == rhs.denom_); }
bool Rational::operator!=(const Rational& rhs) const noexcept { return !operator==(rhs); }
bool Rational::operator>(const Rational& rhs) const noexcept { return ((num_ * rhs.denom_ - rhs.num_ * denom_) > 0); }
bool operator<(const Rational& lhs, const Rational& rhs) { return rhs.operator>(lhs); }
bool operator<=(const Rational& lhs, const Rational& rhs) { return !lhs.operator>(rhs); }
bool operator>=(const Rational& lhs, const Rational& rhs) { return !rhs.operator>(lhs); }