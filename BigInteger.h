#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <exception>
#include <stdexcept>
#include <climits>
#include <algorithm>
#include <cstdint>


class BigInteger {
private:
    std::string digits;

public:
    //Constructors:
    BigInteger(uint64_t n = 0);

    BigInteger(std::string &);

    BigInteger(const char *);

    BigInteger(const BigInteger &) = default;

    BigInteger(BigInteger &&other) noexcept : digits(other.digits) {}

    ~BigInteger() = default;


    // Auxiliary Functions:
    friend void divide_by_2(BigInteger &a);

    friend bool Null(const BigInteger &);

    friend int Length(const BigInteger &);

    const void *address() { return reinterpret_cast<void *>(digits.data()); }


    // Decimal String representation:
    std::string toString() const;

    // Hexadecimal String Representation:
    std::string hex() const;


    /* * * * Operator Overloading * * * */

    // Direct assignment
    BigInteger &operator = (const BigInteger &);
    BigInteger &operator = (BigInteger &&) noexcept;

    // Post/Pre - Incrementation
    BigInteger &operator ++ () &;
    BigInteger &operator -- () &;

    BigInteger &operator ++ () && = delete;
    BigInteger &operator -- () && = delete;

    BigInteger operator ++ (int) &;
    BigInteger operator -- (int) &;

    BigInteger operator ++ (int) && = delete;
    BigInteger operator -- (int) && = delete;

    // Cast to uint64_t
    explicit operator uint64_t() const;

    // Subscript operator
    int operator[] (int) const;

    // Addition and Subtraction
    friend BigInteger &operator += (BigInteger &, const BigInteger &);
    friend BigInteger &operator -= (BigInteger &, const BigInteger &);

    friend BigInteger operator + (const BigInteger &, const BigInteger &);
    friend BigInteger operator - (const BigInteger &, const BigInteger &);

    // Comparison operators
    friend bool operator == (const BigInteger &, const BigInteger &);
    friend bool operator != (const BigInteger &, const BigInteger &);

    friend bool operator > (const BigInteger &, const BigInteger &);
    friend bool operator < (const BigInteger &, const BigInteger &);

    friend bool operator >= (const BigInteger &, const BigInteger &);
    friend bool operator <= (const BigInteger &, const BigInteger &);

    // Multiplication and Division
    friend BigInteger &operator *= (BigInteger &, const BigInteger &);
    friend BigInteger &operator /= (BigInteger &, const BigInteger &);

    friend BigInteger operator * (const BigInteger &, const BigInteger &);
    friend BigInteger operator / (const BigInteger &, const BigInteger &);

    // Modulo
    friend BigInteger &operator %= (BigInteger &, const BigInteger &);
    friend BigInteger operator % (const BigInteger &, const BigInteger &);

    // Power Function
    friend BigInteger &operator ^= (BigInteger &, const BigInteger &);
    friend BigInteger operator ^ (const BigInteger &, const BigInteger &);

    // Square Root Function
    friend BigInteger sqrt(BigInteger &a);

    // Read and Write
    friend std::ostream &operator << (std::ostream &, const BigInteger &);
    friend std::istream &operator >> (std::istream &, BigInteger &);

    // Others
    static BigInteger catalan(int n);
    static BigInteger fibonacci(int n);
    static BigInteger factorial(int n);
};

namespace BigConstants
{
    static const BigInteger ZERO = static_cast<uint64_t>(0);
    static const BigInteger ONE  = static_cast<uint64_t>(1);
    static const BigInteger TWO  = static_cast<uint64_t>(2);
    static const BigInteger FIVE = static_cast<uint64_t>(5);
    static const BigInteger TEN  = static_cast<uint64_t>(10);
    static const BigInteger HUND = static_cast<uint64_t>(100);
}

#endif //BIGINTEGER_BIGINTEGER_H
