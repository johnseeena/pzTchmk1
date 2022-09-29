#include "BigInt.h"
#include "BigInt.h"

// ������� ������� ����� ����� �� ��������� 0
BigInt::BigInt() {
    this->_is_negative = false;
}

// ������� ������� ����� ����� �� C++-������
BigInt::BigInt(std::string str) {
    if (str.length() == 0) {
        this->_is_negative = false;
    }
    else {
        if (str[0] == '-') {
            str = str.substr(1);
            this->_is_negative = true;
        }
        else {
            this->_is_negative = false;
        }

        for (long long i = str.length(); i > 0; i -= 9) {
            if (i < 9)
                this->_digits.push_back(atoi(str.substr(0, i).c_str()));
            else
                this->_digits.push_back(atoi(str.substr(i - 9, 9).c_str()));
        }

        this->_remove_leading_zeros();
    }
}

// ������� ������� ����
void BigInt::_remove_leading_zeros() {
    while (this->_digits.size() > 1 && this->_digits.back() == 0) {
        this->_digits.pop_back();
    }

    if (this->_digits.size() == 1 && this->_digits[0] == 0) this->_is_negative = false;
}

// �������� ����� � ����� ������
std::ostream& operator <<(std::ostream& os, const BigInt& bi) {
    if (bi._digits.empty()) os << 0;
    else {
        if (bi._is_negative) os << '-';
        os << bi._digits.back();
        char old_fill = os.fill('0');
        for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i) os << std::setw(9) << bi._digits[i];
        os.fill(old_fill);
    }

    return os;
}

// ���������� ��� ����� �� ���������
bool operator ==(const BigInt& left, const BigInt& right) {
    if (left._is_negative != right._is_negative) return false;
    if (left._digits.empty()) {
        if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0)) return true;
        else return false;
    }

    if (right._digits.empty()) {
        if (left._digits.size() == 1 && left._digits[0] == 0) return true;
        else return false;
    }

    if (left._digits.size() != right._digits.size()) return false;
    for (size_t i = 0; i < left._digits.size(); ++i) if (left._digits[i] != right._digits[i]) return false;

    return true;
}

// ���������� ����� ����������� �����
const BigInt BigInt::operator +() const {
    return BigInt(*this);
}

// ���������� ���������� ����� � ������ ������
const BigInt BigInt::operator -() const {
    BigInt copy(*this);
    copy._is_negative = !copy._is_negative;
    return copy;
}

// ���������, �������� �� ����� ������� ������ �������
bool operator <(const BigInt& left, const BigInt& right) {
    if (left == right) return false;
    if (left._is_negative) {
        if (right._is_negative) return ((-right) < (-left));
        else return true;
    }
    else if (right._is_negative) return false;
    else {
        if (left._digits.size() != right._digits.size()) {
            return left._digits.size() < right._digits.size();
        }
        else {
            for (long long i = left._digits.size() - 1; i >= 0; --i) {
                if (left._digits[i] != right._digits[i]) return left._digits[i] < right._digits[i];
            }

            return false;
        }
    }
}

