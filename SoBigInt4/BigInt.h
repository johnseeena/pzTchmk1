#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#pragma once




class BigInt {
    // основание системы счисления (1 000 000 000)
    static const int BASE = 1000000000;

    // внутреннее хранилище числа
    std::vector<int> _digits;

    // знак числа
    bool _is_negative;

    void _remove_leading_zeros();
    void _shift_right();

public:
    // класс-исключение, бросаемое при делении на ноль
    class divide_by_zero : public std::exception {  };

    BigInt();
    BigInt(std::string);
    BigInt(signed char);
    BigInt(unsigned char);
    BigInt(signed short);
    BigInt(unsigned short);
    BigInt(signed int);
    BigInt(unsigned int);
    BigInt(signed long);
    BigInt(unsigned long);
    BigInt(signed long long);
    BigInt(unsigned long long);

    friend std::ostream& operator <<(std::ostream&, const BigInt&);
    operator std::string() const;
    const BigInt operator +() const;
    const BigInt operator -() const;
    const BigInt operator ++();
    const BigInt operator ++(int);
    const BigInt operator --();
    const BigInt operator --(int);
    friend bool operator ==(const BigInt&, const BigInt&);
    friend bool operator <(const BigInt&, const BigInt&);
    friend bool operator !=(const BigInt&, const BigInt&);
    friend bool operator <=(const BigInt&, const BigInt&);
    friend bool operator >(const BigInt&, const BigInt&);
    friend bool operator >=(const BigInt&, const BigInt&);
    friend const BigInt operator +(BigInt, const BigInt&);
    BigInt& operator +=(const BigInt&);
    friend const BigInt operator -(BigInt, const BigInt&);
    BigInt& operator -=(const BigInt&);
    friend const BigInt operator *(const BigInt&, const BigInt&);
    BigInt& operator *=(const BigInt&);
    friend const BigInt operator /(const BigInt&, const BigInt&);
    BigInt& operator /=(const BigInt&);
    friend const BigInt operator %(const BigInt&, const BigInt&);
    BigInt& operator %=(const BigInt&);

    bool odd() const;
    bool even() const;
    const BigInt pow(BigInt) const;
};

