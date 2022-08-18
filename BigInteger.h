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
#include <cmath>

#define LOG2_10 3.32192809489

#define POSITIVE false
#define NEGATIVE true

class BigInteger {
private:
    bool sign;

    std::string digits;

public:
    //Constructors:
    BigInteger(int64_t n = 0);

    BigInteger(std::string &);

    BigInteger(const char *);

    BigInteger(const BigInteger &) = default;

    BigInteger(BigInteger &&other) noexcept : digits(std::move(other.digits)), sign(other.sign) {}

    ~BigInteger() = default;


    // Auxiliary Functions:
    friend void divide_by_2(BigInteger &a);

    friend bool Null(const BigInteger &);

    friend int Length(const BigInteger &);

    const void *address() { return reinterpret_cast<void *>(digits.data()); }

    friend void swap(BigInteger &a, BigInteger &b);

    friend bool abs_less(const BigInteger &a, const BigInteger &b);

    friend bool abs_more(const BigInteger &a, const BigInteger &b);

    friend bool abs_equals(const BigInteger &a, const BigInteger &b);

    // Quick Modulus
    BigInteger mod_2() const;
    BigInteger mod_5() const;
    BigInteger mod_10() const;


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
    explicit operator int64_t() const;

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

    // Read and Write
    friend std::ostream &operator << (std::ostream &, const BigInteger &);
    friend std::istream &operator >> (std::istream &, BigInteger &);


    /* * * * Arithmetic functions * * * */

    // Basic functions
    static BigInteger sqrt(const BigInteger &);
    static BigInteger log2(const BigInteger &);
    static BigInteger log10(const BigInteger &);
    static BigInteger abs(const BigInteger &);

    // Others
    static BigInteger catalan(int n);
    static BigInteger fibonacci(int n);
    static BigInteger factorial(int n);
};

namespace BigConstants
{
    static const BigInteger ZERO = static_cast<int64_t>(0);
    static const BigInteger ONE  = static_cast<int64_t>(1);
    static const BigInteger TWO  = static_cast<int64_t>(2);
    static const BigInteger FIVE = static_cast<int64_t>(5);
    static const BigInteger TEN  = static_cast<int64_t>(10);
    static const BigInteger HUND = static_cast<int64_t>(100);
}

#endif //BIGINTEGER_BIGINTEGER_H