// ���������� ��� ����� �� �����������
bool operator !=(const BigInt& left, const BigInt& right) {
    return !(left == right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator <=(const BigInt& left, const BigInt& right) {
    return (left < right || left == right);
}

// ���������, �������� �� ����� ������� ������ �������
bool operator >(const BigInt& left, const BigInt& right) {
    return !(left <= right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������
bool operator >=(const BigInt& left, const BigInt& right) {
    return !(left < right);
}

// ���������� ��� �����
const BigInt operator +(BigInt left, const BigInt& right) {
    if (left._is_negative) {
        if (right._is_negative) return -(-left + (-right));
        else return right - (-left);
    }
    else if (right._is_negative) return left - (-right);
    int carry = 0;
    for (size_t i = 0; i < std::max(left._digits.size(), right._digits.size()) || carry != 0; ++i) {
        if (i == left._digits.size()) left._digits.push_back(0);
        left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] >= BigInt::BASE;
        if (carry != 0) left._digits[i] -= BigInt::BASE;
    }

    return left;
}

// ���������� � �������� ����� �����
BigInt& BigInt::operator +=(const BigInt& value) {
    return *this = (*this + value);
}

// ���������� ���������
const BigInt BigInt::operator++() {
    return (*this += 1);
}

// ����������� ����� � ������
BigInt::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

// ����������� signed char � big_integer
BigInt::BigInt(signed char c) {
    if (c < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(c));
}

// ����������� unsigned char � big_integer
BigInt::BigInt(unsigned char c) {
    this->_is_negative = false;
    this->_digits.push_back(c);
}

// ����������� signed short � big_integer
BigInt::BigInt(signed short s) {
    if (s < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(s));
}

// ����������� unsigned short � big_integer
BigInt::BigInt(unsigned short s) {
    this->_is_negative = false;
    this->_digits.push_back(s);
}

// ����������� signed int � big_integer
BigInt::BigInt(signed int i) {
    if (i < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(i) % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->_digits.push_back(std::abs(i));
}

// ����������� unsigned int � big_integer
BigInt::BigInt(unsigned int i) {
    this->_digits.push_back(i % BigInt::BASE);
    i /= BigInt::BASE;
    if (i != 0) this->_digits.push_back(i);
}

// ����������� signed long � big_integer
BigInt::BigInt(signed long l) {
    if (l < 0) this->_is_negative = true;
    else this->_is_negative = false;
    this->_digits.push_back(std::abs(l) % BigInt::BASE);
    l /= BigInt::BASE;
    if (l != 0) this->_digits.push_back(std::abs(l));
}

// ����������� unsigned long � big_integer
BigInt::BigInt(unsigned long l) {
    this->_digits.push_back(l % BigInt::BASE);
    l /= BigInt::BASE;
    if (l != 0) this->_digits.push_back(l);
}

// ����������� signed long long � big_integer
BigInt::BigInt(signed long long l) {
    if (l < 0) { this->_is_negative = true; l = -l; }
    else this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

// ����������� unsigned long long � big_integer
BigInt::BigInt(unsigned long long l) {
    this->_is_negative = false;
    do {
        this->_digits.push_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

// ����������� ���������
const BigInt BigInt::operator ++(int) {
    *this += 1;
    return *this - 1;
}

// ���������� ���������
const BigInt BigInt::operator --() {
    return *this -= 1;
}

// ����������� ���������
const BigInt BigInt::operator --(int) {
    *this -= 1;
    return *this + 1;
}

// �������� ��� �����
const BigInt operator -(BigInt left, const BigInt& right) {
    if (right._is_negative) return left + (-right);
    else if (left._is_negative) return -(-left + right);
    else if (left < right) return -(right - left);
    int carry = 0;
    for (size_t i = 0; i < right._digits.size() || carry != 0; ++i) {
        left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
        carry = left._digits[i] < 0;
        if (carry != 0) left._digits[i] += BigInt::BASE;
    }

    left._remove_leading_zeros();
    return left;
}

// �������� �� �������� ����� �����
BigInt& BigInt::operator -=(const BigInt& value) {
    return *this = (*this - value);
}

// ����������� ��� �����
const BigInt operator *(const BigInt& left, const BigInt& right) {
    BigInt result;
    result._digits.resize(left._digits.size() + right._digits.size());
    for (size_t i = 0; i < left._digits.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < right._digits.size() || carry != 0; ++j) {
            long long cur = result._digits[i + j] +
                left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
            result._digits[i + j] = static_cast<int>(cur % BigInt::BASE);
            carry = static_cast<int>(cur / BigInt::BASE);
        }
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// ��������� ������� ����� �� ���������
BigInt& BigInt::operator *=(const BigInt& value) {
    return *this = (*this * value);
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE)
void BigInt::_shift_right() {
    if (this->_digits.size() == 0) {
        this->_digits.push_back(0);
        return;
    }
    this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
    for (size_t i = this->_digits.size() - 2; i > 0; --i) this->_digits[i] = this->_digits[i - 1];
    this->_digits[0] = 0;
}

// ����� ��� �����
const BigInt operator /(const BigInt& left, const BigInt& right) {
    if (right == 0) throw BigInt::divide_by_zero();
    BigInt b = right;
    b._is_negative = false;
    BigInt result, current;
    result._digits.resize(left._digits.size());
    for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i) {
        current._shift_right();
        current._digits[0] = left._digits[i];
        current._remove_leading_zeros();
        int x = 0, l = 0, r = BigInt::BASE;
        while (l <= r) {
            int m = (l + r) / 2;
            BigInt t = b * m;
            if (t <= current) {
                x = m;
                l = m + 1;
            }
            else r = m - 1;
        }

        result._digits[i] = x;
        current = current - b * x;
    }

    result._is_negative = left._is_negative != right._is_negative;
    result._remove_leading_zeros();
    return result;
}

// ����� ������� ����� �� ���������
BigInt& BigInt::operator /=(const BigInt& value) {
    return *this = (*this / value);
}

// ���������� ������� �� ������� ���� �����
const BigInt operator %(const BigInt& left, const BigInt& right) {
    BigInt result = left - (left / right) * right;
    if (result._is_negative) result += right;
    return result;
}

// ����������� �������� ����� ������� �� ������� �� ������ �����
BigInt& BigInt::operator %=(const BigInt& value) {
    return *this = (*this % value);
}

// ���������, �������� �� ������� ����� ��������
bool BigInt::odd() const {
    if (this->_digits.size() == 0) return false;
    return this->_digits[0] & 1;
}

// ���������, �������� �� ������� ����� ������
bool BigInt::even() const {
    return !this->odd();
}

// �������� ������� ����� � ��������� �������
const BigInt BigInt::pow(BigInt n) const {
    BigInt a(*this), result(1);
    while (n != 0) {
        if (n.odd()) result *= a;
        a *= a;
        n /= 2;
    }

    return result;
}